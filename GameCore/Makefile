CC=gcc
CXX=g++

INC= "-I../"

CFLAGS= $(INC) -Wall -g -O2

CPPFLAGS=

CXXFLAGS= $(INC) -Wall -g -O2 -std=c++11 -fPIC

CXXPROGS=

OUT_LIB= GameCore.so

LIB= ../Util/Util.so


OB=$(wildcard *.cpp)

OBJS=$(patsubst main.o, , $(patsubst %.cpp, %.o, $(OB)))

all: $(OBJS) prog $(OUT_LIB)

clean:
	rm -f $(OBJS)
	rm -f $(CXXPROGS)
	rm -f $(OUT_LIB)

$(CXXPROGS): %: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(INC) $(OBJS) $< -o $@

prog: $(OBJS) $(CXXPROGS)

$(OUT_LIB):
	$(CXX) -shared $(CXXFLAGS) $(CPPFLAGS) $(INC) $(OBJS) $(LIB) $< -o $@
