#ifndef _ANIMALS_H_
#define _ANIMALS_H_

#include "AnimalUnit.h"
#include "cocos2d.h"

class AnimalUnit;

using namespace cocos2d;

class Animals
{
public:
	Animals(int offset, CCNode *_parent, MapLocation* _m);
	~Animals(void);
	void increasePointByGo(int step);
	void increasePointByKick();
	void increasePointByBorn();
	void increasePointByFinish(int x);
	void setupTeamSpriteToParent();
	void removeTeamSpriteFromParent();
	bool isFinished();
	void increaseFinished();
	void whileBorn(CCNode* sender, char* born_sound);
	void afterFinish(CCNode* sender, char* finish_sound);
	void beforeDie(CCNode* sender, char* die_sound);
	AnimalUnit *getUnit(int index);
private:

	CC_SYNTHESIZE_READONLY(AnimalUnit *, unit0, Unit0);
	CC_SYNTHESIZE_READONLY(AnimalUnit *, unit1, Unit1);
	CC_SYNTHESIZE_READONLY(AnimalUnit *, unit2, Unit2);
	CC_SYNTHESIZE_READONLY(AnimalUnit *, unit3, Unit3);
	
	CC_SYNTHESIZE(int, point, Point);
	CC_SYNTHESIZE(int, teamNo, TeamNo);
	MapLocation *map;
	CC_SYNTHESIZE(CCNode*, parent, Parent);

	CC_SYNTHESIZE_READONLY(CCSprite*, teamSprite, TeamSprite);
	CC_SYNTHESIZE_READONLY(CCAction*, spriteAction, SpriteAction);
	CC_SYNTHESIZE(int, unitFinished, UnitFinished);

	//sound
	char* move_sound;
	char* die_sound;
	char* kick_sound;
	char* born_sound;
	char* finish_sound;
	char* select_sound;
};

#endif