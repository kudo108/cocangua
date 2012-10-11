#ifndef _ANIMALS_H_
#define _ANIMALS_H_

#include "AnimalUnit.h"
#include "MapLocation.h"
class Animals
{
public:
	Animals(int tag);
	~Animals(void);
	AnimalUnit *unit0;
	AnimalUnit *unit1;
	AnimalUnit *unit2;
	AnimalUnit *unit3;
	void setMap(MapLocation *_map);
private:
	MapLocation *map;
};

#endif