#include "Animals.h"
/*
Chua thong tin ve 1 phe
*/

Animals::Animals(int offset, CCNode* _p, MapLocation *_m)
{
	this->map = _m;
	this->parent = _p;
	unit0 = new AnimalUnit(offset,_p,map->getPoint(0,56),map);
	unit1 = new AnimalUnit(offset,_p,map->getPoint(0,57),map);
	unit2 = new AnimalUnit(offset,_p,map->getPoint(0,58),map);
	unit3 = new AnimalUnit(offset,_p,map->getPoint(0,59),map);
	//TODO anything difference here
}


Animals::~Animals(void)
{
	//TODO release all unit
}
