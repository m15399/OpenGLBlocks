
INCLUDES = -L /usr/local/lib -I /usr/local/include

FILES = *.cpp
#FILES += GridGame/*.cpp

all:
	time clang++ -Wall -g $(INCLUDES) -lSDL2 -framework OpenGL -std=c++14 $(FILES)
