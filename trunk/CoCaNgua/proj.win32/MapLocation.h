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
	CCPoint getNextPoint(int type,CCPoint current,int step);
	CCPoint getPoint(int map,int index);
	int getIndexLocation(int map,CCPoint point);
	void lightUp(CCPoint point);
	void deleteAllLightUp();
	void select(CCPoint point);
	void unSelect();
	CCPoint wayLocation[60];
private:
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