
#include "MapLocation.h"
#include "cocos2d.h"

using namespace cocos2d;

MapLocation::MapLocation(int _winSize)
{
	this->winSize = _winSize;
	this->scale = winSize/1024;
	p1 = 45*scale;
	pMid=512*scale;
	pStep1 = 50*scale;
	pStepMid = 117*scale;
	//init wayLocation
	wayLocation[0] = ccp(p1,pMid);
		//anyone do here for me, for love, for neptune
		//TODO
	wayLocation[55]=ccp(p1,(pMid-pStepMid));
	
	//init finishLocation
	//quan dau tien, tag=0, theo dung thu tu cua wayLocation
	//1,2,3,4,5,6
	finishLocation[0] = ccp((p1+pStep1),pMid);
	//TODO
	finishLocation[15] = ccp(pMid, (p1+6*pStep1));
	
	//init initLocation - diem trong chuong
	initLocation[0] = ccp(0,0);
	//TODO
	initLocation[15] = ccp(0,0);
}


MapLocation::~MapLocation(void)
{
	for(int i = 0; i<56; i++)
	{
		wayLocation[i].autorelease();
	}
	for(int i = 0; i<24; i++)
	{
		finishLocation[i].autorelease();
	}
	for(int i = 0; i<16; i++)
	{
		finishLocation[i].autorelease();
	}
}

CCPoint MapLocation::getPoint(int index)
{
	return this->wayLocation[index];
}

CCPoint *MapLocation::getPointNextOf(CCPoint currentLocation,int step)
	//tra ve cac diem tiep theo khi so xuc xac dc step buoc
{
	CCPoint result[12];
	int currentIndex = getIndexLocation(currentLocation);
	int i =1;
	for(i; i <=step; i++)
	{
		if(currentIndex+i >=48)
		{
			currentIndex = currentIndex+step-48;
		}
		result[i] = wayLocation[currentIndex];
	}
	if (step <12) result[i+1] = ccp(-1,-1);
	return result;
	//tu ket qua nay, nhay tung nac qua cac diem:D
}
int MapLocation::getIndexLocation(cocos2d::CCPoint point)
{
	for(int i = 0; i < 56; i++)
	{
		if(wayLocation[i].equals(point)) return i;
	}
	return -1;
}

CCPoint *MapLocation::getFinishPoint(int step, int tag)
{
	CCPoint result[6];
	int i = 0;
	for(i; i < step; i++)
	{
		result[i] = finishLocation[tag*4+i];
	}
	if(step < 5) result[i+1] = ccp(-1,-1);
	return result;
}
CCPoint MapLocation::getFirstWayPoint(int tag)
{
	return wayLocation[14*tag];
}