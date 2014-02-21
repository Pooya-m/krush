#ifndef BOARD_H_
#define BOARD_H_

#include <iostream>
#include <vector>
#include <cstdlib>
#include "SDL/SDL.h"

#define COLORS_COUNT 5
#define TYPE_NORMAL 0

using namespace std;

typedef struct Object {
	int type;
	char color;
	int i;
	int j;
	SDL_Surface* image;
} Object;

typedef struct Block {
	//int column;
	//int row_start;
	//int row_end;
	//vector < string > sub_blocks;
	vector < vector < Object > > sub_blocks;
} Block;

typedef struct Board {
	char colors[5];
	double weights[5];
	int row_count;
	int column_count;
	vector < vector < Object > > objects;
	SDL_Surface* selected_object;
	SDL_Surface* images[5];
} Board;

void init_board(Board&);
void set_object(Object&,int,char,int,int);
void fill_board(Board&);
void dump_board(Board&);

#endif
