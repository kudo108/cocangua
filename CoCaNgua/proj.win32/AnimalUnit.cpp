#include "AnimalUnit.h"
#include "Config.h"
#include "ClassicGameLayer.h"
#include "MapLocation.h"

/*
Chua nhung thong tin ve 1 con co
*/

AnimalUnit::AnimalUnit(Animals* _team, CCNode* _p,CCPoint _initLocation, MapLocation *_m)
{
	this->map = _m;
	this->initLocation = _initLocation;//vi tri trong chuong
	this->location = _initLocation;
	this->path_went = -1;
	this->team = _team;
	//this->isExploring = false;
	parent = _p;

	//setup danceAction
	const char* imageLink="";
	const char* plistLink="";
	char* temp="";
	switch(team->teamNo)
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
			temp="Duck-%d.png";//TODO
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
	button = CCMenuItemSprite::create(sprite,sprite,sprite,parent,menu_selector(ClassicGameLayer::selectCallback));
	button->setUserData(this);
	button->setPosition(location);
	button->retain();

	CCMenu* pMenu = CCMenu::createWithItem(button);
	pMenu->setPosition(CCPointZero);
	parent->addChild(pMenu,1);

	//explore Action 
	//load effect
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(Config::disappearEffect_plist);
	CCSpriteBatchNode *effectSpriteSheet =  CCSpriteBatchNode::create(Config::disappearEffect_texture);
//	char fn[128];
	CCAnimation* effectAnimation =CCAnimation::create();
	for (int i = 0; i <= 7; i++) 
	{
		sprintf(fn, "move-effect-%d.png", i);
		CCSpriteFrame* pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fn);
		effectAnimation->addSpriteFrame(pFrame);
	}
    effectAnimation->setDelayPerUnit(0.1f);
	exploreAction = CCAnimate::create(effectAnimation);
	exploreAction->setOriginalTarget(sprite);
	exploreAction->retain();
	dance();
}
CCPoint AnimalUnit::getLocation(){
	return this->location;
}

AnimalUnit::~AnimalUnit(void)
{
	this->button->autorelease();
	this->sprite->autorelease();
	this->danceAction->autorelease();
}
void AnimalUnit::born()
{//tu chuong ra duong
	CCPoint next = map->getInitLocation(team->teamNo);;
	float time = ccpDistance(location, next)/(Config::animalNormalSpeed*2);//2x faster
	CCFiniteTimeAction *moveAction = CCMoveTo::create(time,next);
	location = next;
	this->button->runAction(moveAction);
	this->team->increasePointByBorn();
	CCLog("Unit born at %d, %d", location.x, location.y);
}
void AnimalUnit::go(int step)
{//di them dc step buoc
	//TODO 
	this->sprite->stopAllActions();
	//explore();
	// may con heo o trong chuong, cho no vao vi tri dau tien de di
	if( this->location.equals(map->wayLocation[56])||
		this->location.equals(map->wayLocation[57])||
		this->location.equals(map->wayLocation[58])||
		this->location.equals(map->wayLocation[59]))
		this->location = map->wayLocation[0];

	int i = 1 ;
	CCPoint listGo [12];
	listGo[0] = this->location;
	//listGo = CCArray::create();
	for(i; i < 12; i++){
		if(i <= step){
			CCPoint next = map->getNextPoint(Config::WAYMAP,location,1);
			listGo[i] = next;
			this->location = next;
		}
		else listGo[i] = this->location;
	}
	float time = ccpDistance(location, map->getNextPoint(Config::WAYMAP,location,1))/(Config::animalNormalSpeed);
	CCFiniteTimeAction *moveAction = CCSequence::actions(
		CCMoveTo::create(time,listGo[0]),
		CCMoveTo::create(time,listGo[1]),
		CCMoveTo::create(time,listGo[2]),
		CCMoveTo::create(time,listGo[3]),
		CCMoveTo::create(time,listGo[4]),
		CCMoveTo::create(time,listGo[5]),
		CCMoveTo::create(time,listGo[6]),
		CCMoveTo::create(time,listGo[7]),
		CCMoveTo::create(time,listGo[8]),
		CCMoveTo::create(time,listGo[9]),
		CCMoveTo::create(time,listGo[10]),
		CCMoveTo::create(time,listGo[11]),NULL
	);
	this->button->runAction(moveAction);

	//dance();
	//increase point of team
	this->team->increasePointByGo(step);
	//CCLog("Move unit %d step to %d, %d", step, next.x, next.y);
}
void AnimalUnit::finish(int x)
{//den dich buoc thu x
	//TODO
	this->team->increasePointByFinish(x);
}
void AnimalUnit::die()
{//chet, ve lai chuong
	//TODO
}
void AnimalUnit::dance()
{
	this->sprite->runAction(danceAction);
}
void AnimalUnit::explore()
{
	this->sprite->runAction(exploreAction);
}