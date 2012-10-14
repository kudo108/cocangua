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
	MapLocation *map;	
	//void changeXucXac(int x);
	//cocos2d::CCAction *xucxacAction ;
	//cocos2d::CCSprite *xucxac;
private:	
	int gameType;
	bool isCalledXucXac;
	
	cocos2d::CCSprite *xucxac1;
	cocos2d::CCSprite *xucxac2;
	cocos2d::CCSprite *xucxac3;
	cocos2d::CCSprite *xucxac4;
	cocos2d::CCSprite *xucxac5;
	cocos2d::CCSprite *xucxac6;
	
	CC_SYNTHESIZE(CCSprite *,xucxac,Xucxac);
	CC_SYNTHESIZE(CCAction *,xucxacAminationAction,XucxacAmination);
	int soXucXac();


};


#endif