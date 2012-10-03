#ifndef _MENU_SCENE_H_
#define _MENU_SCENE_H_

#include "cocos2d.h"

class MenuLayer: public cocos2d::CCLayer
{
public:
	MenuLayer(void);
	~MenuLayer(void);
	bool init();
	CREATE_FUNC(MenuLayer);
};

class MenuScene : public cocos2d::CCScene
{
public:
	MenuScene(void);
	~MenuScene(void);
	bool init();
	CREATE_FUNC(MenuScene);
private:
	void menuClassicGameCallback();
	void menuModernGameCallback();
	void menuLoadGameCallback();
	void menuAboutCallback();
	void menuHelpCallback();
	void menuOptionCallback();
	void menuExitCallback();
	void menuAIGameCallback();
};

#endif