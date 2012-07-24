CXXFLAGS=-std=c++0x -Wall -Wextra -Weffc++ $(shell pkg-config --cflags glib-2.0)
OBJ=read.o particles.o
LDFLAGS=$(shell pkg-config --libs glib-2.0) -lhdf5_cpp -lhdf5

all: optimized $(OBJ)

optimized: read.o particles.o
	$(CXX) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJ) optimized
