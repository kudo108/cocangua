#include "MusicHelper.h"
#include "SimpleAudioEngine.h"


using namespace CocosDenshion;

int MusicHelper::volume							= 100;
bool MusicHelper::isBgMusicPlaying				= false;
bool MusicHelper::isGameplayMusicPlaying		= false;
bool MusicHelper::isSFXEffectPlaying			= true;
bool MusicHelper::hasTurnOffMusic				= false;
int MusicHelper::idDice							= -1;
int MusicHelper::idButton						= -1;
int MusicHelper::idGameOver						= -1;
int MusicHelper::idGameWin						= -1;

const char* MusicHelper::backgroundMusic		= "/music/background-music.mp3";
const char* MusicHelper::gameplayMusic			= "/music/gameplay-music.mp3";
const char* MusicHelper::sfxButton				= "/sound/Button.wav";
const char* MusicHelper::sfxDice				= "/sound/RollDice.wav";
const char* MusicHelper::sfxGameOver			= "/sound/GameOver.wav";
const char* MusicHelper::sfxGameWin				= "/sound/GameWin.wav";
const char* MusicHelper::sfxFireworks			= "/sound/Fireworks.wav";

// animal sound
const char* MusicHelper::animal0_die_sound		="/sound/animal_sound/lon_die.wav";
const char* MusicHelper::animal1_die_sound		="/sound/animal_sound/vit_die.wav";
const char* MusicHelper::animal2_die_sound		="/sound/animal_sound/ngua_die.wav";
const char* MusicHelper::animal3_die_sound		="/sound/animal_sound/cho_die.wav";
	
const char* MusicHelper::animal0_move_sound		="/sound/animal_sound/lon_move.wav";
const char* MusicHelper::animal1_move_sound		="/sound/animal_sound/vit_move.wav";
const char* MusicHelper::animal2_move_sound		="/sound/animal_sound/ngua_move.wav";
const char* MusicHelper::animal3_move_sound		="/sound/animal_sound/cho_move.wav";

const char* MusicHelper::animal0_select_sound	="/sound/animal_sound/lon_selected.wav";
const char* MusicHelper::animal1_select_sound	="/sound/animal_sound/vit_selected.wav";
const char* MusicHelper::animal2_select_sound	="/sound/animal_sound/ngua_selected.wav";
const char* MusicHelper::animal3_select_sound	="/sound/animal_sound/cho_selected.wav";

const char* MusicHelper::animal_born_sound		="/sound/animal_sound/born.wav";
const char* MusicHelper::animal_finish_sound	="/sound/animal_sound/finish.wav";
const char* MusicHelper::animal_kick_sound		="/sound/animal_sound/kick.wav";

const char* MusicHelper::btSkip					="/sound/skipturn.wav";
const char* MusicHelper::btWrong				="/sound/wrongButton.wav";
const char* MusicHelper::moreTurn				="/sound/moreturn.wav";

void MusicHelper::setHasTurnOffMusic(bool _music){
	hasTurnOffMusic = _music;
}

bool MusicHelper::getHasTurnOffMusic(){
	return hasTurnOffMusic;
}

void MusicHelper::setIdGameWin(int _id){
	idGameWin = _id;
}

int MusicHelper::getIdGameWin(){
	return idGameWin;
}

void MusicHelper::setIdGameOver(int _id){
	idGameOver = _id;
}

int MusicHelper::getIdGameOver(){
	return idGameOver;
}

void MusicHelper::setIdButton(int _id){
	idButton = _id;
}

int MusicHelper::getIdButton(){
	return idButton;
}

void MusicHelper::setIdDice(int _id){
	idDice = _id;
}

int MusicHelper::getIdDice(){
	return idDice;
}

void MusicHelper::setIsSFXEffectPlaying(bool _SFX){
	isSFXEffectPlaying = _SFX;
}

bool MusicHelper::getIsSFXEffectPlaying(){
	return isSFXEffectPlaying;
}

void MusicHelper::setIsBgMusicPlaying(bool _Bg){
	isBgMusicPlaying = _Bg;
}

bool MusicHelper::getIsBgMusicPlaying(){
	return isBgMusicPlaying;
}

void MusicHelper::setIsGameplayMusicPlaying(bool _gp){
	isGameplayMusicPlaying = _gp;
}

bool MusicHelper::getIsGameplayMusicPlaying(){
	return isGameplayMusicPlaying;
}

int MusicHelper::getVolume()
{
	return volume;
}

void MusicHelper::setVolume(int _v)
{
	volume = _v;
}

void MusicHelper::playBackgroundMusic(const char* _bgMusic, int type){
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(_bgMusic, true);
	
	if(type == BG_MUSIC){
		MusicHelper::setIsBgMusicPlaying(true);
	}else{
		MusicHelper::setIsGameplayMusicPlaying(true);
	}
}

void MusicHelper::stopBackgroundMusic(){
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	MusicHelper::setIsBgMusicPlaying(false);
}

void MusicHelper::pauseBackgroundMusic(){
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	MusicHelper::setIsBgMusicPlaying(false);
}

void MusicHelper::resumeBackgroundMusic(){
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	MusicHelper::setIsBgMusicPlaying(true);
}

int MusicHelper::playEffect(const char* _sfx, bool loop){
	int id = -1;
	if(MusicHelper::getIsSFXEffectPlaying()){
		id = SimpleAudioEngine::sharedEngine()->playEffect(_sfx, loop);
	}
	return id;
}

void MusicHelper::stopAllEffect(){
	SimpleAudioEngine::sharedEngine()->stopAllEffects();
}
void MusicHelper::stopEffect(int id){
	SimpleAudioEngine::sharedEngine()->stopEffect(id);
}

void MusicHelper::pauseEffect(int id){
	SimpleAudioEngine::sharedEngine()->pauseEffect(id);
}

void MusicHelper::resumeEffect(int id){
	SimpleAudioEngine::sharedEngine()->resumeEffect(id);
}

void MusicHelper::end(){
	SimpleAudioEngine::sharedEngine()->end();
}