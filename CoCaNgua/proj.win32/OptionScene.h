#ifndef _OPTION_SCENE_H_
#define _OPTION_SCENE_H_

#include "cocos2d.h"
#include "HelloWorldScene.h"

class OptionScene : public cocos2d::CCScene
{
public:
	virtual bool init();
	CREATE_FUNC(OptionScene);
	
private:
	void menuCallback(CCObject *sender);
	void toggleMusic(CCObject *sender);
	void toggleSFX(CCObject *sender);
};

#endif