//#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "board.h"
#include <string>
using namespace std;
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT  480
#define SCREEN_BPP 32

bool init_screen(SDL_Surface*&,Board&);
void apply_surface(int x, int y,SDL_Surface*&, SDL_Surface*& );
void select_object(Board,SDL_Event,SDL_Surface*&,vector<Object>& selected_objects);
void unselect_object(Board,SDL_Surface*&,Object);
//void move_to(Board& board,SDL_Surface*&,SDL_Surface*&,int source_x, int source_y, int dest_x,int dest_y);
void rotate_in_graphic(Board,Object&,Object&,SDL_Surface*&);
bool is_valid_click(Board,SDL_Event);
void dump_board_without(Board,Object,Object,SDL_Surface*&);
void dump_board_without(Board,vector <Object>, SDL_Surface*&);
void remove_object_from_screen(Board,Object,SDL_Surface*&);
void move_to(Board,Object&,vector <Object>,SDL_Surface*& screen,int dest_x,int dest_y);
void reload_screen(Board,SDL_Surface*&);
SDL_Surface* load_image(string);
