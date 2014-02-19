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
	for(int i = object.i + 1; i < board.column_count; i++)
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

vector < vector < Object > >  get_duplicates_block(Board board,Object object)
{
	vector <string> blocks;

	for(int j = object.j - 1; j >= 0; j--)
	{
		if(board.objects[object.i][j].color == object.color)
			blocks.push_back("j"+to_string(j)+"i"+to_string(object.i)+to_string(object.i));
		else
			break;
	}
	
	int min_i = object.i, max_i = object1.i;

	for(int i = object.i - 1; i >= 0; i--)
	{
		if(board.objects[i][object.j].color == object.color)
			min_i--;
		else
			break;
	}
	
	for(int i = object.i + 1; i < board.row_count; i++)
	{
		if(board.objects[i][object.j].color == object.color)
			max_i++;
		else
			break;
	}

	blocks.push_back("j"+object.j+"i"+min_i+max_i);

	for(int j = object.j + 1; j < board.column_count ; j++)
	{
		if(board.objects[object.i][j].color == object.color)
			blocks.push_back("j"+j+"i"+object.i+object.i);
		else
			break;
	}
	
}

