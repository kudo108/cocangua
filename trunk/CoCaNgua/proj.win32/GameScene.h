#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "Animals.h"

class GameScene : public cocos2d::CCScene
{
public:
	virtual bool init();
	CREATE_FUNC(GameScene);
	void setGameType(int _t);//1 = classic, 2 = modern, 3 = AI
	void saveGameCallback(CCObject *sender);
	void quitGameCallback(CCObject *sender);
	void ruleCallback(CCObject *sender);
	void xucxacCallback(CCObject *sender);
	//test
	void gameOverCallback(CCObject* sender);
	void gameWinCallback(CCObject* sender);
private:	
	int gameType;
	bool isCalledXucXac;

	CC_SYNTHESIZE(CCSprite *, xucxacA, XucxacA);
	CC_SYNTHESIZE(CCSprite *, xucxacB, XucxacB);
	CC_SYNTHESIZE(CCAction *, xucxacAAminationAction, XucxacAAminationAction);
	CC_SYNTHESIZE(CCAction *, xucxacBAminationAction, XucxacBAminationAction);	
};

#endif