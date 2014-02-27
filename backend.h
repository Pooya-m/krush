#include "board.h"
#include "graphic.h"

typedef struct Game {
	Board board;
	bool quit;	
} Game;

void set_sames_bounds_in_row(Board board, Object, int& , int&);
void set_sames_bounds_in_column(Board board, Object, int&, int&);
int count_sames_in_row(Board,Object);
int count_sames_in_column(Board,Object);
bool rotatable(Board,Object,Object);
void rotate(Board&,Object&,Object&);
Block get_duplicates_block(Board,Object);
void shift_down(Board&,int,int,int,int);
void move_and_replace(Board&, vector<string>);
Object get_random_object(Board);
vector <Object> get_objects(Block);
void remove_duplicates(vector <Object>&);
bool compare(Object,Object);
void blow_out(Board&,vector <Block>);
void rotate_and_blow_out(Board&,Object&,Object&);
void handle_mouse_event(Board&,SDL_Event,vector<Object>&);
bool is_over(Board);
void refill_board(Board&);
bool init_game(Game& game);
void free_everything(Board&);


