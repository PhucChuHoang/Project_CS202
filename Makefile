CC = g++
CFLAGS = -std=c++17 -O2 -Wall -Wno-missing-braces
INCLUDES = -I include/
LIBS = -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
TARGET = crossingroad.exe

SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp,build/%.o,$(SRCS))

build/%.o: src/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 

build: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(TARGET)

default: 
	build

clean:
	rm -rf build/*.o ${TARGET}


