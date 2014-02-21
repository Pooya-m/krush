#include "backend.h"
#include <cmath>
#include <algorithm>
using namespace std;

void set_sames_bounds_in_row(Board board, Object object, int& min_j, int& max_j)
{
	min_j = max_j = object.j;
	for(int j = object.j - 1; j >= 0; j--)
	{
		if(board.objects[object.i][j].color == object.color)
			min_j = j;
	  else
			break;
	}
	for(int j = object.j + 1; j < board.column_count; j++)
	{
		if(board.objects[object.i][j].color == object.color)
			max_j = j;
		else
			break;
	}
}

void set_sames_bounds_in_column(Board board, Object object, int& min_i, int& max_i)
{
	min_i = max_i = object.i;
	for(int i = object.i - 1; i >= 0; i--)
	{
		if(board.objects[i][object.j].color == object.color)
			min_i = i;
		else
			break;
	}
	for(int i = object.i + 1; i < board.row_count; i++)
	{
		if(board.objects[i][object.j].color == object.color)
			max_i = i;
		else
			break;
	}

}

int count_sames_in_row(Board board,Object object)
{
	int min_j,max_j;
	set_sames_bounds_in_row(board,object,min_j,max_j);
	return max_j - min_j + 1;
}

int count_sames_in_column(Board board, Object object)
{
	int min_i,max_i;
	set_sames_bounds_in_column(board,object,min_i,max_i);
	return max_i - min_i + 1;
}

bool rotatable(Board board, Object obj1,Object obj2)
{
	int i = obj1.i,j = obj1.j;
	int ii = obj2.i,jj = obj2.j;
	Object temp = obj1;

	board.objects[i][j] = obj2;
	board.objects[ii][jj] = temp;

  /* because of passed by value */
	board.objects[i][j].i = board.objects[i][j].i + board.objects[ii][jj].i - (board.objects[ii][jj].i = board.objects[i][j].i);
	board.objects[i][j].j = board.objects[i][j].j + board.objects[ii][jj].j - (board.objects[ii][jj].j = board.objects[i][j].j);
	obj1.i = obj1.i + obj2.i - (obj2.i = obj1.i);
	obj1.j = obj1.j + obj2.j - (obj2.j = obj1.j);
	/* */
	
	if(abs(obj1.i - obj2.i) != 1 and abs(obj1.j - obj2.j) != 1)
		return false;
	if(count_sames_in_column(board, obj1) >= 3 or count_sames_in_row(board, obj1) >= 3)
		return true;
	if(count_sames_in_column(board, obj2) >= 3 or count_sames_in_row(board, obj2) >= 3)
		return true;
	return false;
}

void rotate(Board& board,Object& obj1,Object& obj2, SDL_Surface*& screen)
{
	rotate_in_graphic(board,obj1,obj2,screen);
	/*int i = obj1.i,j = obj1.j;
	int ii = obj2.i,jj = obj2.j;

	Object temp = obj1;
	board.objects[i][j] = obj2;
	board.objects[ii][jj] = temp;
	

	obj1.i = obj1.i + obj2.i - (obj2.i = obj1.i);
	obj1.j = obj1.j + obj2.j - (obj2.j = obj1.j);*/

	int i = obj1.i,j = obj1.j;
	int ii = obj2.i,jj = obj2.j;
	Object temp = obj1;

	board.objects[i][j] = obj2;
	board.objects[ii][jj] = temp;

  /* because of passed by value */
	board.objects[i][j].i = board.objects[i][j].i + board.objects[ii][jj].i - (board.objects[ii][jj].i = board.objects[i][j].i);
	board.objects[i][j].j = board.objects[i][j].j + board.objects[ii][jj].j - (board.objects[ii][jj].j = board.objects[i][j].j);
	obj1.i = obj1.i + obj2.i - (obj2.i = obj1.i);
	obj1.j = obj1.j + obj2.j - (obj2.j = obj1.j);
	/* */
	
}

Block get_duplicates_block(Board board,Object object) //pattern: cArBtC (column A from row B to row C)
{
	Block block;
	int min_j,max_j,min_i,max_i,self_index = -1;
	set_sames_bounds_in_row(board,object,min_j,max_j);
	set_sames_bounds_in_column(board,object,min_i,max_i);
	if((max_j - min_j + 1) >= 3)
	{
		for(int j = min_j; j <= max_j; j++)
		{
			if(j == object.j)
				self_index = block.sub_blocks.size();
			block.sub_blocks.push_back(vector < Object >(1,board.objects[object.i][j]));
		}
	}

	if((max_i - min_i + 1) >= 3)
	{
		if(self_index != -1)
			block.sub_blocks.erase(block.sub_blocks.begin() + self_index);
		block.sub_blocks.push_back(vector < Object >(0));
		for(int i = min_i; i <= max_i;i++)
			block.sub_blocks.back().push_back(board.objects[i][object.j]);
	}
	
	return block;
}

Object get_random_object(Board board)
{
	Object object;
	double random_weight;
	//srand(time(NULL));
	random_weight = (rand() / ((double) RAND_MAX + 1.0));
	double sum = 0;
	for(int i = 0; i < COLORS_COUNT; i++)
	{
		sum += board.weights[i];
		if(random_weight < sum)
		{
			object.color = board.colors[i];
			object.image = board.images[i];
			return object;
		}
	}
	
}

void shift_down(Board& board, int column, int row_start, int row_end, int offset)
{
	for(int i = row_end; i >= row_start; i--)
	{
		board.objects[i+offset][column].type = board.objects[i][column].type;
		board.objects[i+offset][column].color = board.objects[i][column].color;
		board.objects[i+offset][column].image = board.objects[i][column].image;
	}
	
	for(int i = row_start+offset-1; i >= 0; i--)
	{
		Object temp = get_random_object(board);
		board.objects[i][column].color = temp.color;
		board.objects[i][column].image = temp.image;
	}
}


vector <Object> get_objects(Block block)
{
	vector <Object> result;
	for(int i = 0; i < block.sub_blocks.size(); i++)
		for(int j = 0; j < block.sub_blocks[i].size(); j++)
			result.push_back(block.sub_blocks[i][j]);
	return result;
}

bool compare(Object obj1,Object obj2)
{
	if(obj1.j < obj2.j)
		return true;

	if(obj1.j == obj2.j)
		if(obj1.i < obj2.i)
			return true;
	
	return false;
}

void blow_out(Board& board, vector < Block > blocks,SDL_Surface*& screen)
{
	if(blocks.size() == 0)
		return;

	vector <Object> temp_objects,objects;
	vector < Block > result_blocks;
	Block temp_block;
	
	for(int i = 0; i < blocks.size(); i++)
	{
		temp_objects = get_objects(blocks[i]);
		objects.insert(objects.end(),temp_objects.begin(),temp_objects.end());
	}

	if(objects.size() == 0)
		return;
	
	sort(objects.begin(),objects.end(),compare);


	for(int i = 0; i < objects.size() - 1;)
	{
		if((objects[i].i == objects[i+1].i) and (objects[i].j == objects[i+1].j))
			objects.erase(objects.begin()+i+1);
		else
			i++;
	}

	SDL_Delay(1000);
	for(int i = 0; i < objects.size(); i++)
	{
		remove_object_from_screen(board,objects[i],screen);
		shift_down(board,objects[i].j,0,objects[i].i-1,1);
	}
	SDL_Delay(1000);
	reload_screen(board,screen);

	cout << "after blow:  " << endl;
	dump_board(board);
	cout << endl;

	
	for(int i = 0; i < objects.size();i++) //for caution
		for(int j = 0; j <= objects[i].i;j++)
			result_blocks.push_back(get_duplicates_block(board,board.objects[j][objects[i].j]));
	
	blow_out(board,result_blocks,screen);
}

void rotate_and_blow_out(Board& board, Object& obj1, Object& obj2,SDL_Surface*& screen)
{
	if(rotatable(board,obj1,obj2))
		rotate(board,obj1,obj2,screen);
	else
	{
		cout << "not rotatable" << endl;
		rotate(board,obj1,obj2,screen);
		rotate(board,obj1,obj2,screen);
		return;
	}
	vector <Block> blocks;
	blocks.push_back(get_duplicates_block(board,obj1));
	blocks.push_back(get_duplicates_block(board,obj2));
	blow_out(board,blocks,screen);
}










