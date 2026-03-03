include(Platform/AIX-XL)
__aix_compiler_xl(CXX)

# -qhalt=s       = Halt on severe any messages
string(APPEND CMAKE_CXX_FLAGS_INIT " -qhalt=s")
