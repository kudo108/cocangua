#ifndef _ANIMAL_UNIT_H_
#define _ANIMAL_UNIT_H_

#include "cocos2d.h"
using namespace cocos2d;

class AnimalUnit
{
public:
	AnimalUnit(CCPoint* _initLocation, const char* imageLink);
	~AnimalUnit(void);
	CCPoint* getLocation();
	void born();//tu chuong ra duong
	void go(int step);//di them dc step buoc
	void finish(int step);//den dich buoc thu x
	void die();//chet, ve lai chuong
	void dance();//luc lac luc lac =))
private:
	CCPoint* location;//vi tri hien tai
	CCPoint* initLocation;//vi tri trong chuong
	int path_went;//doan duong da di
	cocos2d::CCSprite* sprite;
};

#endif