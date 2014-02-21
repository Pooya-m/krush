#include "board.h"
using namespace std;

void init_board(Board& board)
{
	board.colors[0] = 'r';
	board.colors[1] = 'b';
	board.colors[2] = 'g';
	board.colors[3] = 'y';
	board.colors[4] = 'o';
	
	cin >> board.row_count >> board.column_count;

	for(int i = 0; i < COLORS_COUNT; i++)
		cin >> board.weights[i];
	
	board.objects.clear();
	board.objects.resize(board.row_count);
	for(int i = 0; i < board.row_count; i++)
		board.objects[i].resize(board.column_count);

	fill_board(board);
}

void set_object(Object& object,int type, char color, int i, int j)
{
	object.type = type;
	object.color = color;
	object.i = i;
	object.j = j;
}

void fill_board(Board& board)
{
	char color;
	for(int i = 0;i < board.row_count; i++)
		for(int j = 0;j < board.column_count; j++)
		{
			cin >> color;
			set_object(board.objects[i][j],TYPE_NORMAL,color,i,j);
		}
}

void dump_board(Board& board)
{
	for(int i = 0; i < board.row_count; i++)
	{
		for(int j = 0; j < board.column_count; j++)
			//cout << board.objects[i][j].color << " ";
		cout << board.objects[i][j].i << " " << board.objects[i][j].j << "(" << board.objects[i][j].color << ")" << " ";
		cout << endl;
	}
}

