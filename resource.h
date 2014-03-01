#ifndef RESOURCE_H_
#define RESOURCE_H_

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"

#define BOMB_TYPES_COUNT 5
#define RED_FILE_NAME "resources/img/r.bmp"
#define BLUE_FILE_NAME "resources/img/b.bmp"
#define GREEN_FILE_NAME "resources/img/g.bmp"
#define YELLOW_FILE_NAME "resources/img/y.bmp"
#define ORRANGE_FILE_NAME "resources/img/o.bmp"
#define EMPTY_FILE_NAME "resources/img/empty.bmp"

#define BONUS_BLOW_SAME_FILE_NAME "resources/img/same.bmp"
#define BONUS_BLOW_ROW_COLUMN_FILE_NAME "resources/img/row_column.bmp"

#define SELECTED_OBJECT_FILE_NAME "resources/img/dark.bmp"
#define BACKGROUND_MUSIC_FILE_NAME "resources/sounds/background_music.mp3"
#define BLOWING_OUT_SOUND_FILE_NAME "resources/sounds/blowing_out_sound.wav"
#define LASER_SOUND_FILE_NAME "resources/sounds/laser_sound.wav"
#define FONT_SIZE 30
#define FONT_FILE_NAME "resources/fonts/font.ttf"

typedef struct Resource {
	SDL_Surface* bomb_images[BOMB_TYPES_COUNT];
	SDL_Surface* bonus_images[2];
	SDL_Surface* selected_object_image;
	SDL_Surface* empty_image;
	
	TTF_Font* font;

	Mix_Music* background_music;
	Mix_Chunk* blowing_out_sound;
	Mix_Chunk* laser_sound;
} Resource;

bool init_resources(Resource&);
void play_background_music(Resource);
void play_sound(Mix_Chunk*&);
#endif
