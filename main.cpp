#include <cstring>
#include <cmath>
#include "backend.h"
#include "graphic.h"
#include <cstdlib>

using namespace std;

int main(int argc,char* args[])
{
	Game game;
	SDL_Event event;
	vector <Object> selected_objects;
	srand(time(NULL));
	init_game(game);

	while(!game.quit)
	{
		dump_time(game.board);
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				game.quit = true;
				break;
			}
			if(event.type == SDL_MOUSEBUTTONDOWN)
				handle_mouse_event(game.board,event,selected_objects);
		}
	}
	free_everything(game.board);
	return 0;
}


