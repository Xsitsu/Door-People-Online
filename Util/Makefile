CC=gcc
CXX=g++

INC= "-I../"

CFLAGS= $(INC) -Wall -g -O2

CPPFLAGS=

CXXFLAGS= $(INC) -Wall -g -O2 -std=c++11 -fPIC

CXXPROGS=

OUT_LIB= Util.so

LIB= 


OB=$(wildcard *.cpp)

OBJS=$(patsubst main.o, , $(patsubst %.cpp, %.o, $(OB)))

all: $(OBJS) prog lib

clean:
	rm -f $(OBJS)
	rm -f $(CXXPROGS)
	rm -f $(OUT_LIB)

$(CXXPROGS): %: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(INC) $(OBJS) $< -o $@

prog: $(OBJS) $(CXXPROGS)

lib:
	$(CXX) -shared $(CXXFLAGS) $(CPPFLAGS) $(INC) $(OBJS) $(LIB) $< -o $(OUT_LIB)



