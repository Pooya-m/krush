#include <iostream>
#include <vector>
#include <cstdlib>
#define COLORS_COUNT 5
#define TYPE_NORMAL 0

using namespace std;

typedef struct Object {
	int type;
	char color;
	int i;
	int j;
} Object;

typedef struct Board {
	char colors[5];
	double weights[5];
	int row_count;
	int column_count;
	vector < vector < Object > > objects;
} Board;

void init_board(Board&);
void set_object(Object&,int,char,int,int);
void fill_board(Board&);
void dump_board(Board&);
