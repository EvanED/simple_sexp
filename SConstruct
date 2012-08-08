# -*- python -*-

env = Environment()

boost_inc_path = "/unsup/boost-1.49.0/include"
boost_lib_path = "/unsup/boost-1.49.0/lib"

env["CXX"] = "/s/gcc-4.6.1/bin/g++"
env["CC"] = "/s/gcc-4.6.1/bin/gcc"

env.Append(CPPPATH=["#/include", boost_inc_path])
env.Append(CCFLAGS=["-g", "-Wall", "-Wextra", "-Wnon-virtual-dtor"])
env.Append(CXXFLAGS=["-std=c++0x"])
env.Append(LINKFLAGS=["-g"])
env.Append(LIBPATH=[boost_lib_path])
env.Append(RPATH=[boost_lib_path])
env.Append(LIBS=["boost_regex"])

sources = Split("""
    src/sexp.cc
    src/parser.cc
""")

env.SharedLibrary("simple_sexp", sources)
env.Program("simple_sexp", sources)
