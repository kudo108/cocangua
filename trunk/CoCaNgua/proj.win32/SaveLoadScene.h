#pragma once

#include "cocos2d.h"
#include "MenuScene.h"

using namespace cocos2d;

class SaveLoadScene : public cocos2d::CCScene
{
public:
	virtual bool init();
	CREATE_FUNC(SaveLoadScene);

private:
	void classicCallback(CCObject *sender);
	void AICallback(CCObject *sender);
	void modernCallback(CCObject *sender);
	void racingCallback(CCObject *sender);
	void menuCallback(CCObject* sender);
	void showWarning();
};

