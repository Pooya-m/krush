#ifndef BOARD_H_
#define BOARD_H_

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "resource.h"
#include <iostream>
#include <vector>
#include <cstdlib>

#define COLORS_COUNT 5
#define TYPE_NORMAL 0
#define TYPE_BLOW_SAME_BONUS 1
#define TYPE_BLOW_ROW_COLUMN_BONUS 2
#define TOTAL_TIME 60

using namespace std;

typedef struct Object {
	int type;
	char color;
	int i;
	int j;
	SDL_Surface* image;
} Object;

typedef struct Block {
	vector < vector < Object > > sub_blocks;
} Block;

typedef struct Board {
	char colors[5];
	double weights[5];
	int row_count;
	int column_count;
	vector < vector < Object > > objects;
	SDL_Surface* screen;
	int time;
	int score;

	int blow_same_bonus;
	int blow_row_column_bonus;
	
	Resource resources;
} Board;

bool init_board(Board&);
void set_object(Object&,int,char,int,int);
void fill_board(Board&);
void dump_board(Board&);

#endif
