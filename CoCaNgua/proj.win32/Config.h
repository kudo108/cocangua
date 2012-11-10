#ifndef _CONFIG_H_
#define _CONFIG_H_

#define CLASSIC 1
#define MODERN 2
#define AI 3
#define RACING 4

class Config
{
public:
	
	const static int objectFontSize;

	const static char* gameOverBackground;
	const static char* menuBackground;
	const static char* optionBackground;
	const static char* flashBackground;
	const static char* aboutBackground;
	const static char* miniMenu;
	const static char* menuBorder;
	const static char* classicGameBackground;

	const static char* animal1_init_image;
	const static char* animal2_init_image;
	const static char* animal3_init_image;
	const static char* animal0_init_image;
	const static char* animal1_init_plist;
	const static char* animal2_init_plist;
	const static char* animal3_init_plist;
	const static char* animal0_init_plist;

	const static char* dice_plist;
	const static char* dice_texture;

	const static char* loader_plist;
	const static char* loader_texture;
	const static char* loader_image;

	const static char* gameWin_plist;
	const static char* gameWin_texture;
	const static char* gameWin_image;

	const static char* fireWorks_plist;
	const static char* fireWorks_texture;
	const static char* fireWorks_image;

	const static char* disappearEffect_plist;
	const static char* disappearEffect_texture;
	const static char* disappearEffect_image;

	const static char* lightup_way_image;
	const static char* lightup_way_plist;
	const static char* lightup_way_init_image;
	
	const static char* lightup_go_image;
	const static char* lightup_go_plist;
	const static char* lightup_go_init_image;

	const static char* select_image;
	const static char* select_plist;
	const static char* select_init_image;

	//static int isExploring;

	const static float animalNormalMoveTime;
	
	//variable
	static int gameType;
	static bool loadGame;
};

#endif