#ifndef _MAP_LOCATION_H_
#define _MAP_LOCATION_H_

#include "cocos2d.h"
using namespace cocos2d;
class MapLocation
{
public:
	MapLocation(int winSize);
	~MapLocation(void);
	int way;
	int fnR;
	int fnG;
	int fnB;
	int fnY;
	CCPoint getNextPoint(int type,CCPoint current,int step);
	CCPoint getPoint(int map,int index);
	int getIndexLocation(int map,CCPoint point);
private:
	float winSize;
	float scale;
	CCPoint wayLocation[56];
	CCPoint finishLocationYellow[24];
	CCPoint finishLocationGreen[24];
	CCPoint finishLocationRed[24];
	CCPoint finishLocationBlue[24];
	float margin;
	float stepLength;
	float stepEnd;
	float center;

};

#endif