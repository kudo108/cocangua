#ifndef _UNDER_BUILDING_SCENE_H_
#define _UNDER_BUILDING_SCENE_H_

#include "cocos2d.h"

class UnderBuildingScene: public cocos2d::CCScene
{
public:
	virtual bool init();
	void menuCallBack(CCObject *sender);
	CREATE_FUNC(UnderBuildingScene);
};

#endif