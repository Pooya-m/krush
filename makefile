all:
	g++ board.cpp backend.cpp main.cpp parser.cpp graphic.cpp -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
