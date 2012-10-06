#include"MapLocation.h"
#pragma once
class AnimalUnit
{
public:
	AnimalUnit(MapLocation* _initLocation, MapLocation* _bornLocation);
	~AnimalUnit(void);
	MapLocation* getLocation();
	//MapLocation* setLocation();
	void born();//tu chuong ra duong
	void go(int path);//di them dc path buoc
	void success(int x);//den dich buoc thu x
	void die();//chet, ve lai chuong
private:
	MapLocation* location;//vi tri hien tai
	MapLocation* initLocation;//vi tri trong chuong
	MapLocation* bornLocation;
	int path_went;//doan duong da di
	
};
