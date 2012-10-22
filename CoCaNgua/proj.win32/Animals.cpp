#include "Animals.h"
/*
Chua thong tin ve 1 phe
*/

Animals::Animals(int offset, CCNode* _p, MapLocation *_m)
{
	this->map = _m;
	this->parent = _p;
	point = 0;
	teamNo = offset;
	unit0 = new AnimalUnit(this,_p,map->getPoint(0,56),map);
	unit1 = new AnimalUnit(this,_p,map->getPoint(0,57),map);
	unit2 = new AnimalUnit(this,_p,map->getPoint(0,58),map);
	unit3 = new AnimalUnit(this,_p,map->getPoint(0,59),map);
	//TODO anything difference here
}


Animals::~Animals(void)
{
	//TODO release all unit
}

unsigned int Animals::getPoint()
{
	return point;
}

void Animals::increasePointByGo(int step)
{
	point += step*10;
	CCLog("Increase point by %d step = %d",step, point);
}
void Animals::increasePointByKick()
{
	point+= 250;
	CCLog("Increase point by kick = %d", point);
}
void Animals::increasePointByBorn()
{
	point+= 200;
	CCLog("Increase point by born = %d", point);
}
void Animals::increasePointByFinish(int x)
{
	point += x*100;
	CCLog("Increase point by finish at %d = %d", x, point);
}