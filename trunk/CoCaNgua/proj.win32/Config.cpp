#include "Config.h"

int Config::volume=100;
const int Config::objectFontSize=40;
const char* Config::menuBackground = "image/background_menu.jpg";
const char* Config::flashBackground = "image/flash.jpg";
const char* Config::aboutBackground = "image/about.jpg";
const char* Config::classicGameBackground = "image/Background_classic.jpg";
const char* Config::xingau_init_image = "image/ccn4.jpg";

int Config::getVolume()
{
	return volume;
}

void Config::setVolume(int _v)
{
	volume = _v;
}
