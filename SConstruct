# -*- python -*-

env = Environment()

#env["CXX"] = "/s/gcc-4.6.1/bin/g++"
#env["CC"] = "/s/gcc-4.6.1/bin/gcc"

env.Append(CPPPATH=["#/include"])
env.Append(CCFLAGS=["-g", "-Wall", "-Wextra", "-Wnon-virtual-dtor", "-Werror"])
env.Append(CXXFLAGS=["-std=c++0x"])
env.Append(LINKFLAGS=["-g"])


sources = Split("""
    src/sexp.cc
""")

env.SharedLibrary("simple_sexp", sources)
