#pragma once
#include "cocos2d.h"
class GameOverScene : public cocos2d::CCScene {
public:
	bool init();
	CREATE_FUNC(GameOverScene);
private:
	void menuCallBack(CCObject* sender);
	void restartCallBack(CCObject* sender);
};

