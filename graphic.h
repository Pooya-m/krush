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
bool is_valid_click(Board,SDL_Event);
SDL_Surface* load_image(string);
