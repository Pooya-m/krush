#include <cstring>
#include <cmath>
#include "backend.h"
#include "graphic.h"
#include <cstdlib>

using namespace std;

bool rotatable(Object,Object);
int count_sames_in_row(Object);
int count_sames_in_column(Object);

int main(int argc,char* args[])
{
	bool quit = false;
	Board board;
	SDL_Surface* screen = NULL;
	SDL_Event event;
	vector <Object> selected_objects;
	
	srand(time(NULL));
	init_board(board);
	init_screen(screen,board);
	dump_board(board);
	int click = 0;
	while(!quit)
	{
		while(SDL_WaitEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				quit = true;
				break;
			}
			//		remove_object_from_screen(board,board.objects[0][0],screen);
			//move_to(board,board.objects[1][0].image,screen,0,50,0,0);
//			dump_board_without(board,board.objects[0][0],board.objects[1][0],screen);
			//rotate_in_graphic(board,board.objects[0][0],board.objects[1][0],screen);
//			SDL_Delay(1000);
			//move_to(board,board.objects[0][0].image,screen,0,0,0,50);
			//dump_board_without(board,board.objects[0][0],screen);
			//		SDL_Delay(2000);
			//quit = true;
			//break;
			if(event.type == SDL_MOUSEBUTTONDOWN)
			{
				if(event.button.button == SDL_BUTTON_LEFT )
				{
					select_object(board,event,screen,selected_objects);
					//remove_object_from_screen(board,selected_objects[0],screen);
					//SDL_Delay(2000);
					click++;
					if(click == 2)
					{
						if(rotatable(board,selected_objects[0],selected_objects[1]))
						{
							//rotate(board,selected_objects[0],selected_objects[1],screen);
							rotate_and_blow_out(board,selected_objects[0],selected_objects[1],screen);
						}
						else
						{
							rotate(board,selected_objects[0],selected_objects[1],screen);
							rotate(board,selected_objects[0],selected_objects[1],screen);
						}
							
						
						//cout << "unselect" << endl;
						//for(int i = 0; i < selected_objects.size(); i++)
						//	unselect_object(board,screen,selected_objects[i]);
						click = 0;
						selected_objects.clear();
					}
					}
			}
		}
	}
	SDL_FreeSurface(screen);
	
/*	cout << endl;
	int i1,j1,i2,j2;
	while(true)
	{
		cout << "i1 j1:  " << endl;
		cin >> i1 >> j1;
		cout << "i2 j2:  " << endl;
		cin >> i2 >> j2;
		rotate_and_blow_out(board,board.objects[i1][j1],board.objects[i2][j2]);
		}*/
	return 0;
}


