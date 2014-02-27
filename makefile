CFLAGS = -c -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer

all: a.out

a.out: main.o backend.o graphic.o board.o utils.o resource.o
	g++ main.o backend.o graphic.o board.o resource.o utils.o -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -o a.out 

main.o: main.cpp backend.h
	g++ $(CFLAGS) main.cpp

backend.o: backend.cpp graphic.h
	g++ $(CFLAGS) backend.cpp

graphic.o: graphic.cpp board.h utils.h
	g++ $(CFLAGS) graphic.cpp

board.o: board.cpp resource.h
	g++ $(CFLAGS) board.cpp

resource.o: resource.cpp
	g++ $(CFLAGS) resource.cpp

utils.o: utils.cpp
	g++ $(CFLAGS) utils.cpp 

clean:
	rm -rf *o a.out


