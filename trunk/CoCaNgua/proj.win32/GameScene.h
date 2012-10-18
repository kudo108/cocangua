#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

//#include "cocos2d.h"
#include "MapLocation.h"

class GameScene : public cocos2d::CCScene
{
public:
	GameScene(void);
	~GameScene(void);
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
	//unit callback
	void go1Callback(CCObject *sender);
	void go2Callback(CCObject *sender);
	void go3Callback(CCObject *sender);
	void go4Callback(CCObject *sender);
	MapLocation *map;	
private:	
	int gameType;
	bool isCalledXucXac;
	int kqXucXac[2];

	CC_SYNTHESIZE(CCSprite *,xucxacA,XucxacA);
	CC_SYNTHESIZE(CCSprite *,xucxacB,XucxacB);
	CC_SYNTHESIZE(CCAction *,xucxacAAminationAction,XucxacAAminationAction);
	CC_SYNTHESIZE(CCAction *,xucxacBAminationAction,XucxacBAminationAction);
	//test
	//CC_SYNTHESIZE(AnimalUnit *,heo,Heo);
};


#endif