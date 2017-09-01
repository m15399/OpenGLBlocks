
CXX = clang++
INCLUDES = -I /usr/local/include
LIBRARIES = -L /usr/local/lib -lSDL2 -framework OpenGL
CXX_FLAGS = -Wall -g -std=c++14

IN_FILES = *.cpp
IN_FILES += GridGame/*.cpp


all: 
	$(CXX) $(INCLUDES) $(LIBRARIES) $(CXX_FLAGS) $(IN_FILES)
