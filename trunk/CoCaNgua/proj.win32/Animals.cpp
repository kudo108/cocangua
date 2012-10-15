#include "Animals.h"
#include "Config.h"
/*
Chua thong tin ve 1 phe
*/

Animals::Animals(int tag)
{
	switch(tag)
	{
	case 0:
		{
			/*unit0 = new AnimalUnit(&(map->getInitLocation(tag, 0)), Config::animal0_init_image);
			unit1 = new AnimalUnit(&(map->getInitLocation(tag, 1)), Config::animal0_init_image);
			unit2 = new AnimalUnit(&(map->getInitLocation(tag, 2)), Config::animal0_init_image);
			unit3 = new AnimalUnit(&(map->getInitLocation(tag, 3)), Config::animal0_init_image);*/
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
		{
			break;
		}
	};

}


Animals::~Animals(void)
{
	//TODO release all unit
}

void Animals::setMap(MapLocation *m)
{
	this->map = m;
}