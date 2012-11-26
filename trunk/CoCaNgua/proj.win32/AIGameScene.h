#ifndef _AI_GAME_SCENE_H_
#define _AI_GAME_SCENE_H_

#include "cocos2d.h"
#include "GameScene.h"

class AIGameScene: public GameScene
{
public:
	virtual bool init();
	void menuCallBack(CCObject *sender);
	void autoPlay();
	void buttonSkipCallback(CCObject* sender);
	void buttonDiceCallback(CCObject* sender);
	void skipCallBack();
	void diceCallback();
	void checkResultDice(int diceA, int diceB);
	AnimalUnit* unitSelected(int diceA, int diceB);
	CREATE_FUNC(AIGameScene);
private:
	int diceResultA;
	int diceResultB;
};

#endif