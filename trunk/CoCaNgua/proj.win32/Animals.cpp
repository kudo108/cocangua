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
	
	//create menuSprite
	this->teamSprite = CCSprite::createWithTexture(unit0->getSprite()->getTexture());
	this->teamSprite->setPosition(ccp(300,300));
	teamSprite->retain();
	this->spriteAction = (CCAction*)unit0->getDanceAction()->copy();
	spriteAction->retain();
}


Animals::Animals(){
	
}

Animals::~Animals(void)
{
	delete unit0;
	delete unit1;
	delete unit2;
	delete unit3;
}

void Animals::afterDie(){
	//MusicHelper::playEffect(unit0->die_sound, false);
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