@echo off

set CompilerFlags=-MT /DWIN32 /EHsc /I../include
set LinkerFlags=/EHsc /link /LIBPATH:../lib libmariadb.lib

IF NOT EXIST build mkdir build
pushd build
cl %CompilerFlags% ../code/main.cpp ../code/export.cpp ../code/database.cpp ../code/util.cpp %LinkerFlags%
popd