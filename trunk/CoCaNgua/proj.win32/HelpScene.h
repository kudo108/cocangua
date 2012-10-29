#ifndef _HELP_SCENE_H_
#define _HELP_SCENE_H_

#include "cocos2d.h"
using namespace cocos2d;
class HelpScene : public cocos2d::CCScene
{
public:
	virtual bool init();
	CREATE_FUNC(HelpScene);
private:
	void menuCallback(CCObject *sender);
	void previousCallBack(CCObject* sender);
	void nextCallBack(CCObject* sender);
	CC_SYNTHESIZE(CCSprite*, sprite, Sprite);
	const static int total;
	int cur;
	void loadSpriteAtCurrent();
};

#endif