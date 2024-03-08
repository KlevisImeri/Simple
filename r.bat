del a.exe
g++ Src/*.cpp Src/Shapes/*.cpp -IInclude -IShaders -lglew32 -lopengl32 -lglfw3dll -lfreeglut -lglu32
a.exe


@REM -I./Include > this is to include the header files located in the include folder
@REM -lglew32 -l
@REM :qopengl32 -lglfw3dll -lfreeglut -lglu32 > this are all the lib that are needed
