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
	CCPoint getBornLocation();
	void printOutDebugInfo();
	void playSelectSound();
private:
	CC_SYNTHESIZE_READONLY(Animals* ,team, Team);
	bool onWay;
	CC_SYNTHESIZE_READONLY(int, finishedStep, FinishStep);
	CC_SYNTHESIZE_READONLY(CCPoint, location, Location);//vi tri hien tai
	CC_SYNTHESIZE_READONLY(CCPoint, initLocation, InitLocation);//vi tri trong chuong
	CC_SYNTHESIZE_READONLY(int, path_went, PathWent);//doan duong da di

	CCNode *parent;
	CC_SYNTHESIZE_READONLY(CCSprite*, sprite, Sprite);
	CC_SYNTHESIZE_READONLY(CCMenuItemSprite*, button,Button);
	CC_SYNTHESIZE_READONLY(CCAction*, danceAction, DanceAction);
	CC_SYNTHESIZE_READONLY(CCFiniteTimeAction*, exploreAction, ExploreAction);

	MapLocation *map;
	//sound
	const char* move_sound;
	const char* die_sound;
	const char* kick_sound;
	const char* born_sound;
	const char* finish_sound;
	const char* select_sound;
};

#endif