CC = g++
CFLAGS = -std=c++17 -O2 -Wall -Wno-missing-braces
INCLUDES = -I include/
LIBS = -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
TARGET = crossingroad.exe

SRCS := $(wildcard src/*.cpp)
OBJS := $(subst src/,build/,$(patsubst %.cpp,%.o,$(SRCS)))

build/%.o: src/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(TARGET)

default: $(TARGET)

clean:
	rm -rf build/*.o ${TARGET}
