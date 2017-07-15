
INCLUDES = -L /usr/local/lib -I /usr/local/include 

all:
	clang++ $(INCLUDES) -lSDL2 -framework OpenGL -std=c++14 *.cpp 