#include "backend.h"
#include <cmath>
using namespace std;

int count_sames_in_row(Board board,Object object)
{
	int count = 0;
	for(int j = object.j - 1; j >= 0; j--)
	{
		if(board.objects[object.i][j].color == object.color)
			count++;
		else
			break;
	}
	for(int j = object.j + 1; j < board.column_count; j++)
	{
		if(board.objects[object.i][j].color == object.color)
			count++;
		else
			break;
	}
	return count;
}

int count_sames_in_column(Board board, Object object)
{
	int count = 0;
	for(int i = object.i - 1; i >= 0; i--)
	{
		if(board.objects[i][object.j].color == object.color)
			count++;
		else
			break;
	}
	for(int i = object.i + 1; i < board.row_count; i++)
	{
		if(board.objects[i][object.j].color == object.color)
			count++;
		else
			break;
	}
	return count;
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

