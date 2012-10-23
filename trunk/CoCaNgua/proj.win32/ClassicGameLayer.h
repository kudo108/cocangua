#ifndef __CLASSICGAME_LAYER_H__
#define __CLASSICGAME_LAYER_H__

#include "Animals.h"

using namespace cocos2d;

class ClassicGameLayer: public cocos2d::CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(ClassicGameLayer);
	void selectCallback(CCObject *sender);
	void effectActionDone(CCObject *sender);
	void buttonGoCallBack(CCObject *sender);
private:
	MapLocation *map;	
	CC_SYNTHESIZE(AnimalUnit *, unit, Unit);//current select unit
	//animals
	CC_SYNTHESIZE(Animals *, animal0, Animal0);
	CC_SYNTHESIZE(Animals *, animal1, Animal1);
	CC_SYNTHESIZE(Animals *, animal2, Animal2);
	CC_SYNTHESIZE(Animals *, animal3, Animal3);
	CC_SYNTHESIZE(Animals *, currentTurn,CurrentTurn);

	CC_SYNTHESIZE(CCMenuItemFont*, team0PointLable, Team0PointLable);
	CC_SYNTHESIZE(CCMenuItemFont*, team1PointLable, Team1PointLable);
	CC_SYNTHESIZE(CCMenuItemFont*, team2PointLable, Team2PointLable);
	CC_SYNTHESIZE(CCMenuItemFont*, team3PointLable, Team3PointLable);
	CC_SYNTHESIZE(CCMenuItemFont*, teamLable, TeamLable);

	void updatePoint(int teamNo);
	void updateTeamLable();
};

#endif