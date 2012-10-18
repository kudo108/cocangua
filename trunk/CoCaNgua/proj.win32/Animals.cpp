#include "Animals.h"
/*
Chua thong tin ve 1 phe
*/

Animals::Animals(int tag, CCNode* _p, MapLocation *_m)
{
	this->map = _m;
	this->parent = _p;
	switch(tag)
	{
	case 0:
		{
			unit0 = new AnimalUnit(0,_p,map->getPoint(0,0),map);
			//TODO
			break;
		}
	case 1:
		{
			//TODO
			break;
		}
	case 2:
		{
			//TODO
			break;
		}
	case 3:
		{
			//TODO
			break;
		}
	default:
			break;
	};
	
}


Animals::~Animals(void)
{
	//TODO release all unit
}
