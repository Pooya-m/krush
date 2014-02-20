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
		cout << "here2" << endl;
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
	}
	
	for(int i = row_start+offset-1; i >= 0; i--)
		board.objects[i][column].color = get_random_object(board).color;
}

/*void move_and_replace(Board& board, vector <string> blocks)
{
	cout << "move and replace:  " << endl;
	cout << "======" << endl;
	for(int i = 0; i < blocks.size();i++)
		cout << blocks[i] << endl;
	cout << "======" << endl;


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
			{
				cout << "shifting down column " << column << " from row " << 0 << " to row " << row_start - 1 << " with 1 offset" << endl;
				shift_down(board,column,0,row_start-1,1);
			}
			else
			{
				cout << "creating random for i:  " << 0 << " j: " << column << endl;
				board.objects[0][column].color = get_random_object(board).color;
			}
		}
		else
		{
			cout << "shifting down column " << column << " from row " << 0 << " to row " << row_start - 1 << " with " << row_end-row_start+1 << "offset" << endl;
			shift_down(board,column,0,row_start-1,row_end-row_start+1);
		}
	}
}

vector < Object > get_objects(Board board, vector < string > blocks)
{
	vector < Object > objects;
	int column,row_start,row_end;
	for(int i = 0; i < blocks.size(); i++)
	{
		column = get_column(blocks[i]);
		row_start = get_row_start(blocks[i]);
		row_end = get_row_end(blocks[i]);
		for(int i = row_start; i != row_end; i++)
			objects.push_back(board.objects[i][column]);
	}
	return objects;
	}*/

void blow_out(Board& board, Object object, vector <Object>& removed_objects)
{
	Block object_block = get_duplicates_block(board,object);
	if(object_block.sub_blocks.size() == 0)
		return;
	
	for(int i = 0; i < object_block.sub_blocks.size();i++)
		for(int j = 0; j < object_block.sub_blocks[i].size(); j++)
			removed_objects.push_back(object_block.sub_blocks[i][j]);
}

vector <Object> get_objects(Block block)
{
	vector <Object> result;
	for(int i = 0; i < block.sub_blocks.size(); i++)
		for(int j = 0; j < block.sub_blocks[i].size(); j++)
			result.push_back(block.sub_blocks[i][j]);
	return result;
}

/*void remove_duplicates(vector <Object>& objects)
{
	for(int i = 0; i < objects.size(); i++)
		for(int j = i + 1; j < objects.size(); j++)
			if(objects[i] == objects[j])
				objects.erase(objects.begin() + j);
				}*/

bool compare(Object obj1,Object obj2)
{
	if(obj1.j < obj2.j)
		return true;

	if(obj1.j == obj2.j)
		if(obj1.i < obj2.i)
			return true;
	
	return false;
}

void blow_out(Board& board, vector < Block > blocks)
{
	if(blocks.size() == 0)
		return;

	vector <Object> temp_objects,objects;
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
	
	//unique(objects.begin(),objects.end(),check);

	cout << "free objects:  " << endl;
	for(int i = 0; i < objects.size();i++)
		cout << objects[i].i << " " << objects[i].j << endl;
	
	vector < Block > result_blocks;
	for(int i = 0; i < objects.size(); i++)
		shift_down(board,objects[i].j,0,objects[i].i-1,1);
	dump_board(board);
	cout << endl;
	Block temp_block;
	for(int i = 0; i < objects.size();i++) //for caution
	{
		for(int j = 0; j < objects[i].i;j++)
		{	
			temp_block = get_duplicates_block(board,board.objects[j][objects[i].j]);
			/*cout << "new blowings of object:  " << j << " " << objects[i].j << endl;	
			for(int k = 0; k < temp_block.sub_blocks.size(); k++)
				for(int l = 0; l < temp_block.sub_blocks[k].size(); l++)
				cout << temp_block.sub_blocks[k][l].i << " " << temp_block.sub_blocks[k][l].j << endl;*/
			result_blocks.push_back(get_duplicates_block(board,board.objects[j][objects[i].j]));
		}
	}
	
	blow_out(board,result_blocks);
}










