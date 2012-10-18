#ifndef _ANIMAL_UNIT_H_
#define _ANIMAL_UNIT_H_

#include "cocos2d.h"
#include "MapLocation.h"

using namespace cocos2d;

class AnimalUnit
{
public:
	AnimalUnit(int offset, CCNode *parent,CCPoint _initLocation, MapLocation *_m);
	~AnimalUnit(void);
	CCPoint getLocation();
	void born();//tu chuong ra duong
	void go(int step);//di them dc step buoc
	void finish(int step);//den dich buoc thu x
	void die();//chet, ve lai chuong
	void dance();//luc lac luc lac =))
private:
	CCPoint location;//vi tri hien tai
	CCPoint initLocation;//vi tri trong chuong
	int path_went;//doan duong da di
	CC_SYNTHESIZE(CCSprite*, sprite, Sprite);
	CC_SYNTHESIZE(CCAction*, danceAction, DanceAction);
	MapLocation *map;
};

#endif