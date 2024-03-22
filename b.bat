@REM This is if you are running the Clang LSP to get the compile_commands.json
del /s /q build
mkdir build
cd build
cmake -G "Unix Makefiles" -DCMAKE_CXX_COMPILER="D:/Program Files (x86)/C_compilers/mingw32/bin/g++.exe" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
make
move compile_commands.json ..


