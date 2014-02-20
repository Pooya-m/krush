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
	srand(time(NULL));
	Board board;
	init_board(board);
	dump_board(board);
	cout << endl;
	Block block = get_duplicates_block(board,board.objects[1][2]);
	vector <Block> blocks;
	blocks.push_back(get_duplicates_block(board,board.objects[2][2]));
	blow_out(board,blocks);
	/*for(int i = 0; i < block.sub_blocks.size(); i++)
		for(int j = 0; j < block.sub_blocks[i].size(); j++)
		cout << block.sub_blocks[i][j].i << " " << block.sub_blocks[i][j].j << endl;*/
/*	for(int i = 0; i < block.objects.size(); i++)
		for(int j = 0; j < block.objects[i].size(); j++)
		cout << block.objects[i][j].i << " " << block.objects[i][j].j << endl;*/
	//shift_down(board,1,0,1,2);
	//move_and_replace(board, get_duplicates_block(board,board.objects[1][2]));
//	vector<string> blocks = get_duplicates_block(board,board.objects[1][2]);
	//for(int i = 0; i < blocks.size(); i++)
	//cout << blocks[i] << endl;
	//dump_board(board);
	//blow_out(board,board.objects[1][2]);
	
	return 0;
}


