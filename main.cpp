#include <cstring>
#include <cmath>
#include "backend.h"
#include <cstdlib>
using namespace std;

bool rotatable(Object,Object);
int count_sames_in_row(Object);
int count_sames_in_column(Object);

int main()
{
	Board board;
	init_board(board);
	dump_board(board);
	cout << endl;
	shift_down(board,1,0,1,2);
	dump_board(board);
	return 0;
}


