#ifndef _ANIMAL_UNIT_H_
#define _ANIMAL_UNIT_H_

#include "cocos2d.h"
#include "MapLocation.h"
#include "Animals.h"

class Animals;

using namespace cocos2d;

class AnimalUnit
{
public:
	AnimalUnit(Animals* team, CCNode *parent,CCPoint _initLocation, MapLocation *_m);
	AnimalUnit(void);
	~AnimalUnit(void);
	float born();//tu chuong ra duong
	float go(int step);//di them dc step buoc
	float finish();//den dich them 1 buoc
	void die(int step);//chet, ve lai chuong
	void kick(int step);// da sau step buoc
	void dance();//luc lac luc lac =))
	void explore();
	bool isOnInitLocation();//o trong chuong
	bool isOnWay();//dang o tren duong di
	bool isOnStartPosition(AnimalUnit* unit, int team);//o ngay vi tri xuat phat
	CCPoint getBornLocation();
	CCPoint getMileStone(CCPoint point1, CCPoint point2, float deltaX, float deltaY);
	void printOutDebugInfo();
	void playSelectSound();
	
private:
	CC_SYNTHESIZE_READONLY(Animals* ,team, Team);
	CC_SYNTHESIZE(bool, onWay, OnWay);
	CC_SYNTHESIZE(int, finishedStep, FinishStep);
	CC_SYNTHESIZE(CCPoint, location, Location);//vi tri hien tai
	CC_SYNTHESIZE(CCPoint, initLocation, InitLocation);//vi tri trong chuong
	CC_SYNTHESIZE(int, path_went, PathWent);//doan duong da di

	CC_SYNTHESIZE(CCNode*, parent, Parent);
	CC_SYNTHESIZE_READONLY(CCSprite*, sprite, Sprite);
	CC_SYNTHESIZE_READONLY(CCMenuItemSprite*, button,Button);
	CC_SYNTHESIZE_READONLY(CCAction*, danceAction, DanceAction);
	CC_SYNTHESIZE_READONLY(CCFiniteTimeAction*, exploreAction, ExploreAction);

	MapLocation *map;
	
	
};

#endif