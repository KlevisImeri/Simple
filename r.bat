cmake --build build
build\simple.exe

@REM del a.exe
@REM g++ Src/*.cpp Src/Shapes/*.cpp -IInclude -IShaders -lglew32 -lopengl32 -lglfw3dll -lfreeglut -lglu32
@REM a.exe

@REM @REM -I./Include > this is to include the header files located in the include folder
@REM @REM -lglew32 -l
@REM @REM -lglew32 -lopengl32 -lglfw3dll -lfreeglut -lglu32 > this are all the lib that are needed
