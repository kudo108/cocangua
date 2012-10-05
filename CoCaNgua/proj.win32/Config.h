#pragma once

class Config
{
public:
	static void setVolume(int _v);
	static int getVolume();

	const static int objectFontSize;
	const static char* menuBackground;
	const static char* flashBackground;
	const static char* aboutBackground;
	const static char* classicGameBackground;
	const static char* xingau_init_image;
private:
	static int volume;
	
};

