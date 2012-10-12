#pragma once

class Config
{
public:
	static void setVolume(int _v);
	//static void setIsBGMusicPlaying(int _BG);
	static int getVolume();
	//static int getIsBGMusicPlaying();
	const static char* sfxButton;
	const static char* backgroundMusic;
	const static int objectFontSize;
	const static char* menuBackground;
	const static char* flashBackground;
	const static char* aboutBackground;
	const static char* classicGameBackground;
	const static char* xingau_init_image;
	const static char* animal1_init_image;
	const static char* animal2_init_image;
	const static char* animal3_init_image;
	const static char* animal0_init_image;
private:
	//static int isBGMusicPlaying;
	static int volume;
	
};

