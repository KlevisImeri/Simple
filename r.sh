#--------------------------MAKE------------------------------#
make

#-------------------------WINDOWS----------------------------#
# rm a.exe
# g++ Src/*.cpp Src/Shapes/*.cpp -IInclude -IShaders -lglew32 -lopengl32 -lglfw3dll -lfreeglut -lglu32
# ./a.exe

# -I./Include > this is to include the header files located in the include folder
# -lglew32 -l
# -lglew32 -lopengl32 -lglfw3dll -lfreeglut -lglu32 > this are all the lib that are needed

#--------------------------LINUX-----------------------------#
# rm a.out   # Remove any existing executable (if present)
# g++ Src/*.cpp Src/Shapes/*.cpp -IInclude -IShaders -lGLEW -lGL -lglfw -lglut -lGLU -o a.out   # Compile the source files and link the necessary libraries, generating an executable named 'a.out'
# ./a.out    # Execute the compiled program

