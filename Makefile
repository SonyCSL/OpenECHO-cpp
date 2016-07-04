# This is makefile for GNU Make and linux.
# confirm with g++ 4.8.x
CPP = g++
CFLAGS = -O2 -std=c++11 -Wall
LDFLAGS = 
LIBS = -lpthread
CPP_FILES = src/OpenECHO.cpp $(wildcard src/echo/*.cpp)
# TODO: fix this.
OBJ_DIR = obj
OBJS = $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))

PROGRAM = OpenECHOForCpp

all: $(PROGRAM)

$(PROGRAM): directories $(OBJS)
	$(CPP) $(OBJS) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $(PROGRAM)

obj/%.o: src/%.cpp
	$(CPP) $(CFLAGS) -c -o $@ $<

obj/%.o: src/echo/%.cpp
	$(CPP) $(CFLAGS) -c -o $@ $<

clean:;
	find . -type f -name "*.o" | xargs rm -f
	rm -r obj

PHONY: check-syntax
check-syntax:
	$(CPP) -Wall -fsyntax-only $(LDFLAGS) $(CFLAGS) $(LIBS) $(CHK_SOURCES)

PHONY: directories
directories: $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

