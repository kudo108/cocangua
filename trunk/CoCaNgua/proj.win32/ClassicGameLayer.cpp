#ifndef _CLASSIC_GAME_SCENE_H_
#define _CLASSIC_GAME_SCENE_H_
#define COCOS_DEBUG 1

#include "ClassicGameLayer.h"
#include "Config.h"
#include "MenuScene.h"

using namespace cocos2d;


bool ClassicGameLayer::init()
{
	if(! CCLayer::init()) return false;
	
	//init map
	map = new MapLocation(600, this);

	//init animals
	animal0 = new Animals(0,this,map);
	//animal1 = new Animals(1,this,map);
	//animal2 = new Animals(2,this,map);
	//animal3 = new Animals(3,this,map);


	//create button go
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCMenuItemFont* pButtonGo = CCMenuItemFont::create(
										"Go",
										this,
										menu_selector(ClassicGameLayer::buttonGoCallBack));
	pButtonGo->setFontSizeObj(Config::objectFontSize);
	pButtonGo->setPosition(ccp(size.width-100, 5*60));
	CCMenu* menu= CCMenu::createWithItem(pButtonGo);
	menu->setPosition(CCPointZero);
	this->addChild(menu,10);

	//currentTurn
	currentTurn=animal0;

	return true;
}

void ClassicGameLayer::selectCallback(CCObject *sender)
{

	//CCObject o day la CCMENUitemsprite	
	if(Config::kqXucXac1<=0 || Config::kqXucXac2<=0) return;

	//OutputDebugStringW(L"selected...............");
	unit = (AnimalUnit*) ((CCMenuItemSprite*)sender)->getUserData();
	
	//get array of next point can go
	//lightup these point
	//map->lightUp(map->getPoint(0,5));
	//map->lightUp(map->getPoint(0,6));
	//select amination unit
	map->select(unit->getLocation());
}


void ClassicGameLayer::effectActionDone (CCObject *sender)
{
	CCSprite* sprite = (CCSprite*) sender;
	sprite->release();
}
void ClassicGameLayer::buttonGoCallBack(CCObject *sender)
{
	//delete lightup
	map->deleteAllLightUp();
	//delete select
	map->unSelect(unit->getLocation());
	//move 
	unit->go(Config::kqXucXac1+Config::kqXucXac2);
	
	//unload kqXucXac
	Config::kqXucXac1=Config::kqXucXac2=0;
}
#endif