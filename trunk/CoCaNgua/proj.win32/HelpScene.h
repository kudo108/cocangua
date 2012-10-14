#ifndef _HELP_SCENE_H_
#define _HELP_SCENE_H_

#include "cocos2d.h"

class HelpScene : public cocos2d::CCScene
{
public:
	virtual bool init();
	CREATE_FUNC(HelpScene);
private:
	void menuCallback(CCObject *sender);
	void previousCallBack(CCObject* sender);
	void nextCallBack(CCObject* sender);
};

#endif