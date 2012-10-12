#include "Config.h"

int Config::volume=100;
const int Config::objectFontSize=40;
const char* Config::menuBackground = "image/background_menu.jpg";
const char* Config::flashBackground = "image/flash.jpg";
const char* Config::aboutBackground = "image/about.jpg";
const char* Config::classicGameBackground = "image/Background_classic.jpg";
const char* Config::xingau_init_image = "image/ccn4.jpg";
const char* Config::animal1_init_image="/image/animal/1.jpg";
const char* Config::animal2_init_image="/image/animal/2.jpg";
const char* Config::animal3_init_image="/image/animal/3.jpg";
const char* Config::animal0_init_image="/image/animal/0.jpg";
const char* Config::backgroundMusic = "music/background-music.wav";
const char* Config::sfxButton = "sound/Button.wav";

//int Config::getIsBGMusicPlaying(){
//	return isBGMusicPlaying;
//}
//
//void Config::setIsBGMusicPlaying(int _BG){
//	isBGMusicPlaying = _BG;
//}

int Config::getVolume()
{
	return volume;
}

void Config::setVolume(int _v)
{
	volume = _v;
}
