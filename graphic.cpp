#include "graphic.h"
#include <iostream>
using namespace std;

void apply_surface(int x, int y,SDL_Surface*& source,SDL_Surface*& destination)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(source,NULL,destination,&offset);
}

bool is_valid_click(Board board, SDL_Event event)
{
	int x = event.button.x;
	int y = event.button.y;

	if((y / IMAGE_HEIGHT) == 0 and (x / IMAGE_WIDTH) == board.column_count)
	{
		if(board.blow_same_bonus > 0)
		{
			cout << "valid bonus click" << endl;
			return true;
		}
		else
		{
			cout << "expired bonus click" << endl;
			return false;
		}
	}

	if((y / IMAGE_HEIGHT == 1) and (x / IMAGE_WIDTH) == board.column_count)
	{
		if(board.blow_row_column_bonus > 0)
		{
			cout << "valid bonus click" << endl;
			return true;
		}
		else
		{
			cout << "expired bonus click" << endl;
			return false;
		}
	}
	
	if((y / IMAGE_HEIGHT) >= board.row_count)
		return false;
	if((x / IMAGE_WIDTH) >= board.column_count)
		return false;
	if(x < 0)
		return false;
	if(y < 0)
		return false;

	return true;
}

bool select_object(Board& board, SDL_Event event,vector <Object>& selected_objects)
{
	int x = event.button.x;
	int y = event.button.y;

	if(!is_valid_click(board,event))
	{
		cout << "not a valid click!" << endl;
		for(int i = 0; i < selected_objects.size(); i++)
			unselect_object(board,selected_objects[i]);
		return false;
	}
	
	for(int i = 0; i < selected_objects.size(); i++)
	{
		if(selected_objects[i].i == y / IMAGE_HEIGHT and selected_objects[i].j == x / IMAGE_WIDTH)
		{
			cout << "here!" << endl;
			unselect_object(board,selected_objects[i]);
			cout << "not here!" << endl;
			return false;
		}
	}

											
	cout << "selected:  " << endl;
	cout << y / 50 << " " << x / 50 << endl;

	
	if((y / IMAGE_HEIGHT) == 0 and (x / IMAGE_WIDTH) == board.column_count)
	{
		Object bonus_bomb;
		bonus_bomb.image = board.resources.bonus_images[0];
		bonus_bomb.type = TYPE_BLOW_SAME_BONUS;
		bonus_bomb.i = 0;
		bonus_bomb.j = board.column_count;		
		selected_objects.push_back(bonus_bomb);
	  apply_surface((x / IMAGE_WIDTH) * IMAGE_WIDTH, (y / IMAGE_HEIGHT) * IMAGE_HEIGHT,board.resources.bonus_images[0],board.screen);
	}
	else if((y / IMAGE_HEIGHT) == 1 and (x / IMAGE_WIDTH) == board.column_count)
	{
		Object bonus_bomb;
		bonus_bomb.image = board.resources.bonus_images[1];
		bonus_bomb.type = TYPE_BLOW_ROW_COLUMN_BONUS;
		bonus_bomb.i = 1;
		bonus_bomb.j = board.column_count;		
		selected_objects.push_back(bonus_bomb);
	  apply_surface((x / IMAGE_WIDTH) * IMAGE_WIDTH, (y / IMAGE_HEIGHT) * IMAGE_HEIGHT,board.resources.bonus_images[1],board.screen);
	}
	else
	{
		selected_objects.push_back(board.objects[y/IMAGE_HEIGHT][x/IMAGE_WIDTH]);
		apply_surface((x / IMAGE_WIDTH) * IMAGE_WIDTH, (y / IMAGE_HEIGHT) * IMAGE_HEIGHT,board.resources.selected_object_image,board.screen);
	}
	SDL_Flip(board.screen);
	return true;
}

void unselect_object(Board& board,Object object)
{
		SDL_Rect rect;
   	rect.x = object.j * IMAGE_WIDTH;
		rect.y = object.i * IMAGE_HEIGHT;
		rect.h = IMAGE_HEIGHT;
		rect.w = IMAGE_WIDTH;
		SDL_FillRect(board.screen,&rect,0x000000);
		apply_surface(rect.x,rect.y,object.image,board.screen);
		SDL_Flip(board.screen);
}

void dump_board_without(Board& board, Object obj1,Object obj2)
{
	SDL_Rect rect;
	rect.h = SCREEN_HEIGHT;
	rect.w = SCREEN_WIDTH;
	SDL_FillRect(board.screen,NULL,0x000000);
	for(int i = 0; i < board.row_count; i++)
		for(int j = 0; j < board.column_count; j++)
		{
			if(obj1.i == i and obj1.j == j)
				continue;
			if(obj2.i == i and obj2.j == j)
				continue;
			apply_surface(j*IMAGE_WIDTH,i*IMAGE_HEIGHT,board.objects[i][j].image,board.screen);
			}

	apply_surface(board.column_count * IMAGE_WIDTH,0,board.resources.bonus_images[0],board.screen);
	apply_surface(board.column_count * IMAGE_WIDTH,IMAGE_HEIGHT,board.resources.bonus_images[1],board.screen);
	
	show_score(board);
	dump_time(board);
	dump_bonus(board);
	}

void move_to(Board& board,Object& object, vector <Object> removed_objects,int dest_x, int dest_y)
{
	SDL_Rect rect;
	rect.x = object.j * IMAGE_WIDTH;
	rect.y = object.i * IMAGE_HEIGHT;
	while((rect.x != dest_x) or (rect.y != dest_y))
	{
		dump_board_without(board,removed_objects[0],removed_objects[1]);
		if(rect.x < dest_x)
			rect.x += 1;
		else if(rect.x > dest_x)
			rect.x -= 1;

		if(rect.y < dest_y)
			rect.y += 1;
		else if(rect.y > dest_y)
			rect.y -= 1;
		SDL_BlitSurface(object.image,NULL,board.screen,&rect);
		SDL_Flip(board.screen);
		SDL_Delay(3);
	}
}

void rotate_in_graphic(Board& board,Object& obj1,Object& obj2)
{
	cout << "======= rotate in graphic =====" << endl;
	cout << "obj1:  " << obj1.i << " " << obj1.j << endl;
	cout << "obj2:  " << obj2.i << " " << obj2.j << endl;
	cout << endl;
	SDL_Rect rect1,rect2;
	rect1.x = obj1.j * IMAGE_WIDTH;
	rect1.y = obj1.i * IMAGE_HEIGHT;
	rect2.x = obj2.j * IMAGE_WIDTH;
	rect2.y = obj2.i* IMAGE_HEIGHT;
	bool checked = false;
	while(true)
	{
		if((rect1.x != obj2.j*IMAGE_WIDTH) or (rect1.y != obj2.i*IMAGE_HEIGHT))
		{
			if(!checked)
			{
				dump_board_without(board,obj1,obj2);
				checked = true;
			}
			if(rect1.x < obj2.j*IMAGE_WIDTH)
				rect1.x += 1;
			else if(rect1.x > obj2.j*IMAGE_WIDTH)
				rect1.x -= 1;

			if(rect1.y < obj2.i*IMAGE_HEIGHT)
				rect1.y += 1;
			else if(rect1.y > obj2.i*IMAGE_HEIGHT)
				rect1.y -= 1;
			SDL_BlitSurface(obj1.image,NULL,board.screen,&rect1);
		}
		else
			break;
		
		if((rect2.x != obj1.j*IMAGE_WIDTH) or (rect2.y != obj1.i*IMAGE_HEIGHT))
		{
			if(!checked)
			{
				dump_board_without(board,obj1,obj2);
				checked = true;
			}
			
			if(rect2.x < obj1.j*IMAGE_WIDTH)
				rect2.x += 1;
			else if(rect2.x > obj1.j*IMAGE_WIDTH)
				rect2.x -= 1;

			if(rect2.y < obj1.i*IMAGE_HEIGHT)
				rect2.y += 1;
			else if(rect2.y > obj1.i*IMAGE_HEIGHT)
				rect2.y -= 1;
			SDL_BlitSurface(obj2.image,NULL,board.screen,&rect2);
		}
		else
			break;

		checked = false;
		SDL_Flip(board.screen);
		SDL_Delay(3);
	}
}

void remove_object_from_screen(Board& board,Object object)
{
	SDL_Rect rect;
	rect.x = object.j*IMAGE_WIDTH;
	rect.y = object.i*IMAGE_HEIGHT;
	rect.h = IMAGE_HEIGHT;
	rect.w = IMAGE_WIDTH;
	SDL_FillRect(board.screen,&rect,0x000000);
	SDL_Flip(board.screen);
}

void reload_screen(Board& board)
{
	SDL_Rect rect;
	rect.h = SCREEN_HEIGHT;
	rect.w = SCREEN_WIDTH;
	SDL_FillRect(board.screen,NULL,0x000000);
	for(int i = 0; i < board.row_count; i++)
		for(int j = 0; j < board.column_count; j++)
			apply_surface(j*50,i*50,board.objects[i][j].image,board.screen);

	apply_surface(board.column_count * IMAGE_WIDTH,0,board.resources.bonus_images[0],board.screen);
	apply_surface(board.column_count * IMAGE_WIDTH,IMAGE_HEIGHT,board.resources.bonus_images[1],board.screen);
	
	show_score(board);
	dump_time(board);
	dump_bonus(board);
}


bool init_screen(Board& board)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		cout << "coudln't init" << endl;
		return false;
	}
	board.screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE);
	if(board.screen == NULL)
	{
		cout << "set video mode failed:  " << endl;
		cout << SDL_GetError() << endl;
		return false;
	}

	if(!init_resources(board.resources))
	{
		cout << "couldn't init resources" << endl;
		return false;
	}

	SDL_WM_SetCaption("Krush",NULL);

		for(int i = 0; i < board.row_count ; i++)
		for(int j = 0; j < board.column_count; j++)
		{
			switch(board.objects[i][j].color)
			{
			case 'b':
				board.objects[i][j].image = board.resources.bomb_images[1];
				break;
			case 'r':
				board.objects[i][j].image = board.resources.bomb_images[0];
				break;
			case 'g':
				board.objects[i][j].image = board.resources.bomb_images[2];
				break;
			case 'o':
				board.objects[i][j].image = board.resources.bomb_images[4];
				break;
			case 'y':
				board.objects[i][j].image = board.resources.bomb_images[3];
				break;
		  }
				apply_surface(j*50,i*50,board.objects[i][j].image,board.screen);
			}
	 
		reload_screen(board);
	return true;
}

SDL_Surface* load_image(string file_name)
{
	SDL_Surface* temp_image = NULL;
	SDL_Surface* image = NULL;
	temp_image = IMG_Load(file_name.c_str());
	if(temp_image != NULL)
	{
		image = SDL_DisplayFormat(temp_image);
		SDL_SetColorKey(image,SDL_SRCCOLORKEY,0xffffff);
		SDL_FreeSurface(temp_image);
	}
	else
	{
		cout << "IMG_load failed: " << endl;
		cout << SDL_GetError() << endl;
	}
	return image;
}

void render_text(Board& board, int x, int y,string message,SDL_Color color)
{
	SDL_Surface* message_surface = TTF_RenderText_Solid(board.resources.font,message.c_str(),color);
	apply_surface(x,y,message_surface,board.screen);
	SDL_Flip(board.screen);
	SDL_FreeSurface(message_surface);
}

void show_score(Board& board)
{
	SDL_Color color = SCORE_VALUE_COLOR;
	render_text(board,INFO_X_OFFSET,(board.row_count * IMAGE_HEIGHT) + INFO_Y_OFFSET,"Score: "+to_string(board.score),color);
}

void dump_time(Board& board)
{
	SDL_Rect rect;
	rect.x = INFO_X_OFFSET;
	rect.y = (board.row_count * IMAGE_HEIGHT) + INFO_Y_OFFSET + 30;
	rect.h = IMAGE_HEIGHT+10;
	rect.w = IMAGE_WIDTH;
	SDL_FillRect(board.screen,&rect,0x000000);
	SDL_Flip(board.screen);
	SDL_Color color = SCORE_VALUE_COLOR;
	render_text(board,rect.x,rect.y,to_string(TOTAL_TIME - board.time),color);
}

void dump_bonus(Board& board)
{
	cout << "dump bonus" << endl;
	cout << "bonus:  " << board.blow_same_bonus << endl;
	
	SDL_Rect rect;
	rect.x = ((board.column_count+1) * IMAGE_WIDTH)+10;
	rect.y = 10;
	rect.h = IMAGE_HEIGHT;
	rect.w = IMAGE_WIDTH;
	SDL_FillRect(board.screen,&rect,0x000000);
	SDL_Flip(board.screen);
	SDL_Color color = SCORE_VALUE_COLOR;
	render_text(board,rect.x,rect.y,to_string(board.blow_same_bonus),color);

	rect.x = ((board.column_count+1) * IMAGE_WIDTH)+10;
	rect.y = 10+IMAGE_HEIGHT;
	rect.h = IMAGE_HEIGHT;
	rect.w = IMAGE_WIDTH;
	SDL_FillRect(board.screen,&rect,0x000000);
	SDL_Flip(board.screen);
	render_text(board,rect.x,rect.y,to_string(board.blow_row_column_bonus),color);
}




