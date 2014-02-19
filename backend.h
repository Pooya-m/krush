#include "board.h"
void set_sames_bounds_in_row(Board board, Object, int& , int&);
void set_sames_bounds_in_column(Board board, Object, int&, int&);
int count_sames_in_row(Board,Object);
int count_sames_in_column(Board,Object);
bool rotatable(Board,Object,Object);
vector < vector < Object > > get_duplicates_block(Board,Object);
