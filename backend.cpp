#include "backend.h"
#include <cmath>
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
	obj1.i = obj1.i + obj2.i - (obj2.i = obj1.i);
	obj1.j = obj1.j + obj2.j - (obj2.j = obj1.j);

	if(abs(obj1.i - obj2.i) != 1 and abs(obj1.j - obj2.j) != 1)
		return false;
	if(count_sames_in_column(board, obj1) >= 3 or count_sames_in_row(board, obj1) >= 3)
		return true;
	if(count_sames_in_column(board, obj2) >= 3 or count_sames_in_row(board, obj2) >= 3)
		return true;
	return false;
}

void rotate(Board board,Object& obj1,Object& obj2)
{
	obj1.i = obj1.i + obj2.i - (obj2.i = obj1.i);
	obj1.j = obj1.j + obj2.j - (obj2.j = obj1.j);
}

vector <string>  get_duplicates_block(Board board,Object object) //pattern: cArBtC (column A from row B to row C)
{
	vector <string> blocks;
	int min_j,max_j,min_i,max_i;
	set_sames_bounds_in_row(board,object,min_j,max_j);
	set_sames_bounds_in_column(board,object,min_i,max_i);
 	for(int j = min_j; j <= max_j; j++)
	{
		if(j == object.j)
			continue;
		blocks.push_back("c" + to_string(j) + "r" + to_string(object.i) + "t" + to_string(object.i));
	}

	blocks.push_back("c" + to_string(object.j) + "r" + to_string(min_i) + "t" + to_string(max_i));
	return blocks;
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
			return object;
		}
	}
	
}

void shift_down(Board& board, int column, int row_start, int row_end, int offset)
{
	for(int i = row_end; i >= row_start; i--)
		board.objects[i+offset][column] = board.objects[i][column];
	
	for(int i = row_start+offset-1; i >= 0; i--)
		board.objects[i][column].color = get_random_object(board).color;
}

void move_and_replace(Board& board, vector <string> blocks)
{
	srand(time(NULL));
	int column,row_start,row_end;
	for(int i = 0; i < blocks.size(); i++)
	{
		column = get_column(blocks[i]);
		row_start = get_row_start(blocks[i]);
		row_end = get_row_end(blocks[i]);
		
		if(is_single_block(blocks[i]))
		{
			if(row_start != 0)
				shift_down(board,column,0,row_start-1,1);
			else
				board.objects[0][column].color = get_random_object(board).color;
		}
		else
			shift_down(board,column,0,row_start-1,row_end-row_start+1);
	}
}



