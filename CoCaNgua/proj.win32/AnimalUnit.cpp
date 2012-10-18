#include "AnimalUnit.h"
#include "Config.h"
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
			//TODO
			break;
		}
	case 2:
		{
			//TODO
			break;
		}
	case 3:
		{
			//TODO
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

	parent->addChild(this->sprite,100);
	this->sprite->setPosition(location);
	this->sprite->retain();

	danceAction = CCRepeatForever::create(CCAnimate::create(danceAnim));
	danceAction->setOriginalTarget(sprite);
	danceAction->retain();


	//run action
	dance();
}
CCPoint AnimalUnit::getLocation(){
	return this->location;
}

AnimalUnit::~AnimalUnit(void)
{
	this->sprite->autorelease();
}
void AnimalUnit::born()
{//tu chuong ra duong
	this->location = this->initLocation;
}
void AnimalUnit::go(int step)
{//di them dc step buoc
	CCPoint next = map->getNextPoint(Config::WAYMAP,location,step);
	CCAction *moveAction = CCMoveTo::create(5.0f,next);
	this->sprite->runAction(moveAction);
}
void AnimalUnit::finish(int x)
{//den dich buoc thu x

}
void AnimalUnit::die()
{//chet, ve lai chuong

}
void AnimalUnit::dance()
{
	this->sprite->runAction(danceAction);
}
