# -*- python -*-

env = Environment()

boost_inc_path = "/unsup/boost-1.49.0/include"

env["CXX"] = "/s/gcc-4.6.1/bin/g++"
env["CC"] = "/s/gcc-4.6.1/bin/gcc"

env.Append(CPPPATH=["#/include", boost_inc_path])
env.Append(CCFLAGS=["-g", "-Wall", "-Wextra", "-Wnon-virtual-dtor"])
env.Append(CXXFLAGS=["-std=c++0x"])
env.Append(LINKFLAGS=["-g"])


sources = Split("""
    src/sexp.cc
    src/parser.cc
""")

env.SharedLibrary("simple_sexp", sources)
