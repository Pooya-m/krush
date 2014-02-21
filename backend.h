#include "board.h"
#include "parser.h"

void set_sames_bounds_in_row(Board board, Object, int& , int&);
void set_sames_bounds_in_column(Board board, Object, int&, int&);
int count_sames_in_row(Board,Object);
int count_sames_in_column(Board,Object);
bool rotatable(Board,Object,Object);
void rotate(Board&,Object&,Object&);
Block get_duplicates_block(Board,Object);
//void blow_out(Board& board, Object object,vector < Object >& removed_objects);
void shift_down(Board&,int,int,int,int);
void move_and_replace(Board&, vector<string>);
Object get_random_object(Board);
vector <Object> get_objects(Block);
void remove_duplicates(vector <Object>&);
bool compare(Object,Object);
void blow_out(Board&,vector <Block>);
void rotate_and_blow_out(Board&,Object&,Object&);

