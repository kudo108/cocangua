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
	animal1 = new Animals(1,this,map);
	//animal2 = new Animals(2,this,map);
	//animal3 = new Animals(3,this,map);

	CCArray *menuArray = CCArray::create();
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	
	//Team Lable
	CCMenuItemFont* pTeam0Point = CCMenuItemFont::create("Team 0:");
	menuArray->addObject(pTeam0Point);

	CCMenuItemFont* pTeam1Point = CCMenuItemFont::create("Team 1:");
	menuArray->addObject(pTeam1Point);

	CCMenuItemFont* pTeam2Point = CCMenuItemFont::create("Team 2:");
	menuArray->addObject(pTeam2Point);

	CCMenuItemFont* pTeam3Point = CCMenuItemFont::create("Team 3:");
	menuArray->addObject(pTeam3Point);
	
	for(unsigned int i = 0; i < menuArray->count(); i ++)
	{
		CCMenuItemFont *item = (CCMenuItemFont*)menuArray->objectAtIndex(i);
		item->setFontSizeObj(Config::objectFontSize/2);
		item->setPosition(ccp(size.width-140,size.height/3+i*45+30));
	}
	//point
	team0PointLable = CCMenuItemFont::create("0");
	team0PointLable->setFontSizeObj(Config::objectFontSize/2);
	team0PointLable->setPosition(ccp(size.width-60, size.height/3+30));
	team0PointLable->setColor(ccGREEN);
	menuArray->addObject(team0PointLable);
	team0PointLable->retain();

	team1PointLable = CCMenuItemFont::create("0");
	team1PointLable->setFontSizeObj(Config::objectFontSize/2);
	team1PointLable->setPosition(ccp(size.width-60, size.height/3+75));
	team1PointLable->setColor(ccGREEN);
	menuArray->addObject(team1PointLable);
	team1PointLable->retain();

	team2PointLable = CCMenuItemFont::create("0");
	team2PointLable->setFontSizeObj(Config::objectFontSize/2);
	team2PointLable->setPosition(ccp(size.width-60, size.height/3+120));
	team2PointLable->setColor(ccGREEN);
	menuArray->addObject(team2PointLable);
	team2PointLable->retain();

	team3PointLable = CCMenuItemFont::create("0");
	team3PointLable->setFontSizeObj(Config::objectFontSize/2);
	team3PointLable->setPosition(ccp(size.width-60, size.height/3+165));
	team3PointLable->setColor(ccGREEN);
	menuArray->addObject(team3PointLable);
	team3PointLable->retain();

	//create button go
	CCMenuItemFont* pButtonGo = CCMenuItemFont::create(
										"Go",
										this,
										menu_selector(ClassicGameLayer::buttonGoCallBack));
	pButtonGo->setColor(ccORANGE);
	pButtonGo->setFontSizeObj(Config::objectFontSize);
	pButtonGo->setPosition(ccp(size.width-100, size.height*2/3+20));
	menuArray->addObject(pButtonGo);

	
	//create menu
	CCMenu* menu= CCMenu::createWithArray(menuArray);
	menu->setPosition(CCPointZero);
	this->addChild(menu,10);
	//currentTurn
	currentTurn=animal0;
	//unit
	unit = NULL;

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
	if (unit==NULL) return;
	//delete lightup
	map->deleteAllLightUp();
	//delete select
	map->unSelect();
	//neu o trong chuong + ra quan dc=> ra quan
	unit->born();
	//neu o tren duong di + khong bi can => di chuyen
	unit->go(Config::kqXucXac1+Config::kqXucXac2);
	
	//unload kqXucXac
	Config::kqXucXac1=Config::kqXucXac2=0;
	//unload unit
	unit = NULL;
	//update point
	updatePoint(currentTurn->teamNo);
}
void ClassicGameLayer::updatePoint(int teamNo)
{
	char lable[128];
	switch (teamNo)
	{
	case 0:		
		sprintf(lable, "%d", animal0->getPoint());
		team0PointLable->setString(lable);
		CCLog("updated point team %d = %d", teamNo, animal0->getPoint());
		break;
	case 1:
		sprintf(lable, "%d", animal1->getPoint());
		team1PointLable->setString(lable);
		CCLog("updated point team %d = %d", teamNo, animal1->getPoint());
		break;
	case 2:
		sprintf(lable, "%d", animal2->getPoint());
		team2PointLable->setString(lable);
		CCLog("updated point team %d = %d", teamNo, animal2->getPoint());
		break;
	case 3:
		sprintf(lable, "%d", animal3->getPoint());
		team3PointLable->setString(lable);
		CCLog("updated point team %d = %d", teamNo, animal3->getPoint());
		break;
	default:
		break;
	}
}
#endif