#ifndef _MAP_LOCATION_H_
#define _MAP_LOCATION_H_
#include "cocos2d.h"
using namespace cocos2d;
class MapLocation
{
public:
	MapLocation(int winSize);
	~MapLocation(void);
	CCPoint *getPointNextOf( CCPoint currentLocation,int step);
	CCPoint *getFinishPoint(int step, int tag);
	CCPoint getFirstWayPoint(int tag);
private:
	int winSize;
	float scale;
	CCPoint getPoint(int index);
	CCPoint wayLocation[48];
	CCPoint finishLocation[24];
	CCPoint initLocation[16];
	int getIndexLocation(CCPoint point);
	float p1;
	float pMid;
	float pStep1;
	float pStepMid;
};

#endif