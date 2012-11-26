#ifndef _MAP_LOCATION_H_
#define _MAP_LOCATION_H_

#include "cocos2d.h"

using namespace cocos2d;

class MapLocation
{
public:
	MapLocation(int winSize, CCNode* parent);
	~MapLocation(void);
	
	void getNextLocationsInWay(CCPoint current,int step);//duong di
	CCPoint getStartLocation(int teamNo);//diem ra quan
	CCPoint getFinishLocation(int teamNo,int step);//diem finish
	CCPoint getInitLocation(int teamNo,int teamUnit);//diem trong chuong
	int getIndexLocation(CCPoint point);
	CCPoint getNextLocationInWay(int current,int step);

	int wayColision[56];
	int finishColision[24];
	int startColision[16];
	void drawWay();
private:
	float winSize;
	float scale;
	
	float margin;
	float stepLength;
	float stepEnd;
	float center;
	
	CCPoint finishLocation0[6];
	CCPoint finishLocation1[6];
	CCPoint finishLocation2[6];
	CCPoint finishLocation3[6];
	CCPoint wayLocation[56];
	CCPoint initLocation[16];
	
	//nextWay array
	CC_SYNTHESIZE(CCPointArray*, nextWay, NextWay);
	void resetNextWay();

	CCNode* parent;
};

#endif