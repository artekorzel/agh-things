#!/usr/bin/env python

import sys, c4jvm.jasmin_translator, c4jvm.bytecode_generator, subprocess, pycparser

class ParseException(Exception):
    pass

def generate_class(out_path, j_filename):
    p = subprocess.Popen(["java", "-jar", "jasmin.jar", "-d", out_path, j_filename],
                         stdout=subprocess.PIPE)
    stdoutdata = p.communicate()[0]
    if not stdoutdata.startswith("Generated:"):
        raise ParseException("Generating class from file {0} failed:\n{1}"
                             .format(j_filename, stdoutdata))

def parse(c_source_filename, out_path, classname):    
    jasmin_tr = c4jvm.jasmin_translator.JasminTranslator(c_source_filename, classname)
    jasmin_tr.generate_fields()
    jasmin_tr.generate_structs()
    jasmin_tr.generate_methods()
    
    for struct in jasmin_tr.structs_output:
        j_filename = out_path + '/' + struct[0] + '.j'
        with open(j_filename, 'w') as f:
            f.write(struct[1])
        generate_class(out_path, j_filename)
        
    j_filename = out_path + '/' + classname + '.j'
    with open(j_filename, 'w') as f:
        f.write(jasmin_tr.class_header + '\n')
        f.write(jasmin_tr.static_block + '\n')
        for method in jasmin_tr.method_output:        
            f.write(method + '\n')
    generate_class(out_path, j_filename)
    
if __name__ == '__main__':
#     if len(sys.argv) == 4:
#         parse(sys.argv[1], sys.argv[2], sys.argv[3])
        bt = c4jvm.bytecode_generator.BytecodeGenerator("Buszko")
        bt.visit(pycparser.parse_file(sys.argv[1], use_cpp=True))
        print(bt.show())
#     else:
#        print("Usage: {0} <C source file> <result path> <main class name>".format(sys.argv[0]))