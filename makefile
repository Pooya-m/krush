all:
	g++ board.cpp backend.cpp main.cpp graphic.cpp utils.cpp resource.cpp -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
