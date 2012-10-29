#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "Animals.h"
#include "MapLocation.h"

using namespace cocos2d;

class GameObject : public CCObject
{
public:
	GameObject(CCNode* _parent);
	~GameObject(void);

	//game function
	void changeTurn();
	void resetDice();
	bool canInitFromRollResult();
	bool canContinueRollFromRollResult();
	bool canFinishFromRollResult();
	int getStepFromRollResult();
	bool canSelectUnit();

	//amination function
	void lightUp(CCPoint point);
	void deleteAllLightUp();
	void select(CCPoint point);
	void unSelect();
	
	//unit location function
	int havingUnitOnWay(int step);// 100 = no;-1 = co, 0->15 ->unit o cuoi 
	bool havingUnitOnFinish(int teamNo, int step);
	AnimalUnit *getUnitOnInitLocation(int teamNo);
	AnimalUnit *getUnitByTag(int tag);
	int getTagByUnit(AnimalUnit* unit);

	//reset
	void resetCurrentUnit();
private:
	//animals
	CC_SYNTHESIZE_READONLY(Animals *, animal0, Animal0);
	CC_SYNTHESIZE_READONLY(Animals *, animal1, Animal1);
	CC_SYNTHESIZE_READONLY(Animals *, animal2, Animal2);
	CC_SYNTHESIZE_READONLY(Animals *, animal3, Animal3);
	
	CC_SYNTHESIZE_READONLY(MapLocation*, map, Map);

	CC_SYNTHESIZE_READONLY(Animals *, currentTurn,CurrentTurn);
	CC_SYNTHESIZE(AnimalUnit*, currentSelectUnit, CurrentSelectUnit);
	
	CCNode* parent;

	//amination
	CC_SYNTHESIZE(CCAction*, selectAction, SelectAction);
	CC_SYNTHESIZE(CCSprite*, selectedSprite, SelectedSprite);
	CC_SYNTHESIZE(CCAction*, lightupAction, LightupAction);
	CC_SYNTHESIZE(CCArray*, lightupArray, LightupArray);

	//dice
	CC_SYNTHESIZE(int, diceResult1, DiceResult1);
	CC_SYNTHESIZE(int, diceResult2, DiceResult2);
	CC_SYNTHESIZE(bool, lockDice, LockDice);
	
	//lock user
	CC_SYNTHESIZE(bool, lockUser, LockUser);
};

#endif