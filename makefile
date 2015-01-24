CC=g++
CFLAGS=-c -Wall
LDFLAGS=-framework GLUT -framework OpenGL
SOURCES=main.cpp map.cpp game.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=skyroad

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
