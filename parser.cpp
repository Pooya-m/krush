#include "parser.h"
#include <cstdlib>

string to_string(int number)
{
	string result = "";

	if(number == 0)
		return "0";
	
	while(number != 0)
	{
		result = "0123456789abcdef"[number % 10] + result;
		number /= 10;
	}
	return result;
}

string select(string input,int index1,int index2)
{
	return input.substr(index1,index2 - index1 + 1);
}

int to_int(string input)
{
	return atoi(input.c_str());
}

int get_numbers_in(string input,char start,char end)
{
	int start_index = input.find(start);
	int end_index = input.find(end);
	string number = select(input,start_index+1,end_index-1);
	return to_int(number);
}

int get_column(string input)
{
	return get_numbers_in(input,'c','r');
}

int get_row_start(string input)
{
	return get_numbers_in(input,'r','t');
}

int get_row_end(string input)
{
	return get_numbers_in(input,'t','\0');
}

bool is_single_block(string input)
{
	return (get_row_start(input) == get_row_end(input));
}






