#include "Config.h"

using namespace CocosDenshion;

int Config::volume							= 100;
bool Config::isBgMusicPlaying				= false;
bool Config::isSFXEffectPlaying				= true;
int Config::idDice							= -1;
int Config::idButton						= -1;
int Config::idGameOver						= -1;
const int Config::objectFontSize			= 40;
const char* Config::menuBackground			= "image/background_menu.jpg";
const char* Config::flashBackground			= "image/flash.png";
const char* Config::aboutBackground			= "image/about.jpg";
const char* Config::classicGameBackground	= "image/Background_classic.jpg";
const char* Config::gameOverBackground		= "image/gameover.png";
const char* Config::xingau_init_image		= "image/ccn4.jpg";
const char* Config::animal1_init_image		= "/image/animal/1.jpg";
const char* Config::animal2_init_image		= "/image/animal/2.jpg";
const char* Config::animal3_init_image		= "/image/animal/3.jpg";
const char* Config::animal0_init_image		= "/image/animal/0.jpg";
const char* Config::backgroundMusic			= "music/background-music.wav";
const char* Config::sfxButton				= "sound/Button.wav";
const char* Config::sfxDice					= "sound/RollDice.wav";
const char* Config::sfxGameOver				= "sound/GameOver.wav";
const char* Config::border1					= "/image/ngua1.png";
const char* Config::miniMenu				= "/image/background_mini_menu.jpg";
const char* Config::menuBorder				= "/image/picture_border.png";
const char* Config::xucxac_plist			="/image/xucxac/xucxac.plist";
const char* Config::xucxac_texture			="/image/xucxac/xucxac.png";
const char* Config::xucxac_texture1			="/image/xucxac/1.png";


void Config::setIdGameOver(int _id){
	idGameOver = _id;
}

int Config::getIdGameOver(){
	return idGameOver;
}

void Config::setIdButton(int _id){
	idButton = _id;
}

int Config::getIdButton(){
	return idButton;
}

void Config::setIdDice(int _id){
	idDice = _id;
}

int Config::getIdDice(){
	return idDice;
}

void Config::setIsSFXEffectPlaying(bool _SFX){
	isSFXEffectPlaying = _SFX;
}

bool Config::getIsSFXEffectPlaying(){
	return isSFXEffectPlaying;
}

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

void Config::playBackgroundMusic(const char* _bgMusic){
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(_bgMusic, true);   
}

void Config::stopBackgroundMusic(){
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

void Config::pauseBackgroundMusic(){
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void Config::resumeBackgroundMusic(){
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

int Config::playEffect(const char* _sfx, bool loop){
	int id = -1;
	if(Config::getIsSFXEffectPlaying()){
		id = SimpleAudioEngine::sharedEngine()->playEffect(_sfx, loop);
	}
	return id;
}

void Config::stopEffect(int id){
	SimpleAudioEngine::sharedEngine()->stopEffect(id);
}