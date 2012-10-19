#ifndef _CLASSIC_GAME_SCENE_H_
#define _CLASSIC_GAME_SCENE_H_

#include "ClassicGameLayer.h"
#include "Config.h"
#include "MenuScene.h"

using namespace cocos2d;


bool ClassicGameLayer::init()
{
	if(! CCLayer::init()) return false;
	
	//init map
	map = new MapLocation(600);

	//init animals
	animal0 = new Animals(0,this,map);
	//animal1 = new Animals(1,this,map);
	//animal2 = new Animals(2,this,map);
	//animal3 = new Animals(3,this,map);

	currentTurn=animal0;

	return true;
}

void ClassicGameLayer::goCallback(CCObject *sender)
{
	//CCObject o day la CCMENUitemsprite	
	if(Config::kqXucXac1<=0 || Config::kqXucXac2<=0) return;
	OutputDebugStringW(L"go...............");
	AnimalUnit* unit = (AnimalUnit*) ((CCMenuItemSprite*)sender)->getUserData();
	unit->go(Config::kqXucXac1+Config::kqXucXac2);
	Config::kqXucXac1=Config::kqXucXac2=0;
}

#endif