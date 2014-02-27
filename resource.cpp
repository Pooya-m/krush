#include "resource.h"
#include "graphic.h"
using namespace std;

bool init_resources(Resource& resource)
{
	resource.bomb_images[0] = load_image(RED_FILE_NAME);
	resource.bomb_images[1] = load_image(BLUE_FILE_NAME);
	resource.bomb_images[2] = load_image(GREEN_FILE_NAME);
	resource.bomb_images[3] = load_image(YELLOW_FILE_NAME);
	resource.bomb_images[4] = load_image(ORRANGE_FILE_NAME);
	resource.selected_object_image = load_image(SELECTED_OBJECT_FILE_NAME);
	
	resource.background_music = NULL;
	resource.blowing_out_sound = NULL;
	resource.laser_sound = NULL;
	resource.font = NULL;

	if(Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
	{
		cout << Mix_GetError() << endl;
		return false;
	}
	
	resource.background_music = Mix_LoadMUS(BACKGROUND_MUSIC_FILE_NAME);
	if(resource.background_music == NULL)
	{
		cout << Mix_GetError() << endl;
		return false;
	}

	resource.blowing_out_sound = Mix_LoadWAV(BLOWING_OUT_SOUND_FILE_NAME);
	if(resource.blowing_out_sound == NULL)
	{
		cout << Mix_GetError() << endl;
		return false;
	}

	resource.laser_sound = Mix_LoadWAV(LASER_SOUND_FILE_NAME);
	if(resource.laser_sound == NULL)
	{
		cout << Mix_GetError() << endl;
		return false;
	}

	if(TTF_Init() == -1)
		return false;

  resource.font = TTF_OpenFont(FONT_FILE_NAME,FONT_SIZE);
	if(resource.font == NULL)
	{
		cout << "coultdn't open font" << endl;
		return false;
		}
	
	return true;
}

void play_background_music(Resource resource)
{
	Mix_PlayMusic(resource.background_music, -1 );
}

void play_sound(Mix_Chunk*& sound)
{
	Mix_PlayChannel(-1,sound,0) ;
}
