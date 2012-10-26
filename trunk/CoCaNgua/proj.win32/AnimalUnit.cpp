#include "AnimalUnit.h"
#include "Config.h"
#include "MapLocation.h"
#include "GameScene.h"
#include "MusicHelper.h"

/*
Chua nhung thong tin ve 1 con co
*/

AnimalUnit::AnimalUnit(Animals* _team, CCNode* _p,CCPoint _initLocation, MapLocation *_m)
{
	this->map = _m;
	this->initLocation = _initLocation;//vi tri trong chuong
	this->location = _initLocation;
	this->path_went = -1;
	this->finishedStep = 0;
	this->team = _team;
	onWay = false;
	//this->isExploring = false;
	parent = _p;

	//setup danceAction
	const char* imageLink="";
	const char* plistLink="";
	char* temp="";
	switch(team->getTeamNo())
	{
	case 0:
		{
			imageLink=Config::animal0_init_image;
			plistLink=Config::animal0_init_plist;
			temp="pig%d copy.png";
			move_sound=MusicHelper::animal0_move_sound;
			die_sound=MusicHelper::animal0_die_sound;
			kick_sound=MusicHelper::animal_kick_sound;
			born_sound=MusicHelper::animal_born_sound;
			finish_sound=MusicHelper::animal_finish_sound;
			select_sound=MusicHelper::animal0_select_sound;
			break;
		}
	case 1:
		{
			imageLink=Config::animal1_init_image;
			plistLink=Config::animal1_init_plist;
			temp="Duck-%d.png";
			move_sound=MusicHelper::animal1_move_sound;
			die_sound=MusicHelper::animal1_die_sound;
			kick_sound=MusicHelper::animal_kick_sound;
			born_sound=MusicHelper::animal_born_sound;
			finish_sound=MusicHelper::animal_finish_sound;
			select_sound=MusicHelper::animal1_select_sound;
			break;
		}
	case 2:
		{
			imageLink=Config::animal2_init_image;
			plistLink=Config::animal2_init_plist;
			temp="horse%d.png";
			move_sound=MusicHelper::animal2_move_sound;
			die_sound=MusicHelper::animal2_die_sound;
			kick_sound=MusicHelper::animal_kick_sound;
			born_sound=MusicHelper::animal_born_sound;
			finish_sound=MusicHelper::animal_finish_sound;
			select_sound=MusicHelper::animal2_select_sound;
			break;
		}
	case 3:
		{
			imageLink=Config::animal3_init_image;
			plistLink=Config::animal3_init_plist;
			temp="dog%d.png";
			move_sound=MusicHelper::animal3_move_sound;
			die_sound=MusicHelper::animal3_die_sound;
			kick_sound=MusicHelper::animal_kick_sound;
			born_sound=MusicHelper::animal_born_sound;
			finish_sound=MusicHelper::animal_finish_sound;
			select_sound=MusicHelper::animal3_select_sound;
			break;
		}
	default: 
		break;
	}
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plistLink);
	//CCSpriteBatchNode *danceSpriteBatchNode =  CCSpriteBatchNode::create(imageLink);
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
	button = CCMenuItemSprite::create(sprite,sprite,sprite,parent,menu_selector(GameScene::buttonSelectCallback));
	button->setUserData(this);
	button->setPosition(location);
	button->retain();

	CCMenu* pMenu = CCMenu::createWithItem(button);
	pMenu->setPosition(CCPointZero);
	parent->addChild(pMenu,1);

	//explore Action 
	//load effect
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(Config::disappearEffect_plist);
	//CCSpriteBatchNode *effectSpriteSheet =  CCSpriteBatchNode::create(Config::disappearEffect_texture);
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

AnimalUnit::~AnimalUnit(void)
{
	this->sprite->release();
	this->button->release();
	this->danceAction->release();
}
float AnimalUnit::born()
{//tu chuong ra duong
	MusicHelper::playEffect(this->born_sound, false);
	CCPoint next = getBornLocation();
	float time = Config::animalNormalMoveTime*2;//2x faster
	CCFiniteTimeAction *moveAction = CCMoveTo::create(time,next);
	location = next;
	this->button->runAction(moveAction);
	this->team->increasePointByBorn();
	onWay = true;
	path_went = 1;
	CCLog("Unit born at %f, %f", location.x, location.y);
	return time;
}
float AnimalUnit::go(int step)
{//di them dc step buoc
	
	MusicHelper::playEffect(this->move_sound, false);
	float time = Config::animalNormalMoveTime;
	CCArray *listGo = CCArray::create();
	CCPointArray* next = map->getNextWay();
	for(int i = 0; i < step; i++)
	{
		listGo->addObject(CCMoveTo::create(time, next->getControlPointAtIndex(i)));
	}
	CCFiniteTimeAction *moveAction = CCSequence::create(listGo);
	this->location = next->getControlPointAtIndex(step-1);
	this->button->runAction(moveAction);

	//increase point of team
	this->team->increasePointByGo(step);
	this->path_went+=step;
	CCLog("Move unit %d step to %f, %f", step, next->getControlPointAtIndex(step-1).x, next->getControlPointAtIndex(step-1).y);
	return time*step;
}
float AnimalUnit::finish()
{//den dich buoc thu x
	MusicHelper::playEffect(finish_sound, false);
	float time = Config::animalNormalMoveTime;
	CCPoint next = map->getFinishLocation(team->getTeamNo(),finishedStep);
	CCAction* move = CCMoveTo::create(time,next);
	this->location = next;
	button->runAction(move);
	this->team->increasePointByFinish(1);
	finishedStep++;
	//update to team
	if(finishedStep == (6 - team->getUnitFinished())) // 6-0 // 5-1 // 4-2 // 3-3
	{
		team->increaseFinished();
	}
	CCLog("Unit finished to %d", finishedStep);
	return time;
}
void AnimalUnit::die(int step)
{//chet, ve lai chuong
	MusicHelper::playEffect(this->die_sound, false);
	float time = Config::animalNormalMoveTime*step;
	if(step <=0)//chet do con khac born
	{
		time = Config::animalNormalMoveTime*2;
	}
	CCAction *action = CCSequence::createWithTwoActions(CCDelayTime::create(time),
														CCMoveTo::create(0.01f,initLocation));
	button->runAction(action);
	location = initLocation;
	path_went = 0;
	onWay=false;
	CCLog("Unit died");
}
void AnimalUnit::dance()
{
	this->sprite->runAction(danceAction);
}
void AnimalUnit::explore()
{
	this->sprite->runAction(exploreAction);
}
bool AnimalUnit::isOnInitLocation()
{
	if (location.equals(initLocation)) return true;
	return false;
}
bool AnimalUnit::isOnWay()
{
	return onWay;
}
CCPoint AnimalUnit::getBornLocation()
{
	return map->getStartLocation(team->getTeamNo());
}
void AnimalUnit::kick(int step)
{
	this->team->increasePointByKick();
}
void AnimalUnit::printOutDebugInfo()
{
	CCLog("----unit debug info----");
	CCLog("--location  = %f %f", location.x, location.y);
	CCLog("--path_went = %d",path_went);
	CCLog("--isOnWay = %s",onWay?"true":"false");
	CCLog("--finishedStep = %d",finishedStep);
	CCLog("----end----------------");
}
void AnimalUnit::playSelectSound()
{
	MusicHelper::playEffect(select_sound, false);
}