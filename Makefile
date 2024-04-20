# Define variables
CXX = g++
CPP_FILES := $(shell find Simple/Src -name '*.cpp') $(wildcard Src/*.cpp)
INCLUDE_DIRS := $(shell find Simple/Include -type d)
CXXFLAGS := $(addprefix -I, $(INCLUDE_DIRS)) -IShaders
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
    LIBS = -lGLEW -lGL -lglfw -lglut -lGLU
else
    LIBS = -lglew32 -lopengl32 -lglfw3dll -lfreeglut -lglu32
endif
NAME = program

# What to run when you just type `make`
all: compile run clean

compile: 
	$(CXX) $(CPP_FILES) -o $(NAME) $(CXXFLAGS) $(LIBS) 

compileDebug: 
	$(CXX) $(CPP_FILES) -o $(NAME) $(CXXFLAGS) $(LIBS) -g -O0

gdb: compileDebug
	gdb ./$(NAME) -tui -x .gdb

val: compileDebug
	valgrind ./$(NAME) 

run: compile
	./$(NAME)

clean: 
	rm -f $(NAME).exe

# To tell make that `make clean` cleans here and is not an actual file
.PHONY: clean
