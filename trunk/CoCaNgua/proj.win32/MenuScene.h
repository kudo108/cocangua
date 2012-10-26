#ifndef _MENU_SCENE_H_
#define _MENU_SCENE_H_

#include "cocos2d.h"
using namespace cocos2d;

class MenuScene : public cocos2d::CCScene
{
public:
	virtual bool init();
	CREATE_FUNC(MenuScene);
private:
	void menuClassicGameCallback(CCObject* sender);
	void menuModernGameCallback(CCObject* sender);
	void menuLoadGameCallback(CCObject* sender);
	void menuAboutCallback(CCObject* sender);
	void menuHelpCallback(CCObject* sender);
	void menuOptionCallback(CCObject* sender);
	void menuExitCallback(CCObject* sender);
	void menuAIGameCallback(CCObject* sender);
};

#endif