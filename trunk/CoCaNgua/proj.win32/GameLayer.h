#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_

#include "cocos2d.h"

class GameLayer : public cocos2d::CCLayer
{
public:
	GameLayer(void);
	~GameLayer(void);
	bool init();
	CREATE_FUNC(GameLayer);
	void saveGameCallback(CCObject *sender);
	void quitGameCallback(CCObject *sender);
	void ruleCallback(CCObject *sender);
	void xingauCallback(CCObject *sender);
	static int soXiNgau();
private:

};

#endif