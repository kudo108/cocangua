#ifndef _ANIMALS_H_
#define _ANIMALS_H_

#include "AnimalUnit.h"
#include "cocos2d.h"

class Animals
{
public:
	Animals(int offset, CCNode *_parent, MapLocation* _m);
	~Animals(void);
	AnimalUnit *unit0;
	AnimalUnit *unit1;
	AnimalUnit *unit2;
	AnimalUnit *unit3;
	/*
	CC_SYNTHESIZE(AnimalUnit *,unit0,Unit0);
	CC_SYNTHESIZE(AnimalUnit *,unit1,Unit1);
	CC_SYNTHESIZE(AnimalUnit *,unit2,Unit2);
	CC_SYNTHESIZE(AnimalUnit *,unit3,Unit3);
	*/
private:
	MapLocation *map;
	CCNode *parent;
};

#endif