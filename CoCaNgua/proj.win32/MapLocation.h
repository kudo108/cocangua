#ifndef _MAP_LOCATION_H_
#define _MAP_LOCATION_H_

#include "cocos2d.h"
using namespace cocos2d;

class MapLocation
{
public:
	MapLocation(int winSize, CCNode* parent);
	~MapLocation(void);
	int way;
	int fnR;
	int fnG;
	int fnB;
	int fnY;
	CCPoint wayLocation[56];
	CCPoint getNextPoint(int type,CCPoint current,int step);
	CCPoint getPoint(int map,int index);
	int getIndexLocation(int map,CCPoint point);
	//some function to get point
	CCPoint getBornLocation(int teamNo);
	CCPoint getFinishLocation(int teamNo, int step);
	//some help function for game rule
	bool canBorn(int k1, int k2);
	bool canContinueRoll(int k1, int k2);
	float distance(CCPoint p1, CCPoint p2);
	//some animaltion fucntion
	void lightUp(CCPoint point);
	void deleteAllLightUp();
	void select(CCPoint point);
	void unSelect();
private:
	CCPoint initLocation[16];
	
	CCPoint finishLocation[24];
	float winSize;
	float scale;
	CCPoint finishLocationYellow[24];
	CCPoint finishLocationGreen[24];
	CCPoint finishLocationRed[24];
	CCPoint finishLocationBlue[24];
	float margin;
	float stepLength;
	float stepEnd;
	float center;

	CC_SYNTHESIZE(CCAction*, lightupAction, LightupAction);
	CC_SYNTHESIZE(CCArray*, lightupArray, LightupArray);
	CC_SYNTHESIZE(CCNode*, parent, Parent);
	CC_SYNTHESIZE(CCAction*, selectAction, SelectAction);
	CC_SYNTHESIZE(CCSprite*, selectSprite, SelectSprite);
};

#endif