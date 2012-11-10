#include "Config.h"


const int Config::objectFontSize			= 40;

//background
const char* Config::menuBackground			= "image/background_menu.jpg";
const char* Config::optionBackground		= "image/background_option.jpg";
const char* Config::flashBackground			= "image/flash.png";
const char* Config::aboutBackground			= "image/about.jpg";
const char* Config::classicGameBackground	= "image/Background_classic.png";
const char* Config::gameOverBackground		= "image/gameover.png";
const char* Config::miniMenu				= "/image/background_mini_menu.jpg";
const char* Config::menuBorder				= "/image/picture_border.png";

//animals
const char* Config::animal0_init_image		= "/image/animal/heo/heo2.png";
const char* Config::animal1_init_image		= "/image/animal/vit/vit.png";
const char* Config::animal2_init_image		= "/image/animal/ngua/horse.png";
const char* Config::animal3_init_image		= "/image/animal/cho/dog.png";
const char* Config::animal0_init_plist		= "/image/animal/heo/heo2.plist";
const char* Config::animal1_init_plist		= "/image/animal/vit/vit.plist";
const char* Config::animal2_init_plist		= "/image/animal/ngua/horse.plist";
const char* Config::animal3_init_plist		= "/image/animal/cho/dog.plist";

const char* Config::dice_plist			="/image/xucxac/xucxac.plist";
const char* Config::dice_texture			="/image/xucxac/xucxac.png";

const char* Config::loader_plist			= "/image/loader/AnimatedLoader.plist";
const char* Config::loader_texture			= "/image/loader/AnimatedLoader.png";
const char* Config::loader_image			= "IMG00000.png";

const char* Config::gameWin_plist			= "/image/gamewin/Gangnam.plist";
const char* Config::gameWin_texture			= "/image/gamewin/Gangnam.png";
const char* Config::gameWin_image			= "gw0.png";

const char* Config::fireWorks_plist			= "/image/phao hoa/phaohoa.plist";
const char* Config::fireWorks_texture		= "/image/phao hoa/phaohoa.png";
const char* Config::fireWorks_image			= "1.png";

const char* Config::disappearEffect_plist	= "/image/effect/effect.plist";
const char* Config::disappearEffect_texture	= "/image/effect/effect.png";
const char* Config::disappearEffect_image	= "move-effect-0.png";

const char* Config::lightup_go_image		= "/image/lighup/lightup.png";
const char* Config::lightup_go_plist		= "/image/lighup/lightup.plist";
const char* Config::lightup_go_init_image	= "/image/lighup/lightup1.png";

const char* Config::lightup_way_image		= "/image/way/way.png";
const char* Config::lightup_way_plist		= "/image/way/way.plist";
const char* Config::lightup_way_init_image	= "/image/way/way1.png";

const char* Config::select_image			= "/image/select/select.png";
const char* Config::select_plist			= "/image/select/select.plist";
const char* Config::select_init_image		= "/image/select/select1.png";


//int Config::isExploring=0;
const float Config::animalNormalMoveTime = 0.2f;//s

int Config::gameType = 0;
bool Config::loadGame = false;
