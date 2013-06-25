
import os
import os.path
import sys

opts = Variables('custom.py')
opts.Add(BoolVariable('debug', 'Set to build for debug', True))
opts.Add(BoolVariable('optimized', 'Set to build for optimization', False))
opts.Add(BoolVariable('profile', 'Set to build for profiling', False))
opts.Add(PathVariable('prefix', 'Sets the path where the programs and libs will be installed', os.getcwd()))
opts.Add(BoolVariable('parallel', 'Use parallel library (TBB)', False))
opts.Add(PathVariable('boostdir', 'Boost folder path', "."))
opts.Add(PathVariable('eigendir', 'Eigen folder path', "."))
opts.Add(PathVariable('swigdir', 'Swig folder path', "."))
opts.Add('cflags', 'Set the C++ flags', '')
opts.Add('ldflags', 'Set the linker flags', '')
opts.Add('tools', 'Set the tool set to use', '')
opts.Add('topdir', 'Set the location of the tool set', '')
opts.Add('optlevel', 'Optimization level (1, 2 or 3', '1')

env = Environment(options = opts,
                  BINDIR = "%s/bin" % '$prefix',
                  INCDIR = "%s/include" % '$prefix',
                  LIBDIR = "%s/lib" % '$prefix',
                  tools = ["default", "doxygen"],
                  toolpath = '.',
      ENV=os.environ
                  )

opts.Save('custom.py', env)

#if env.WhereIs('doxygen') is not None:
#  env.Doxygen("irt.doxyfile")

env['boost_suffix'] = ''
Export('env')

if env['tools'] != '':
  env = SConscript('%s-%s.scons' % (env['tools'], sys.platform))
elif sys.platform == "win32":
  env = SConscript('msvc-win32.scons')
elif sys.platform == "linux2":
  env = SConscript('gcc-linux2.scons')
elif sys.platform == "darwin":
  env = SConscript('gcc-darwin.scons')

if env["swigdir"] != "":
  env['SWIG'] = env["swigdir"] + "/swig.exe"

if env['parallel'] == True:
  if sys.platform == "win32":
    env = SConscript('tbb-win32.scons')
  elif sys.platform == "linux2":
    env = SConscript('tbb-linux2.scons')
  elif sys.platform == "darwin":
    env = SConscript('tbb-darwin.scons')

Help(opts.GenerateHelpText(env))

import distutils.sysconfig
import numpy
env.Append(CPPPATH=[os.getcwd(), distutils.sysconfig.get_python_inc(), numpy.get_include(), env["eigendir"], env["boostdir"]])
if sys.platform == "win32":
  env.Append(CPPPATH=os.environ["INCLUDE"].split(";"))
else:
  env.Append(CPPPATH=os.environ["INCLUDE"].split(":"))
if sys.platform == "win32":
  env.Append(LIBPATH=[distutils.sysconfig.get_python_lib(standard_lib=True) + os.sep + '..' + os.sep + "libs", '.', ])
elif sys.platform == "darwin":
  env.Append(LIBPATH=[distutils.sysconfig.get_python_lib(standard_lib=True) + os.sep + 'config', '.', ])
else:
  env.Append(LIBPATH=[distutils.sysconfig.get_python_lib(standard_lib=True), '.', ])

if env['cflags']:
  env.Append(CCFLAGS=env['cflags'])
if env['ldflags']:
  env.Append(LINKFLAGS=env['ldflags'])

import python_compile

Py2PycBld = env.Builder(action = python_compile.py2pyc_build_function,
                    suffix = '.pyc',
                    src_suffix = '.py',
                    emitter = python_compile.py2pyc_emitter)

env['BUILDERS']['Python'] = Py2PycBld
env.Append(SWIGFLAGS=['-threads'])

Export('env')
env.SConscript(['IRT/SConstruct', ], variant_dir='build', duplicate=0)
env.SConscript(['tests/SConstruct', ], variant_dir='build_test', duplicate=0)
