#include "board.h"
using namespace std;

bool init_board(Board& board)
{
	board.colors[0] = 'r';
	board.colors[1] = 'b';
	board.colors[2] = 'g';
	board.colors[3] = 'y';
	board.colors[4] = 'o';
	board.score = 0;
	board.time = 60;
	board.music = NULL;
	board.blow = NULL;

	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
	{
		cout << "fuck that" << endl;
		return false;
	}
	
	board.music = Mix_LoadMUS("theme_sound.mp3");
	if(board.music == NULL)
	{
		cout << "theme sound not found!" << endl;
		return false;
	}

	board.blow = Mix_LoadWAV("bomb.wav");
	if(board.blow == NULL)
	{
		cout << Mix_GetError() << endl;
		cout << "bomb wav not found!" << endl;
		return false;
	}

	cin >> board.row_count >> board.column_count;

	for(int i = 0; i < COLORS_COUNT; i++)
		cin >> board.weights[i];
	
	board.objects.clear();
	board.objects.resize(board.row_count);
	for(int i = 0; i < board.row_count; i++)
		board.objects[i].resize(board.column_count);
		
	fill_board(board);
	
	return true;
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

