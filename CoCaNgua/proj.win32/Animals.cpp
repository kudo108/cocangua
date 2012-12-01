#include "Animals.h"
#include "MusicHelper.h"
/*
Chua thong tin ve 1 phe
*/

Animals::Animals(int offset, CCNode* _p, MapLocation *_m)
{
	this->map = _m;
	this->parent = _p;
	point = 0;
	teamNo = offset;
	unitFinished = 0;
	unit0 = new AnimalUnit(this,_p,map->getInitLocation(teamNo,0),map);
	unit1 = new AnimalUnit(this,_p,map->getInitLocation(teamNo,1),map);
	unit2 = new AnimalUnit(this,_p,map->getInitLocation(teamNo,2),map);
	unit3 = new AnimalUnit(this,_p,map->getInitLocation(teamNo,3),map);
	switch(teamNo){
	case 0:
		move_sound= (char*)MusicHelper::animal0_move_sound;
		die_sound=(char*)MusicHelper::animal0_die_sound;
		finish_sound=(char*)MusicHelper::animal_finish_sound;
		select_sound=(char*)MusicHelper::animal0_select_sound;
		break;
	case 1:
		move_sound=(char*)MusicHelper::animal1_move_sound;
		die_sound=(char*)MusicHelper::animal1_die_sound;
		finish_sound=(char*)MusicHelper::animal_finish_sound;
		select_sound=(char*)MusicHelper::animal1_select_sound;
		break;
	case 2:
		move_sound=(char*)MusicHelper::animal2_move_sound;
		die_sound=(char*)MusicHelper::animal2_die_sound;
		finish_sound=(char*)MusicHelper::animal_finish_sound;
		select_sound=(char*)MusicHelper::animal2_select_sound;
		break;
	case 3:
		move_sound=(char*)MusicHelper::animal3_move_sound;
		die_sound=(char*)MusicHelper::animal3_die_sound;
		finish_sound=(char*)MusicHelper::animal_finish_sound;
		select_sound=(char*)MusicHelper::animal3_select_sound;
		break;
	default:
		move_sound=(char*)MusicHelper::animal0_move_sound;
		die_sound=(char*)MusicHelper::animal0_die_sound;

		finish_sound=(char*)MusicHelper::animal_finish_sound;
		select_sound=(char*)MusicHelper::animal0_select_sound;
		break;
	}
	kick_sound=(char*)MusicHelper::animal_kick_sound;
	born_sound=(char*)MusicHelper::animal_born_sound;
	//create menuSprite
	this->teamSprite = CCSprite::createWithTexture(unit0->getSprite()->getTexture());
	this->teamSprite->setPosition(ccp(300,300));
	teamSprite->retain();
	this->spriteAction = (CCAction*)unit0->getDanceAction()->copy();
	spriteAction->retain();
}


Animals::~Animals(void)
{
	delete unit0;
	delete unit1;
	delete unit2;
	delete unit3;
}
//play effects
void Animals::beforeDie(CCNode* sender, char* dieSound){
	MusicHelper::playEffect(dieSound, false);
}

void Animals::whileBorn(CCNode* sender, char* bornSound){
	MusicHelper::playEffect(bornSound, false);
}

void Animals::afterFinish(CCNode* sender, char* finishSound){
	MusicHelper::playEffect(finishSound, false);
}
void Animals::increasePointByGo(int step)
{
	point += step*10;
	CCLog("Increase point by %d step = %d",step, point);
}
void Animals::increasePointByKick()
{
	point+= 250;
	CCLog("Increase point by kick = %d", point);
}
void Animals::increasePointByBorn()
{
	point+= 200;
	CCLog("Increase point by born = %d", point);
}
void Animals::increasePointByFinish(int x)
{
	point += x*100;
	CCLog("Increase point by finish at %d = %d", x, point);
}

void Animals::setupTeamSpriteToParent()
{
	teamSprite->runAction(spriteAction);
	parent->addChild(teamSprite);
	teamSprite->retain();
}

void Animals::removeTeamSpriteFromParent()
{	
	teamSprite->stopAllActions();
	teamSprite->removeFromParentAndCleanup(true);
	teamSprite->retain();
}
bool Animals::isFinished()
{
	if(unitFinished >=4) return true;
	return false;
}
void Animals::increaseFinished()
{
	unitFinished++;
}

AnimalUnit *Animals::getUnit(int index){
	switch(index){
	case 0:
		return unit0;
		break;
	case 1:
		return unit1;
		break;
	case 2:
		return unit2;
		break;
	case 3:
		return unit3;
		break;
	default:
		return unit0;
		break;
	}
}