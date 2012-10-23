#ifndef _ANIMAL_UNIT_H_
#define _ANIMAL_UNIT_H_

#include "cocos2d.h"
#include "MapLocation.h"
#include "Animals.h"

using namespace cocos2d;

class Animals;
class MapLocation;

class AnimalUnit
{
public:
	AnimalUnit(Animals* team, CCNode *parent,CCPoint _initLocation, MapLocation *_m);
	~AnimalUnit(void);
	void born();//tu chuong ra duong
	void go(int step);//di them dc step buoc
	void finish(int step);//den dich buoc thu x
	void die();//chet, ve lai chuong
	void dance();//luc lac luc lac =))
	void explore();
	bool isOnInitLocation();//o trong chuong
	bool isOnWay();//dang o tren duong di
	CCPoint getBornLocation();
private:
	CC_SYNTHESIZE(Animals* ,team, Team);
	bool onWay;
	CC_SYNTHESIZE(CCPoint, location, Location);//vi tri hien tai
	CC_SYNTHESIZE(CCPoint, initLocation, InitLocation);//vi tri trong chuong
	int path_went;//doan duong da di

	CCNode *parent;
	CC_SYNTHESIZE(CCSprite*, sprite, Sprite);
	CC_SYNTHESIZE(CCMenuItemSprite*, button,Button);
	CC_SYNTHESIZE(CCAction*, danceAction, DanceAction);
	CC_SYNTHESIZE(CCFiniteTimeAction*, exploreAction, ExploreAction);
	CC_SYNTHESIZE(CCArray*, listGo, ListGo);

	MapLocation *map;
};

#endif