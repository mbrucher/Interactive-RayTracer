
# Matthieu Brucher
# Last Change : 2007-11-20 17:09


def py2pyc_build_function(target, source, env):
    " call python to convert py to pyc "

    import py_compile
    exit_code=0

    for i in range(0,len(source)):
        try:
            py_compile.compile(source[i].abspath,target[i].abspath)
        except:
            # cannot compile file
            exit_code=-1

    return exit_code

def py2pyc_emitter(target, source, env):
    target=[]
    for file in source:
        target.append(file.name+'c')

    return target,source 
