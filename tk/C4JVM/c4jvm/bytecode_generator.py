from pycparser import c_ast

class NameException(Exception):
    pass

class TypeException(Exception):
    pass

class SyntaxException(Exception):
    pass

class BytecodeGenerator(object):
    def __init__(self, parent_class):
        self.output = ''
        self.parent_class = parent_class
        self.fields = {}
        self.locals = {}
        self.functions = {}
        self.structs = {}
        self.constants = []
        self.current_return_type = None
        self.current_type = None
        self.class_field_name = None
    
    def visit(self, node):
        method = 'visit_' + node.__class__.__name__
        return getattr(self, method, self.generic_visit)(node)
    
    def generic_visit(self, node):
        if node is None:
            return []
        else:
            return [self.visit(child) for child in node.children()]

    def error_if_exists(self, name):
        if (name in self.structs 
                or name in self.functions or name in self.fields):
            raise NameException(name + " already exists")

    def error_if_exists_locally(self, name):
        if (name in self.structs 
                or name in self.functions or name in self.locals):
            raise NameException(name + " already exists")

    def type_short_name(self, key_value, for_array=None):
        try:
            return {"char": ("c" if for_array else "i"),
                    "int": "i",
                    "float": "f",
                    "void": ""
            }[key_value]
        except:
            return "a"

    def visit_and_prepare_conversion(self, rvalue, lvalue_type):
        visited_rvalue = self.visit(rvalue)
        rvalue_type = self.current_type
        conversion = []
        if rvalue_type != lvalue_type and rvalue_type != "char":
            if (rvalue_type in ("int", "float") and lvalue_type in ("int", "float", "char")):
                if lvalue_type == "char":
                    if rvalue_type == "float":
                        conversion += [("f2i", None)]
                    conversion += [("i2c", None)]
                else:
                    rvalue_type_short_name = self.type_short_name(rvalue_type)
                    lvalue_type_short_name = self.type_short_name(lvalue_type)
                    conversion += [(rvalue_type_short_name + "2" + lvalue_type_short_name, None)]
            else:
                raise TypeException("Cannot convert {0} to {1}".format(rvalue_type, lvalue_type))
        return visited_rvalue + conversion

    def visit_FileAST(self, node):        
        for ext in node.ext:
            name, content = self.visit(ext)
            if isinstance(ext, c_ast.Decl):
                self.error_if_exists(name) 
                typ = type(ext.type)
                if typ == c_ast.Struct:
                    self.structs[name] = content
                elif typ == c_ast.FuncDecl:
                    self.functions[name] = content
                else:          
                    init = [] 
                    if isinstance(ext.type, c_ast.ArrayDecl):
                        if ext.type.dim:
                            if ext.init:
                                raise SyntaxException(
                                            "Cannot initiate array - syntax not supported")
                            init += self.visit(ext.type.dim) + [ 
                                ("newarray" if isinstance(ext.type.type.type, 
                                    c_ast.IdentifierType) else "anewarray" , content[:-2]),
                                ("putstatic", name)]
                        elif ext.init and isinstance(ext.init,
                                              c_ast.Constant) and ext.init.type == "string":
                                    init += self.visit(ext.init) 
                                    init += [("invokevirtual", "toCharArray")]
                                    init += [("putstatic", name)]
                        else:
                            raise SyntaxException("Array size missing")
                    else:
                        if ext.init:
                            init += self.visit_and_prepare_conversion(ext.init, content)
                            init += [("putstatic", name)]
                        elif (isinstance(ext.type, c_ast.TypeDecl) 
                                and ext.type.type and isinstance(ext.type.type, c_ast.Struct)):
                            init += [
                                ("new", content),
                                ("dup", None),
                                ("invoke", content + "/<init>()V"),
                                ("putstatic", name)
                            ]
                        
                    self.fields[name] = (content, init)
            else:
                if name not in self.functions or not self.functions[name]["content"]: 
                    self.functions[name] = content
                else:
                    raise NameException("Redefinition of function " + name)
                    
    def visit_Decl(self, node):
        if isinstance(node.type, c_ast.FuncDecl):
            if node.name in self.functions:
                raise NameException(node.name + " already declared")
            self.current_return_type = ("void" if node.name == "main" 
                                else self.visit(node.type.type)[1])
            args = [] if node.name == "main" else [
                (lambda x: (x[0], x[1]))(self.visit(arg.type)) for arg 
                in node.type.args.params] if node.type.args else []
            
            return (node.name, {
                "returned_type": self.current_return_type,
                "args": args,
                "content": None
            })
        return self.visit(node.type)

    def visit_ArrayDecl(self, node):
        name, typ = self.visit(node.type)
        return (name, typ + '[]')

    def visit_TypeDecl(self, node):
        return (node.declname, self.visit(node.type))

    def visit_IdentifierType(self, node):
        return node.names[0]

    def visit_Struct(self, node):
        if not node.decls:
            return node.name
        return (node.name, [self.visit(decl) for decl in node.decls])

    def visit_FuncDef(self, node):
        if node.decl.name in self.functions and self.functions[node.decl.name]["content"]:
                raise NameException(node.decl.name + " already defined")
        
        self.current_return_type = ("void" if node.decl.name == "main" 
                            else self.visit(node.decl.type.type)[1])
        args = [] if node.decl.name == "main" else [
            (lambda x: (x[0], x[1]))(self.visit(arg.type)) for arg 
            in node.decl.type.args.params] if node.decl.type.args else []
            
        def compare_args(args, new_args):
            if len(new_args) != len(args):
                raise SyntaxException("{0}: bad number of arguments in definition"
                                      .format(node.decl.name))
            for index, arg in enumerate(args):
                if new_args[index][1] != arg[1]:
                    raise TypeException(
                            "{0}: bad argument type at index {1}, got {2}, expected {3}".format(
                            node.decl.name, index, arg[1], new_args[index][1]))
            
        if node.decl.name in self.functions:
            compare_args(self.functions[node.decl.name]["args"], args)
                   
        old_locals = dict(self.locals)
        self.locals = {name: (typ,) for (name, typ) in args}
        body = self.visit(node.body)[0]
        self.locals = old_locals
    
        if self.current_return_type == "void" and (len(body[0]) == 0 
                                or body[0][-1][0] != "return"):
            body[0].append(self.visit(c_ast.Return(None))) 
        
        return (node.decl.name, {
            "returned_type": self.current_return_type,
            "args": args,
            "content": body
        })

    def visit_Constant(self, node):
        if node.type == "char":
            new_constant = (node.type, ord(node.value[1:-1]))
        else:
            new_constant = (node.type, node.value)
        if new_constant in self.constants:
            index = self.constants.index(new_constant)
        else:
            self.constants += [new_constant]
            index = len(self.constants) - 1
        self.current_type = node.type
        return [("ldc", index)]
         
    def visit_ID(self, node):
        if node.name in self.locals:
            node_type_name = self.locals[node.name][0]
            node_type_short_name = self.type_short_name(node_type_name)
            self.current_type = node_type_name
            return [(node_type_short_name + "load", node.name)]
        elif node.name in self.fields:
            self.current_type = self.fields[node.name][0]
            return [("getstatic", node.name)]
        else:
            raise NameException(node.name + " not exists")
 
    def visit_FuncCall(self, node):
        if node.name.name == "printf":
            if len(node.args.exprs) != 1:
                raise SyntaxException("printf: bad number of args")
            visited_arg = self.visit(node.args.exprs[0])
            arg_type = self.current_type
            if arg_type not in ("float", "int", "char", "char[]", "string"):
                raise TypeException("printf: unsupported argument type: " + arg_type)
            return [("PRINTF", visited_arg, arg_type)]
        
        if node.name.name not in self.functions:
            raise NameException(node.name.name + " is undefined")
        self.current_type = self.functions[node.name.name]["returned_type"]
        
        def collect_args(args):
            result = []
            func_args = self.functions[node.name.name]["args"]
            if len(func_args) != len(args):
                raise SyntaxException("{0}: bad number of arguments".format(node.name.name))
            for index, arg in enumerate(args):
                visited_arg = self.visit(arg)
                if func_args[index][1] != self.current_type:
                    raise TypeException(
                            "{0}: bad argument type at index {1}, got {2}, expected {3}".format(
                            node.name.name, index, self.current_type, func_args[index][1]))
                result += visited_arg
            return result
        
        return (collect_args(node.args.exprs) 
                if node.args else []) + [("invokestatic", node.name.name)]
    
    def visit_ArrayRef(self, node):
        visited_array = self.visit(node.name)
        node_type_name = self.current_type
        try:
            node_type_short_name = {
                "char[]": "c",
                "int[]": "i",
                "float[]": "f"              
            }[node_type_name]
        except:
            node_type_short_name = "a"
        result = visited_array + self.visit(node.subscript) + [
                                            (node_type_short_name + "aload", None)]
        self.current_type = node_type_name[:-2]
        return result
 
    def visit_StructRef(self, node):
        visited_node_name = self.visit(node.name)
        struct_type = self.current_type 
        fields = filter(lambda x: x[0] == node.field.name, self.structs[self.current_type])
        if len(fields) == 0:
            raise NameException("{0} has no field {1}".format(struct_type, node.field.name))
        
        field_type = fields[0][0]
        self.class_field_name = (struct_type, field_type)
        self.current_type = fields[0][1]
        return visited_node_name + [("getfield", struct_type, node.field.name, field_type)]

    def visit_Assignment(self, node):        
        returned_get = self.visit(node.lvalue)
        extras = []
        if returned_get[-1][0] == "getstatic":
            lvalue_name = node.lvalue.name            
            if (lvalue_name not in self.locals and lvalue_name not in self.fields):
                raise NameException(lvalue_name + " not exists")
            lvalue_type = self.fields[lvalue_name][0]
            store_op = [("putstatic", lvalue_name)]
        elif returned_get[-1][0] == "getfield":
            lvalue_type = self.current_type
            extras = self.visit(node.lvalue.name)
            store_op = [("putfield", (self.class_field_name[0], 
                            self.class_field_name[1], lvalue_type))]
        elif returned_get[-1][0].endswith("aload"):
            lvalue_type = self.current_type
            lvalue_type_short_name = self.type_short_name(lvalue_type, True)
            extras = returned_get[:-1]
            store_op = [(lvalue_type_short_name + "astore", None)]
        elif returned_get[-1][0].endswith("load"):
            lvalue_name = node.lvalue.name            
            if (lvalue_name not in self.locals and lvalue_name not in self.fields):
                raise NameException(lvalue_name + " not exists")
            lvalue_type = self.locals[lvalue_name][0]
            lvalue_type_short_name = self.type_short_name(lvalue_type)
            store_op = [(lvalue_type_short_name + "store", lvalue_name)] 
        else:
            raise SyntaxException("{0} is not lvalue".format(lvalue_name))           
        self.current_type = lvalue_type
        visited_rvalue = self.visit_and_prepare_conversion(node.rvalue, lvalue_type)        
        return extras + visited_rvalue + store_op;
    
    def visitCompoundDecl(self, node):              
        name, content = self.visit(node)
        init = []
        self.error_if_exists_locally(name)
          
        if isinstance(node.type, c_ast.ArrayDecl):
            store_type_name = self.type_short_name(content, True)
            if node.type.dim:
                if node.init:
                    raise SyntaxException("Cannot initiate array - syntax not supported")
                init += self.visit(node.type.dim) 
                init += [("newarray" if isinstance(node.type.type.type, c_ast.IdentifierType) 
                         else "anewarray", content[:-2]),
                    (store_type_name + "store", name)]
            elif (node.init and isinstance(node.init, c_ast.Constant) 
                            and node.init.type == "string"):
                        init += self.visit(node.init)
                        init += [("invokevirtual", "toCharArray")]
                        init += [("astore", name)]
#             else:
#                 raise SyntaxException("Array size missing")
        else:
            store_type_name = self.type_short_name(content)
            if node.init:   
                init += self.visit_and_prepare_conversion(node.init, content)
                init += [(store_type_name + "store", name)]    
            elif (isinstance(node.type, c_ast.TypeDecl) 
                    and node.type.type and isinstance(node.type.type, c_ast.Struct)):
                init += [
                    ("new", content),
                    ("dup", None),
                    ("invoke", content + "/<init>()V"),
                    ("astore", name)
                ]   
        self.locals[name] = (content,)
        self.current_type = content
        return init
        
    def visit_Compound(self, node):
        old_locals = dict(self.locals)
        
        def sumVisited(a, b):
            if isinstance(b, c_ast.Decl):
                return a + self.visitCompoundDecl(b)
            else:
                visited_b = self.visit(b)
                if isinstance(visited_b, list):
                    return a + visited_b
                else:
                    return a
        
        result = [(reduce(sumVisited, node.block_items, []), 
                   dict(self.locals))] if node.block_items else [([], dict())]
        self.locals = old_locals
        return result
 
    def visit_UnaryOp(self, node):
        if node.op == "-":
            result = self.visit(node.expr)
            result_type = self.current_type
            if result_type not in ("float", "int"):
                raise TypeException("Negation not allowed for type: " + result_type)
            
            return result + [("fneg" if self.current_type == "float" else "ineg", None)]
        elif node.op in ("++", "--"):
            return self.visit(c_ast.Assignment("=", node.expr, c_ast.BinaryOp(node.op[0], 
                node.expr, c_ast.Constant("int", "1"))))
        else:
            raise SyntaxException(node.op + ": unknown unary operator")
 
    def visit_BinaryOp(self, node):
        lval_str = self.visit(node.left)
        lval_type = self.current_type
        rval_str = self.visit(node.right)
        rval_type = self.current_type
            
        if (lval_type not in ("float", "int", "char") 
                or rval_type not in ("float", "int", "char")):
            raise TypeException("Operation '{0}' not allowed for types: {1}, {2}"
                                .format(node.op, lval_type, rval_type)) 
            
        if lval_type == "float" and rval_type != "float":
            rval_str += [("i2f", None)]
        elif rval_type == "float" and lval_type != "float":
            lval_str += [("i2f", None)]
        type_mark = "f" if lval_type == "float" or rval_type == "float" else "i"
        self.current_type = "float" if type_mark == "f" else "int"
            
        if node.op in ("+", "-", "*", "/"):   
            op_instr = {
                "+": "add",
                "-": "sub",
                "*": "mul",
                "/": "div"        
            }[node.op] 
                                
            return lval_str + rval_str + [(type_mark + op_instr, None)]
        else:
            return [lval_str, rval_str, node.op]
 
    def visit_Return(self, node):
        return_type_name = self.type_short_name(self.current_return_type)
        return (self.visit(node.expr) if node.expr 
                else []) + [(return_type_name + "return", None)] 
 
    def visit_Break(self, node):
        return [("BREAK")]
 
    def visit_If(self, node):
        condition = (node.cond if isinstance(node.cond, c_ast.BinaryOp) 
                     else c_ast.BinaryOp("!=", node.cond, c_ast.Constant("int", "0")))
        return [('IF', {
            "cond": self.visit(condition),
            "true": self.visit(node.iftrue if isinstance(node.iftrue, c_ast.Compound) 
                                  else c_ast.Compound([node.iftrue])),
            "false": self.visit(node.iffalse if isinstance(node.iffalse, c_ast.Compound) 
                                  else c_ast.Compound([node.iffalse]))
        })]
 
    def visit_For(self, node):
        condition = (node.cond if isinstance(node.cond, c_ast.BinaryOp) 
                     else c_ast.BinaryOp("!=", node.cond, c_ast.Constant("int", "0")))
        return [('FOR', {
            "init": self.visit(node.init),
            "cond": self.visit(condition),
            "next": self.visit(node.next),
            "content": self.visit(node.stmt if isinstance(node.stmt, c_ast.Compound) 
                                  else c_ast.Compound([node.stmt]))
        })]
 
    def visit_While(self, node):
        condition = (node.cond if isinstance(node.cond, c_ast.BinaryOp) 
                     else c_ast.BinaryOp("!=", node.cond, c_ast.Constant("int", "0")))
        return [('WHILE', {
            "cond": self.visit(condition),
            "content": self.visit(node.stmt if isinstance(node.stmt, c_ast.Compound) 
                                  else c_ast.Compound([node.stmt]))
        })]
 
    def visit_Switch(self, node):
        return [('SWITCH', {
            "cond": self.visit(node.cond),
            "content": self.visit(node.stmt)
        })]
 
    def visit_Case(self, node):
        return [("CASE", {
            "label": self.visit(node.expr),
            "content": self.visit(node.stmts if isinstance(node.stmts, c_ast.Compound) 
                                  else c_ast.Compound(node.stmts))
        })]
 
    def visit_Default(self, node):
        return [("DEFAULT", {
            "content": self.visit(node.stmts if isinstance(node.stmts, c_ast.Compound) 
                                  else c_ast.Compound(node.stmts))
        })]
