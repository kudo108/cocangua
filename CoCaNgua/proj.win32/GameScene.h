#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "GameObject.h"
#include "GameLogic.h"
#include "SaveLoad.h"
using namespace cocos2d;

class GameScene : public cocos2d::CCScene
{
public:
	virtual bool init();
	~GameScene();
	CREATE_FUNC(GameScene);
	
	//button callback
	void saveGameCallback(CCObject *sender);
	void helpGameCallback(CCObject *sender);
	void quitGameCallback(CCObject *sender);
	void ruleCallback(CCObject *sender);
	void diceCallback(CCObject *sender);
	//void diceCallbackForAI();
	void buttonSkipCallback(CCObject *sender);
	//void buttonGoCallback(CCObject *sender);
	void buttonSelectCallback(CCObject *sender);
	int loadGame();
	
	//test
	//void gameOverCallback(CCObject* sender);
	//void gameWinCallback(CCObject* sender);
	//release lock
	//void releaseLockUser();
private:	

	//CC_SYNTHESIZE(int, gameType, GameType);
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
	
	//game object
	GameObject* gameObject;
	
	void update(CCTime dt);
	void updatePoint(int teamNo);
	
	GameLogic *gameLogic;
};

#endif