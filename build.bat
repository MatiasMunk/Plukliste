@echo off

set CompilerFlags=-MTd /DWIN32
set LinkerFlags=/EHsc

IF NOT EXIST build mkdir build
pushd build
cl %CompilerFlags% ../code/main.cpp /I../include %LinkerFlags%
popd