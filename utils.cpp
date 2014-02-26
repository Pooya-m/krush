#include "utils.h"
using namespace std;

string to_string(int number)
{
	string result="";
	if(number == 0)
		result = "0";
	
	while(number != 0)
	{
		result = "0123456789abcdef"[number % 10] + result;
		number /= 10;
	}

	return result;
}
