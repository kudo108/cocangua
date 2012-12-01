#ifndef _AI_GAME_SCENE_H_
#define _AI_GAME_SCENE_H_

#include "cocos2d.h"
#include "GameScene.h"

class AIGameScene: public cocos2d::CCScene
{
public:
	virtual bool init();
	void menuCallBack(CCObject *sender);
	void autoPlay();
	void autoSkip();
	void buttonSkipCallback(CCObject* sender);
	void buttonDiceCallback(CCObject* sender);
	void skipCallBack();
	void diceCallback();
	void checkResultDice(int diceA, int diceB);
	bool haveAnyPlayerOnWay(GameObject* gameObject);
	AnimalUnit* unitSelected(int diceA, int diceB);
	CREATE_FUNC(AIGameScene);
private:
	CC_SYNTHESIZE(bool, isCalledDice, IsCalledDice);	
	//dice
	CC_SYNTHESIZE(CCSprite *, diceA, diceA);
	CC_SYNTHESIZE(CCSprite *, diceB, diceB);
	CC_SYNTHESIZE(CCAction *, diceAminationAction, diceAminationAction);

	//point lable
	CC_SYNTHESIZE(CCMenuItemFont*, team0PointLable, Team0PointLable);
	CC_SYNTHESIZE(CCMenuItemFont*, team1PointLable, Team1PointLable);
	CC_SYNTHESIZE(CCMenuItemFont*, team2PointLable, Team2PointLable);
	CC_SYNTHESIZE(CCMenuItemFont*, team3PointLable, Team3PointLable);

	GameObject* gameObject;
	int diceResultA;
	int diceResultB;
	CCMenuItemSprite *diceButton1;
	CCMenuItemSprite *diceButton2;
};

#endif