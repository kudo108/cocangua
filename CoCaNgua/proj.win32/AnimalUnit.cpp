#include "AnimalUnit.h"
#include "Config.h"
#include "ClassicGameLayer.h"

/*
Chua nhung thong tin ve 1 con co
*/

AnimalUnit::AnimalUnit(int offset, CCNode* parent,CCPoint _initLocation, MapLocation *_m)
{
	this->map = _m;
	this->initLocation = _initLocation;//vi tri trong chuong
	this->location = _initLocation;
	this->path_went = -1;

	//setup danceAction
	const char* imageLink="";
	const char* plistLink="";
	char* temp="";
	switch(offset)
	{
	case 0:
		{
			imageLink=Config::animal0_init_image;
			plistLink=Config::animal0_init_plist;
			temp="pig%d copy.png";
			break;
		}
	case 1:
		{
			imageLink=Config::animal1_init_image;
			plistLink=Config::animal1_init_plist;
			temp="pig%d copy.png";//TODO
			break;
		}
	case 2:
		{
			imageLink=Config::animal2_init_image;
			plistLink=Config::animal2_init_plist;
			temp="pig%d copy.png";//TODO
			break;
		}
	case 3:
		{
			imageLink=Config::animal3_init_image;
			plistLink=Config::animal3_init_plist;
			temp="pig%d copy.png";//TODO
			break;
		}
	default: 
		break;
	}
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plistLink);
	CCSpriteBatchNode *danceSpriteBatchNode =  CCSpriteBatchNode::create(imageLink);
	char fn[128];
	CCAnimation* danceAnim =CCAnimation::create();
	
	for (int i = 1; i <= 2; i++) 
	{
		sprintf(fn, temp, i);
		CCSpriteFrame* pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fn);
		danceAnim->addSpriteFrame(pFrame);
	}
	sprintf(fn,temp,1);
    danceAnim->setDelayPerUnit(0.5f);
	this->sprite = CCSprite::createWithSpriteFrameName(fn);
	this->sprite->retain();

	danceAction = CCRepeatForever::create(CCAnimate::create(danceAnim));
	danceAction->setOriginalTarget(sprite);
	danceAction->retain();

	//create menu
	button = CCMenuItemSprite::create(sprite,sprite,sprite,parent,menu_selector(ClassicGameLayer::goCallback));
	button->setUserData(this);
	button->setPosition(location);
	button->retain();

	CCMenu* pMenu = CCMenu::createWithItem(button);
	pMenu->setPosition(CCPointZero);
	parent->addChild(pMenu,1);
	//run action
	dance();
}
CCPoint AnimalUnit::getLocation(){
	return this->location;
}

AnimalUnit::~AnimalUnit(void)
{
	this->sprite->autorelease();
	this->button->autorelease();
	this->danceAction->autorelease();
}
void AnimalUnit::born()
{//tu chuong ra duong
	this->location = this->initLocation;
}
void AnimalUnit::go(int step)
{//di them dc step buoc
	//TODO 
	CCPoint next = map->getNextPoint(Config::WAYMAP,location,step);
	CCAction *moveAction = CCMoveTo::create(5.0f,next);
	this->button->runAction(moveAction);
}
void AnimalUnit::finish(int x)
{//den dich buoc thu x
	//TODO
}
void AnimalUnit::die()
{//chet, ve lai chuong
	//TODO
}
void AnimalUnit::dance()
{
	this->sprite->runAction(danceAction);
}
