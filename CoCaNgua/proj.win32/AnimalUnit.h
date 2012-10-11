#ifndef _ANIMAL_UNIT_H_
#define _ANIMAL_UNIT_H_

#include"MapLocation.h"

class AnimalUnit
{
public:
	AnimalUnit(MapLocation* _initLocation, MapLocation* _bornLocation);
	~AnimalUnit(void);
	MapLocation* getLocation();
	//MapLocation* setLocation();
	void born();//tu chuong ra duong
	void go(int step);//di them dc step buoc
	void finish(int step);//den dich buoc thu x
	void die();//chet, ve lai chuong
private:
	MapLocation* location;//vi tri hien tai
	MapLocation* initLocation;//vi tri trong chuong
	//MapLocation* bornLocation;
	int path_went;//doan duong da di
	
};

#endif