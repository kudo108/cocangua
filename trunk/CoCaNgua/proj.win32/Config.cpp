#include "Config.h"

using namespace CocosDenshion;

int Config::volume							= 100;
bool Config::isBgMusicPlaying				= false;
bool Config::isGameplayMusicPlaying			= false;
bool Config::isSFXEffectPlaying				= true;
bool Config::hasTurnOffMusic				= false;
int Config::idDice							= -1;
int Config::idButton						= -1;
int Config::idGameOver						= -1;
int Config::idGameWin						= -1;

const int Config::objectFontSize			= 40;
const char* Config::menuBackground			= "image/background_menu.jpg";
const char* Config::optionBackground		= "image/background_option.jpg";
const char* Config::flashBackground			= "image/flash.png";
const char* Config::aboutBackground			= "image/about.jpg";
const char* Config::classicGameBackground	= "image/Background_classic.jpg";
const char* Config::gameOverBackground		= "image/gameover.png";
const char* Config::xingau_init_image		= "image/ccn4.jpg";
const char* Config::animal1_init_image		= "/image/animal/heo/heo.png";
const char* Config::animal2_init_image		= "/image/animal/heo/heo.png";
const char* Config::animal3_init_image		= "/image/animal/heo/heo.png";
const char* Config::animal0_init_image		= "/image/animal/heo/heo2.png";
const char* Config::animal1_init_plist		= "/image/animal/heo/heo.plist";
const char* Config::animal2_init_plist		= "/image/animal/heo/heo.plist";
const char* Config::animal3_init_plist		= "/image/animal/heo/heo.plist";
const char* Config::animal0_init_plist		= "/image/animal/heo/heo2.plist";
const char* Config::backgroundMusic			= "music/background-music.mp3";
const char* Config::gameplayMusic			= "music/gameplay-music.mp3";
const char* Config::sfxButton				= "sound/Button.wav";
const char* Config::sfxDice					= "sound/RollDice.wav";
const char* Config::sfxGameOver				= "sound/GameOver.wav";
const char* Config::sfxGameWin				= "sound/GameWin.wav";
const char* Config::sfxFireworks			= "sound/Fireworks.wav";
const char* Config::border1					= "/image/ngua1.png";
const char* Config::miniMenu				= "/image/background_mini_menu.jpg";
const char* Config::menuBorder				= "/image/picture_border.png";
const char* Config::xucxac_plist			="/image/xucxac/xucxac.plist";
const char* Config::xucxac_texture			="/image/xucxac/xucxac.png";
const char* Config::xucxac_texture1			="/image/xucxac/1.png";
const char* Config::loader_plist			= "image/loader/AnimatedLoader.plist";
const char* Config::loader_texture			= "image/loader/AnimatedLoader.png";
const char* Config::loader_image			= "IMG00000.png";
const char* Config::gameWin_plist			= "image/gamewin/Gangnam.plist";
const char* Config::gameWin_texture			= "image/gamewin/Gangnam.png";
const char* Config::gameWin_image			= "gw0.png";
const char* Config::fireWorks_plist			= "image/phaohoa/phaohoa.plist";
const char* Config::fireWorks_texture		= "image/phaohoa/phaohoa.png";
const char* Config::fireWorks_image			= "1.png";
const char* Config::disappearEffect_plist	= "image/effect/effect.plist";
const char* Config::disappearEffect_texture	= "image/effect/effect.png";
const char* Config::disappearEffect_image	= "move-effect-0.png";

int Config::kqXucXac1=0;
int Config::kqXucXac2=0;

const int Config::WAYMAP = 0;
const int Config::INITMAP = -1;
const int Config::FINISHMAP = 1;

void Config::setHasTurnOffMusic(bool _music){
	hasTurnOffMusic = _music;
}

bool Config::getHasTurnOffMusic(){
	return hasTurnOffMusic;
}

void Config::setIdGameWin(int _id){
	idGameWin = _id;
}

int Config::getIdGameWin(){
	return idGameWin;
}

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

void Config::setIsGameplayMusicPlaying(bool _gp){
	isGameplayMusicPlaying = _gp;
}

bool Config::getIsGameplayMusicPlaying(){
	return isGameplayMusicPlaying;
}

int Config::getVolume()
{
	return volume;
}

void Config::setVolume(int _v)
{
	volume = _v;
}

void Config::playBackgroundMusic(const char* _bgMusic, int type){
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(_bgMusic, true);
	
	if(type == BG_MUSIC){
		Config::setIsBgMusicPlaying(true);
	}else{
		Config::setIsGameplayMusicPlaying(true);
	}
}

void Config::stopBackgroundMusic(){
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	Config::setIsBgMusicPlaying(false);
}

void Config::pauseBackgroundMusic(){
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	Config::setIsBgMusicPlaying(false);
}

void Config::resumeBackgroundMusic(){
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	Config::setIsBgMusicPlaying(true);
}

int Config::playEffect(const char* _sfx, bool loop){
	int id = -1;
	if(Config::getIsSFXEffectPlaying()){
		id = SimpleAudioEngine::sharedEngine()->playEffect(_sfx, loop);
	}
	return id;
}

void Config::stopAllEffect(){
	SimpleAudioEngine::sharedEngine()->stopAllEffects();
}
void Config::stopEffect(int id){
	SimpleAudioEngine::sharedEngine()->stopEffect(id);
}