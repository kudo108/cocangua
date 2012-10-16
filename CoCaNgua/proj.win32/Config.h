#ifndef _CONFIG_H_
#define _CONFIG_H_
#include "SimpleAudioEngine.h"

class Config
{
public:
	static void setVolume(int _v);
	static void setIsBgMusicPlaying(bool _Bg);
	static void setIsSFXEffectPlaying(bool _SFX);
	static void setIdDice(int _id);
	static void setIdButton(int _id);
	static void setIdGameOver(int _id);
	static void setIdGameWin(int _id);
	static void setHasTurnOffMusic(bool _music);

	static bool getIsBgMusicPlaying();
	static bool getIsSFXEffectPlaying();
	static bool getHasTurnOffMusic();
	static int getVolume();
	static int getIdDice();
	static int getIdButton();
	static int getIdGameOver();
	static int getIdGameWin();

	static void playBackgroundMusic(const char* _bgMusic);
	static void stopBackgroundMusic();
	static void pauseBackgroundMusic();
	static void resumeBackgroundMusic();
	static int playEffect(const char* _sfx, bool loop);
	static void stopEffect(int id);
	static void stopAllEffect();

	const static char* backgroundMusic;
	const static char* sfxButton;
	const static char* sfxDice;
	const static char* sfxGameOver;
	const static char* sfxGameWin;
	
	const static int objectFontSize;
	const static char* gameOverBackground;
	const static char* menuBackground;
	const static char* optionBackground;
	const static char* flashBackground;
	const static char* aboutBackground;
	const static char* border1;
	const static char* miniMenu;
	const static char* menuBorder;
	const static char* classicGameBackground;
	const static char* xingau_init_image;
	const static char* animal1_init_image;
	const static char* animal2_init_image;
	const static char* animal3_init_image;
	const static char* animal0_init_image;
	const static char* xucxac_plist;
	const static char* xucxac_texture;
	const static char* xucxac_texture1;
	const static char* loader_plist;
	const static char* loader_texture;
	const static char* loader_image;
	const static char* gameWin_plist;
	const static char* gameWin_texture;
	const static char* gameWin_image;
private:
	static bool isBgMusicPlaying;
	static bool hasTurnOffMusic;
	static bool isSFXEffectPlaying;
	static int volume;
	static int idDice;
	static int idButton;
	static int idGameOver;
	static int idGameWin;
};

#endif