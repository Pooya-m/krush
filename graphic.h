//#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "utils.h"
#include "board.h"
#include <string>

using namespace std;
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT  480
#define SCREEN_BPP 32
#define SCORE_VALUE_COLOR {82,182,00}
#define INFO_X_OFFSET 30
#define INFO_Y_OFFSET 10
#define IMAGE_HEIGHT 50
#define IMAGE_WIDTH 50


bool init_screen(Board&);
void apply_surface(int x, int y,SDL_Surface*&, SDL_Surface*& );
bool select_object(Board&,SDL_Event,vector<Object>& selected_objects);
void unselect_object(Board&,Object);
void rotate_in_graphic(Board&,Object&,Object&);
bool is_valid_click(Board,SDL_Event);
void dump_board_without(Board&,Object,Object);
void remove_object_from_screen(Board&,Object);
void move_to(Board&,Object&,vector <Object>,int dest_x,int dest_y);
void reload_screen(Board&);
void render_text(Board& board,int x, int y,string,SDL_Color);
void show_score(Board&);
SDL_Surface* load_image(string);
void dump_time(Board&);
