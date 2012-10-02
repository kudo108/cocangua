#include "AnimalUnit.h"
#include "MapLocation.h"
/*
Chua nhung thong tin ve 1 con co
*/

AnimalUnit::AnimalUnit(MapLocation* _initLocation, MapLocation* _bornLocation)
{
	this->initLocation = _initLocation;
	this->bornLocation = _bornLocation;
	this->location = _initLocation;
}
MapLocation* AnimalUnit::getLocation(){
	return this->location;
}

AnimalUnit::~AnimalUnit(void)
{
	//nothing to do
}
void AnimalUnit::born(){//tu chuong ra duong
	this->location = this->bornLocation;
}
void AnimalUnit::go(int path){//di them dc path buoc
	
}
void AnimalUnit::success(int x){//den dich buoc thu x

}
void AnimalUnit::die(){//chet, ve lai chuong

}