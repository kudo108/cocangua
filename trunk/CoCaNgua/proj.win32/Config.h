#pragma once

class Config
{
public:
	static void setVolume(int _v);
	static void setIsBgMusicPlaying(bool _Bg);
	//static void setIsSFXEffectPlaying(bool _SFX);

	static int getVolume();
	static bool getIsBgMusicPlaying();
	//static bool getIsSFXEffectPlaying();

	const static char* sfxDirectory;
	const static char* musicDirectory;
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
	static bool isBgMusicPlaying;
	static int volume;
	//static bool isSFXEffectPlaying;
};

