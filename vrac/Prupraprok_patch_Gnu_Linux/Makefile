SOURCES=$(wildcard *.cpp)
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES))
CXXFLAGS=-I /usr/include/SDL
LIBS=-lSDL -lSDL_image -lSDL_mixer -lz
BIN=splash
all: $(BIN)
$(BIN): $(OBJECTS)
	g++ -o $@ $(OBJECTS) $(CXXFLAGS) $(LIBS)
%.o: %.cpp
	g++ -c $< -o $@ $(CXXFLAGS)
clean:
	rm *.o $(BIN)
