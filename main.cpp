#include <cstring>
#include <cmath>
#include "backend.h"
#include "graphic.h"
#include <cstdlib>

using namespace std;

int main(int argc,char* args[])
{
	bool quit = false;
	Board board;
	SDL_Surface* screen = NULL;
	SDL_Event event;
	vector <Object> selected_objects;

	srand(time(NULL));
	init_board(board);
	init_screen(board);
	while(!quit)
	{
		while(SDL_WaitEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				quit = true;
				break;
			}
			if(event.type == SDL_MOUSEBUTTONDOWN)
				handle_mouse_event(board,event,selected_objects);
		}
	}
	free_everything(board);
	return 0;
}


