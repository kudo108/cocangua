#include "Config.h"
#include <string.h>

int Config::volume							= 100;
bool Config::isBgMusicPlaying				= true;
//bool Config::isSFXEffectPlaying				= true;
const int Config::objectFontSize			= 40;
const char* Config::menuBackground			= "image/background_menu.jpg";
const char* Config::flashBackground			= "image/flash.jpg";
const char* Config::aboutBackground			= "image/about.jpg";
const char* Config::classicGameBackground	= "image/Background_classic.jpg";
const char* Config::xingau_init_image		= "image/ccn4.jpg";
const char* Config::animal1_init_image		= "/image/animal/1.jpg";
const char* Config::animal2_init_image		= "/image/animal/2.jpg";
const char* Config::animal3_init_image		= "/image/animal/3.jpg";
const char* Config::animal0_init_image		= "/image/animal/0.jpg";
const char* Config::musicDirectory			= "music/";
const char* Config::sfxDirectory			= "sound/";
const char* Config::backgroundMusic			= strcat("background-music.wav",Config::musicDirectory);
const char* Config::sfxButton				= strcat("background-music.wav",Config::sfxDirectory);


//void Config::setIsSFXEffectPlaying(bool _SFX){
//	isSFXEffectPlaying = _SFX;
//}
//
//bool Config::getIsSFXEffectPlaying(){
//	return isSFXEffectPlaying;
//}

void Config::setIsBgMusicPlaying(bool _Bg){
	isBgMusicPlaying = _Bg;
}

bool Config::getIsBgMusicPlaying(){
	return isBgMusicPlaying;
}

int Config::getVolume()
{
	return volume;
}

void Config::setVolume(int _v)
{
	volume = _v;
}
