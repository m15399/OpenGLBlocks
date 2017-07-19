
INCLUDES = -L /usr/lib -L /opt/vc/lib -L /usr/local/lib -lbcm_host -lGLESv2 -lEGL -I /usr/include -I /usr/local/include -I /opt/vc/include -I /opt/vc/include/interface/vcos/pthreads -I /opt/vc/include/interface/vmcs_host/linux 

all:
	g++ -Wall -g $(INCLUDES) `sdl2-config --cflags --libs` --std=c++11 *.cpp 
