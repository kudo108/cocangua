#ifndef _ANIMALS_H_
#define _ANIMALS_H_

#include "AnimalUnit.h"
#include "cocos2d.h"

class AnimalUnit;
class Animals
{
public:
	Animals(int offset, CCNode *_parent, MapLocation* _m);
	~Animals(void);
	AnimalUnit *unit0;
	AnimalUnit *unit1;
	AnimalUnit *unit2;
	AnimalUnit *unit3;
	int teamNo;
	unsigned int getPoint();
	void increasePointByGo(int step);
	void increasePointByKick();
	void increasePointByBorn();
	void increasePointByFinish(int x);
private:
	int point;
	MapLocation *map;
	CCNode *parent;
};

#endif