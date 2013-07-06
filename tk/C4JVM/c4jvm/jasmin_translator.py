'''
Created on 05-06-2013

@author: filip
'''

import pycparser, bytecode_generator

class JasminTranslator(object):
    def __init__(self, filename, parent_class):
        self.structs_output = [] 
        self.method_output = []
        self.method_name_ref = {}
        self.class_header = ''
        self.fields = []
        self.static_block = ''
        self.parent_class = parent_class
        self.ast = pycparser.parse_file(filename, use_cpp=True)
        self.bytecode_gen = bytecode_generator.BytecodeGenerator(parent_class)
        self.bytecode_gen.visit(self.ast)
        self.label_num = 1
        self.true_false = 0
        self.or_num = 1
        
    def generate_structs(self):
        for struct in self.bytecode_gen.structs: 
            output = ''
            name = struct
            output += '.class public {0}\n.super java/lang/Object\n\n'.format(name.capitalize())
            for argument in self.bytecode_gen.structs[name]:
                output += '.field public ' + argument[0] + " " + self.get_type(argument[1]) + '\n' 
            output += '''\n.method public <init>()V    
    aload_0
    invokenonvirtual java/lang/Object/<init>()V
    return
.end method '''
            self.structs_output.append((name.capitalize(), output))
            
    def generate_methods(self):
        self.class_header = '.class public ' + self.parent_class + '\n.super java/lang/Object\n'
        for function in self.bytecode_gen.functions:
            output = ''
            locals = []
            name = ''
            index = 0
            jump_num = 1
            if(function == 'main'):
                index = 1
                output = '.method public static main([Ljava/lang/String;)V\n\t.limit locals 1000\n\t.limit stack 1000\n'
            else:
                output = '.method public static ' + function + '('
                for arg in self.bytecode_gen.functions[function]['args']:                    
                    type = self.get_type(arg[1])
                    locals.append((arg[0], type, index))
                    index += 1
                    name += type
                    output += type                
                output += ')'
                returned_type = self.bytecode_gen.functions[function]['returned_type']
                output += self.get_type(returned_type) + '\n'
                
                output += '\t.limit locals 1000\n\t.limit stack 1000\n'            
            
            compound = self.bytecode_gen.functions[function]['content']
            for local in compound[1]:
                if(self.get_index(locals, local) == -1):
                    locals.append((local, self.get_type(compound[1][local][0]), index))
                    index += 1
                
            output += self.parse_compound(compound, locals, 1)
            output += '.end method'
            
            self.method_output.append(output) 
    
    def parse_compound(self, compound, locals, label_num):
        lab_num = label_num
        tmp_output = ''
        curr_parsing = ''        
        for line in compound[0]:
            if isinstance(line, type([])):
                tmp_output += self.parse_return(line, locals)
            elif line[0] == 'IF':
                tmp_output += self.parse_if(line[1], locals, lab_num)
                lab_num += 1
            elif line[0] == 'FOR':
                tmp_output += self.parse_for(line[1], locals, lab_num)
                lab_num += 1
            elif line[0] == 'SWITCH':
                tmp_output += self.parse_switch(line[1], locals, lab_num)
                lab_num += 1
            elif line[0] == 'WHILE':
                tmp_output += self.parse_while(line[1], locals, lab_num)
                lab_num += 1
            elif line[0] == 'PRINTF':
                tmp_output += '\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n'
                tmp_output += self.parse_compound([line[1]], locals, label_num)
                tmp_output += '\tinvokevirtual java/io/PrintStream/print(' + self.get_type(line[2]) + ')V\n'
                    
            elif line[0] == 'newarray':
                tmp_output += '\t' + line[0] + ' ' + line[1] + '\n'
            elif line[0] == 'anewarray':
                tmp_output += '\t' + line[0] + ' ' + line[1].capitalize() + '\n'
            elif line[0] == 'invokestatic':
                tmp_output += '\t' + line[0] + ' ' + self.get_method_ref(line[1]) + '\n'
            elif line[0] == 'putstatic':
                tmp_output += '\t' + line[0] + ' ' + self.get_field_name(line[1]) + '\n'
            elif line[0] == 'getstatic':
                if line[1] == 'System.out':
                    tmp_output += '\t' + line[0] + ' java/lang/System/out Ljava/io/PrintStream;' 
                else:
                    tmp_output += '\t' + line[0] + ' ' + self.get_field_name(line[1]) + '\n'
            elif line[0] == 'invokevirtual':
                tmp_output += '\t' + line[0] + ' '
                if line[1] == 'toCharArray':
                    tmp_output += 'java/lang/String/toCharArray()[C\n'
            elif line[0] == 'getfield':
                tmp_output += '\t' + line[0] + ' ' + line[1].capitalize() + '/' + line[2] + ' ' + self.get_struct_field_type(line[1], line[2]) + '\n'
            elif line[0] == 'putfield':
                tmp_output += '\t' + line[0] + ' ' + line[1][0].capitalize() + '/' + line[1][1] + ' ' + self.get_type(line[1][2]) + '\n'
            elif line[0] == 'new':
                tmp_output += '\t' + line[0] + ' ' + line[1].capitalize() + '\n'
            elif line[0] == 'invoke':
                tmp_output += '\tinvokespecial ' + self.prepare_init_call(line[1]) + '\n'
            elif line[1] is None:
                tmp_output += '\t' + line[0] + '\n'
            elif isinstance(line[1], int):
                tmp_output += '\t' + line[0] + ' ' + str(self.bytecode_gen.constants[line[1]][1]) + '\n'
            elif isinstance(line[1], str):
                tmp_output += '\t' + line[0] + ' ' + str(self.get_index(locals, line[1])) + '\n'
        return tmp_output
    
    def prepare_init_call(self, line):
        tmp_output = ''
        splitted = line.split('/')
        splitted[-2] = splitted[-2].capitalize()
        for part in splitted:
            tmp_output += part + '/'
        return tmp_output[:-1]
    
    def get_struct_field_type(self, struct_name, field_name):
        for field in self.bytecode_gen.structs[struct_name]:
            if field[0] == field_name:
                return self.get_type(field[1])
    
    def parse_while(self, compound, locals, label_num):
        tmp_output = ''
        content = compound['content']
        cond = compound['cond']
        tmp_output += 'WHILE' + str(label_num) + ':\n'
        tmp_output += self.parse_cond(cond, locals, label_num, '', 'WHILE')  
        tmp_output += self.parse_compound(content[0], locals, label_num + 1)
        tmp_output += '\tgoto WHILE' + str(label_num) + '\nENDWHILE' + str(label_num) + ':\n'
        
        return tmp_output
        
        
    def parse_while_comp(self, comp, label_num):
        tmp_output = ''
        if comp == '<=':            
            tmp_output += '\tif_icmpgt ' + 'ENDWHILE' + str(label_num) + "\n"
        elif comp == '>=':            
            tmp_output += '\tif_icmplt ' + 'ENDWHILE' + str(label_num) + "\n"
        elif comp == '<':            
            tmp_output += '\tif_icmpge ' + 'ENDWHILE' + str(label_num) + "\n"
        elif comp == '>':            
            tmp_output += '\tif_icmple ' + 'ENDWHILE' + str(label_num) + "\n"
        return tmp_output
    
    def get_field_name(self, name):
        tmp_output = self.parent_class + '/' + name + ' '
        tmp_output += self.get_field_type(name)
        return tmp_output
        
    def get_field_type(self, name):
        for field in self.fields:
            if(field[0] == name):
                return field[1]
    
    def parse_switch_compound(self, compound, locals, label_num):
        tmp_output = ''
        curr_parsing = ''        
        for line in compound[0]:
            if isinstance(line, type([])):
                tmp_output += self.parse_return(line, locals)
            elif line[0] == 'IF':
                tmp_output += self.parse_if(line[1], locals, label_num)
            elif line[0] == 'FOR':
                tmp_output += self.parse_for(line[1], locals, label_num)
            elif line[0] == 'SWITCH':
                tmp_output += self.parse_switch(line[1], locals, label_num)
            elif line == 'BREAK':
                tmp_output += '\tgoto ENDSWITCH' + str(label_num -1) + '\n'
            elif line[1] is None:
                tmp_output += '\t' + line[0] + '\n'
            elif line[0] == 'invokestatic':
                tmp_output += '\t' + line[0] + ' ' + self.get_method_ref(line[1])
            elif isinstance(line[1], int):
                tmp_output += '\t' + line[0] + ' ' + str(self.bytecode_gen.constants[line[1]][1]) + '\n'
            elif isinstance(line[1], str):
                tmp_output += '\t' + line[0] + ' ' + str(self.get_index(locals, line[1])) + '\n'
        return tmp_output
    
    def get_method_ref(self, name):
        return self.method_name_ref[name]
    
    def parse_return(self, return_body, locals):
        tmp_output = ''
        for line in return_body:
            if line[1] is None:
                tmp_output += '\t' + line[0] + '\n'
            elif isinstance(line[1], int):
                tmp_output += '\t' + line[0] + ' ' + str(self.bytecode_gen.constants[line[1]][1]) + '\n'
            elif isinstance(line[1], str):
                tmp_output += '\t' + line[0] + ' ' + str(self.get_index(locals, line[1])) + '\n'        
        return tmp_output
    
    def parse_switch(self, line, locals, label_num):
        tmp_output = ''
        content = line['content'][0][0]
        cond = line['cond']
        tmp_output += self.parse_compound([cond], locals, label_num)
        tmp_output += '\tlookupswitch\n'
        tmp_output += self.get_switch_labels(content, label_num)
        tmp_output += self.parse_switch_contents(content, locals, label_num)
        tmp_output += 'ENDSWITCH' + str(label_num) + ':\n'
        return tmp_output
    
    def get_switch_labels(self, line, label_num):
        tmp_output = ''
        switch_label_num = 1
        for case in line:
            if case[0] == 'CASE':
                label_body = case[1]['label'][0]
                tmp_output += '\t' + str(self.get_const_value(label_body[1])) + ' : SWITCH' + str(label_num) + str(switch_label_num) + '\n' 
            elif case[0] == 'DEFAULT':
                tmp_output += '\tdefault : SWITCH' + str(label_num) + str(switch_label_num) + '\n'
            switch_label_num += 1
        return tmp_output
    
    def parse_switch_contents(self, compound, locals, label_num):
        tmp_output = ''
        switch_label_num = 1
        
        for case in compound:
            content = case[1]['content']
            case_locals = content[0][1]
            for local in case_locals:
                if(self.get_index(locals, local) == -1):
                    locals.append((local, self.get_type(case_locals[local][0]), len(locals) + 1))
            tmp_output += 'SWITCH' + str(label_num) + str(switch_label_num) + ':\n'
            tmp_output += self.parse_switch_compound([content[0][0]], locals, label_num + 1)
            switch_label_num += 1
        
        return tmp_output
    
    def get_const_value(self, index):
        return self.bytecode_gen.constants[index][1]
    
    def parse_for(self, line, locals, label_num):
        tmp_output = ''
        
        init = line['init']
        cond = line['cond']
        next = line['next']
        content = line['content']
        for_locals = content[0][1]
        for local in for_locals:
            if(self.get_index(locals, local) == -1):
                locals.append((local, self.get_type(for_locals[local][0]), len(locals) + 1))
        
        tmp_output += self.parse_init(init, locals)
        tmp_output += 'FOR' + str(label_num) + ':\n'
        tmp_output += self.parse_compound([cond[0]], locals, label_num)
        tmp_output += self.parse_compound([cond[1]], locals, label_num)
        tmp_output += self.parse_comp_for(cond[2], label_num)
        
        tmp_output += self.parse_compound(content[0], locals, label_num+1)
        
        tmp_output += self.parse_next(next, locals, label_num)
        tmp_output += '\tgoto FOR' + str(label_num) + '\n'
        tmp_output += 'ENDFOR' + str(label_num) + ':\n'
        
        return tmp_output
    
    def parse_init(self, init, locals):
        tmp_output = ''
        for line in init:
            if isinstance(line[1], int):
                tmp_output += '\t' + line[0] + ' ' + str(self.bytecode_gen.constants[line[1]][1]) + '\n'
            elif isinstance(line[1], str):
                tmp_output += '\t' + line[0] + ' ' + str(self.get_index(locals, line[1])) + '\n'
        return tmp_output
    
    def parse_comp_for(self, comp, label_num):
        tmp_output = ''
        
        if comp == '<=':            
            tmp_output += '\tif_icmpgt ' + 'ENDFOR' + str(label_num) + "\n"
        elif comp == '>=':            
            tmp_output += '\tif_icmplt ' + 'ENDFOR' + str(label_num) + "\n"
        elif comp == '<':            
            tmp_output += '\tif_icmpge ' + 'ENDFOR' + str(label_num) + "\n"
        elif comp == '>':            
            tmp_output += '\tif_icmple ' + 'ENDFOR' + str(label_num) + "\n"
        
        return tmp_output
    
    def parse_next(self, next, locals, label_num):
        tmp_output = ''
        for line in next:
            if isinstance(line[1], int):
                tmp_output += '\t' + line[0] + ' ' + str(self.bytecode_gen.constants[line[1]][1]) + '\n'
            elif isinstance(line[1], str):
                tmp_output += '\t' + line[0] + ' ' + str(self.get_index(locals, line[1])) + '\n'
            elif line[1] is None:
                tmp_output += '\t' + line[0] + '\n'    
        return tmp_output
    
    def parse_if(self, line, locals, label_num):
        tmp_output = ''
        if_true = line['true']
        if_false = line['false']
        true_locals = []
        false_locals = []
        cond = line['cond']
        first = cond[0]
        second = cond[1]
        comparison = cond[2]
        
        true_locals = if_true[0][1]
        if if_false:
            false_locals = if_false[0][1]
        for local in true_locals:
            if(self.get_index(locals, local) == -1):
                locals.append((local, self.get_type(true_locals[local][0]), len(locals) + 1))
        for local in false_locals:
            if(self.get_index(locals, local) == -1):
                locals.append((local, self.get_type(false_locals[local][0]), len(locals) + 1))        
        
        tmp_output += self.parse_cond(cond, locals, label_num, '')
        tmp_output += 'BODY' + str(label_num) + ':\n'
        #'\t goto ELSE' + str(label_num) + '\n' +
        tmp_output += self.parse_compound(if_true[0], locals, label_num+1)
        if not if_false:
            tmp_output += 'ELSE' + str(label_num) + ':\n'
        elif if_false:
            tmp_output += '\tgoto ENDELSE' + str(label_num) + '\n'
            tmp_output += 'ELSE' + str(label_num) + ':\n'
            tmp_output += self.parse_compound(if_false[0], locals, label_num+1)
            tmp_output += 'ENDELSE' + str(label_num) + ':\n'
        return tmp_output
    
    def parse_cond(self, cond, locals, label_num, from_parse, parent_parse = ''):
        tmp_output = ''
        
        if cond[2] == '||':
            tmp_output += self.parse_cond(cond[0], locals, label_num, 'OR', parent_parse )
            tmp_output += self.parse_cond(cond[1], locals, label_num, 'OR', parent_parse )            
        elif cond[2] == '&&':
            tmp_output += self.parse_cond(cond[0], locals, label_num, 'AND', parent_parse)
            tmp_output += self.parse_cond(cond[1], locals, label_num, 'AND', parent_parse)
        else:
            tmp_output += self.parse_compound([cond[0]], locals, label_num)
            tmp_output += self.parse_compound([cond[1]], locals, label_num)
            tmp_output += self.parse_comp(cond[2], label_num)
            if from_parse == 'OR':
                tmp_output +=  'OR' + str(self.or_num) + '\n\tgoto BODY' + str(label_num) + '\nOR' + str(self.or_num) + ':\n'
                self.or_num += 1
            else:
                if(parent_parse == ''):
                    tmp_output += 'ELSE' + str(label_num) + '\n'
                elif parent_parse == 'WHILE':
                    tmp_output += 'ENDWHILE' + str(label_num) + '\n'
        return tmp_output
                
    def parse_comp(self, comp, label_num):
        tmp_output = ''
        if comp == '==':
            tmp_output += '\tif_icmpne '
        elif comp == '<=':            
            tmp_output += '\tif_icmpgt '
        elif comp == '>=':            
            tmp_output += '\tif_icmplt '
        elif comp == '!=':            
            tmp_output += '\tif_icmpeq '
        elif comp == '<':            
            tmp_output += '\tif_icmpge '
        elif comp == '>':            
            tmp_output += '\tif_icmple '
        return tmp_output
    
    def generate_fields(self):
        index = 1
        for function in self.bytecode_gen.functions:
            if function != 'main':
                returned_type = self.bytecode_gen.functions[function]['returned_type']
                name = self.parent_class + '/' + function + '('
                for arg in self.bytecode_gen.functions[function]['args']:
                    name += self.get_type(arg[1])
                name += ')'
                name += self.get_type(returned_type)
                self.method_name_ref[function] = name
        
        for field in self.bytecode_gen.fields:
            field_prop = self.bytecode_gen.fields[field]
            self.static_block += '.field public static ' + field 
            self.static_block += ' ' + self.get_type(field_prop[0]) + '\n'
            self.fields.append((field, self.get_type(field_prop[0])))
            
        self.static_block += '\n.method static public <clinit>()V\n\t.limit locals 1000\n\t.limit stack 1000\n'
        for field in self.bytecode_gen.fields:
            field_prop = self.bytecode_gen.fields[field]
            if field_prop[1]:
                self.static_block += self.parse_compound([field_prop[1]], [], 0)
        self.static_block += '\treturn\n.end method\n'
        
                       
    def get_index(self, locals, name):
        for local in locals:
            if local[0] == name:
                return local[2]        
        return -1       
            
    def get_type(self, arg):
        type = ''
        if(len(arg.split('[')) == 2):
            type = '['
        if(arg.split('[')[0] == 'int'):
            type += 'I'
        elif(arg.split('[')[0] == 'char'):
            type += 'C'
        elif(arg.split('[')[0] == 'float'):
            type += 'F'
        elif(arg == 'void'):
            type += 'V'
        elif(arg == 'string'):
            type += 'Ljava/lang/String;'
        else:
            struct_name = arg.split('[')[0]
            type += 'L' + struct_name.capitalize()+';'
        return type