#dumb verison int the future we need to create the dependecies

# Define variables (Not necessary)
CXX = g++
CXXFLAGS = -IInclude -IShaders
LIBS = -lglew32 -lopengl32 -lglfw3dll -lfreeglut -lglu32

# What to run when you just type `make`
all: Simple run clean

# $^ = $(wildcard Src/*.cpp) $(wildcard Src/Shapes/*.cpp)
# $@ = Simple   
Simple: $(wildcard Src/*.cpp) $(wildcard Src/Shapes/*.cpp)
	$(CXX) $^ -o $@  $(CXXFLAGS) $(LIBS)

run: Simple.exe
	./$^

clean: 
	rm -f Simple

# To tell make that `make clean` clean here is not a actual file
.PHONY: clean
