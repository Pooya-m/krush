//#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "board.h"
#include "utils.h"
#include <string>
using namespace std;
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT  480
#define SCREEN_BPP 32
#define FONT_NAME "arial.ttf"
#define FONT_SIZE 30
#define SCORE_VALUE_COLOR {255,255,255}
#define SCORE_X 0
#define SCORE_Y 300


bool init_screen(Board&);
void apply_surface(int x, int y,SDL_Surface*&, SDL_Surface*& );
void select_object(Board&,SDL_Event,vector<Object>& selected_objects);
void unselect_object(Board&,Object);
void rotate_in_graphic(Board&,Object&,Object&);
bool is_valid_click(Board,SDL_Event);
void dump_board_without(Board&,Object,Object);
void dump_board_without(Board&,vector <Object>);
void remove_object_from_screen(Board&,Object);
void move_to(Board&,Object&,vector <Object>,int dest_x,int dest_y);
void reload_screen(Board&);
void render_text(Board& board,int x, int y,string,SDL_Color);
void show_score(Board&);
SDL_Surface* load_image(string);
void dump_time(Board&);
