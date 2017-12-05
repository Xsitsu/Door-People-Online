CC=gcc
CXX=g++

INC= "-I../"

CFLAGS= $(INC) -Wall -g -O2

CPPFLAGS=

CXXFLAGS= $(INC) -Wall -g -O2 -std=c++11 -fPIC

CXXPROGS= main

OUT_LIB= 

LIB= ../Util/Util.so ../Network/Network.so ../GameCore/GameCore.so


OB=$(wildcard ./*.cpp)

OBJS=$(patsubst main.o, , $(patsubst %.cpp, %.o, $(OB)))

OBJS=	gameserver.o \
		

all: $(OBJS) prog $(OUT_LIB)

clean:
	rm -f $(OBJS)
	rm -f $(CXXPROGS)
	rm -f $(OUT_LIB)
	rm -f *.o
	rm -f *.so
	rm -f *~
	rm -f server

$(CXXPROGS): %: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(INC) $(OBJS) $(LIB) $< -o server

prog: $(OBJS) $(CXXPROGS)

$(OUT_LIB):
	$(CXX) -shared $(CXXFLAGS) $(CPPFLAGS) $(INC) $(OBJS) $(LIB) $< -o $(OUT_LIB)



