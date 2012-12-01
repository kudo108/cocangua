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
			/*move_sound= (char*)MusicHelper::animal0_move_sound;
			die_sound=(char*)MusicHelper::animal0_die_sound;
			finish_sound=(char*)MusicHelper::animal_finish_sound;
			select_sound=(char*)MusicHelper::animal0_select_sound;*/
			break;
		}
	case 1:
		{
			imageLink=Config::animal1_init_image;
			plistLink=Config::animal1_init_plist;
			temp="Duck-%d.png";
			/*move_sound=(char*)MusicHelper::animal1_move_sound;
			die_sound=(char*)MusicHelper::animal1_die_sound;
			finish_sound=(char*)MusicHelper::animal_finish_sound;
			select_sound=(char*)MusicHelper::animal1_select_sound;*/
			break;
		}
	case 2:
		{
			imageLink=Config::animal2_init_image;
			plistLink=Config::animal2_init_plist;
			temp="horse%d.png";
			/*move_sound=(char*)MusicHelper::animal2_move_sound;
			die_sound=(char*)MusicHelper::animal2_die_sound;
			finish_sound=(char*)MusicHelper::animal_finish_sound;
			select_sound=(char*)MusicHelper::animal2_select_sound;*/
			break;
		}
	case 3:
		{
			imageLink=Config::animal3_init_image;
			plistLink=Config::animal3_init_plist;
			temp="dog%d.png";
			/*move_sound=(char*)MusicHelper::animal3_move_sound;
			die_sound=(char*)MusicHelper::animal3_die_sound;
			finish_sound=(char*)MusicHelper::animal_finish_sound;
			select_sound=(char*)MusicHelper::animal3_select_sound;*/
			break;
		}
	default: 
		break;
	}

	/*kick_sound=(char*)MusicHelper::animal_kick_sound;
	born_sound=(char*)MusicHelper::animal_born_sound;*/
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
	parent->addChild(pMenu,10);

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

AnimalUnit::AnimalUnit(){

}

AnimalUnit::~AnimalUnit(void)
{
	this->sprite->release();
	this->button->release();
	this->danceAction->release();
}
float AnimalUnit::born()
{//tu chuong ra duong

	CCPoint next = getBornLocation();
	float time = Config::animalNormalMoveTime*2;//2x faster
	CCFiniteTimeAction *moveAction = CCMoveTo::create(time,next);
	CCCallFunc* callFunc = CCCallFuncND::create(button, callfuncND_selector(Animals::whileBorn), this->getTeam()->born_sound);
	location = next;
	this->button->runAction(CCSequence::create(moveAction, callFunc, NULL));
	
	this->team->increasePointByBorn();

	onWay = true;
	path_went = 1;
	CCLog("Unit born at %f, %f", location.x, location.y);
	return time;
}

float AnimalUnit::go(int step)
{//di them dc step buoc
	//play music during time*step second
	MusicHelper::playEffect(this->getTeam()->move_sound, false);
	float time = Config::animalNormalMoveTime;
	CCArray *listGo = CCArray::create();
	map->getNextLocationsInWay(location,step);
	CCPointArray* next = map->getNextWay();
	for(int i = 0; i < step; i++)
	{
		CCLOG("list go index = %d, point = %f, %f",i,next->getControlPointAtIndex(i).x,next->getControlPointAtIndex(i).y);
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
	
	float time = Config::animalNormalMoveTime;
	CCPoint next = map->getFinishLocation(team->getTeamNo(),finishedStep);
	CCFiniteTimeAction* move = CCMoveTo::create(time,next);
	CCCallFunc* callFunc = CCCallFuncND::create(button, callfuncND_selector(Animals::afterFinish), this->getTeam()->finish_sound);
	this->location = next;
	button->runAction(CCSequence::create(move, callFunc, NULL));
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
	

	float time = Config::animalNormalMoveTime*step;
	if(step <=0)//chet do con khac born
	{
		time = Config::animalNormalMoveTime*2;
	}

	CCArray *arrayAction = CCArray::create();
	arrayAction->addObject(CCDelayTime::create(time - 0.1f));
	//CCPoint tempLocation;
	//float deltaX = location.x - initLocation.x;
	//float deltaY = location.y - initLocation.y;
	//float rate = 1;
	//button->stopAllActions();
	//while(ccpDistance(location, initLocation) != 0){
	//	CCLOG("Location = (%f, %f)", tempLocation.x, tempLocation.y);
	//	tempLocation = getMileStone(location, initLocation, deltaX, deltaY);
	//	CCActionInterval *actionMove = CCMoveTo::create(0.1f,tempLocation);
	//	CCActionInterval *actionScale = CCScaleTo::create(0.03f, rate);
	//	//CCAction *easeIn = CCEaseElastic::create(actionMove, 5);
	//	arrayAction->addObject(actionScale);
	//	arrayAction->addObject(actionMove);
	//	location = tempLocation;
	//	if(rate < 5){
	//		rate*=1.5;
	//	}else{
	//		rate/=1.5;
	//	}
	//}
	//CCActionInterval *actionTo = CCScaleTo::create(0.8f, 2.5f);
	//CCAction *easeIn = CCEaseExponentialIn::create(actionTo);
	
	//CCActionInterval *actionMove = CCMoveTo::create(1.0f,initLocation);
	//CCAction *easeIn = CCEaseExponentialIn::create(actionMove);
	//CCActionInterval *actionScaleUp = CCScaleTo::create(0.7f, 3.0f);
	CCAction *actionMove = CCEaseElasticOut::create(CCMoveTo::create(0.5f,initLocation));
	//CCActionInterval *actionScaleDown = CCEaseExponentialIn::create(CCScaleTo::create(0.3f, 1.0f));
	CCFiniteTimeAction *callfunc = CCCallFuncND::create(button, callfuncND_selector(Animals::beforeDie), this->getTeam()->die_sound);

	arrayAction->addObject(callfunc);
	arrayAction->addObject(actionMove);
	//arrayAction->addObject(actionScaleDown);
	
	CCAction *action = CCSequence::create(arrayAction);
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
	//play music after step*config::unitNormalMoveTime
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

//go from point1 to point2, 1/10 of distance every step
CCPoint AnimalUnit::getMileStone(CCPoint point1, CCPoint point2, float deltaX, float deltaY){
	float deltaXX = point1.x - point2.x;
	float deltaYY = point1.y - point2.y;
	int factor = 2;
	CCLOG("deltaX : %f\tdeltaY : %f", deltaX, deltaY);
	//if(abs(deltaXX) < 5 || abs(deltaYY) < 5) return ccp(point2.x,point2.y);
	if(deltaX > 0){
		if(deltaY > 0){
			return ccp(point1.x - abs(deltaX/factor), point1.y - abs(deltaY/factor));
		}else if(deltaY < 0){
			return ccp(point1.x - abs(deltaX/factor), point1.y + abs(deltaY/factor));
		}else{
			return ccp(point1.x - abs(deltaX/factor),point1.y);
		}
	}else if(deltaX < 0){
		if(deltaY > 0){
			return ccp(point1.x + abs(deltaX/factor), point1.y - abs(deltaY/factor));
		}else if(deltaY < 0){
			return ccp(point1.x + abs(deltaX/factor), point1.y + abs(deltaY/factor));
		}else{
			return ccp(point1.x + abs(deltaX/factor),point1.y);
		}
	}else{
		if(deltaY > 0){
			return ccp(point1.x, point1.y - abs(deltaY/factor));
		}else if(deltaY < 0){
			return ccp(point1.x, point1.y + abs(deltaY/factor));
		}else{
			return ccp(point2.x, point2.y);
		}
	}
}

bool AnimalUnit::isOnStartPosition(AnimalUnit* unit, int teamNo) 
{
	if(unit->getLocation().x == map->getStartLocation(teamNo).x && unit->getLocation().y == map->getStartLocation(teamNo).y)
		return TRUE;
	return FALSE;
}