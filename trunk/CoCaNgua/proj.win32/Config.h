#ifndef _CONFIG_H_
#define _CONFIG_H_

class Config
{
public:
	static void setVolume(int _v);
	static void setIsBgMusicPlaying(bool _Bg);
	static void setIsSFXEffectPlaying(bool _SFX);

	static int getVolume();
	static bool getIsBgMusicPlaying();
	static bool getIsSFXEffectPlaying();

	const static char* sfxDirectory;
	const static char* musicDirectory;
	const static char* sfxButton;
	const static char* backgroundMusic;
	const static int objectFontSize;
	const static char* menuBackground;
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
private:
	static bool isBgMusicPlaying;
	static int volume;
	static bool isSFXEffectPlaying;
};

#endif