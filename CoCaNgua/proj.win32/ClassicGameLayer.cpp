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
	
	//get winsize
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	OutputDebugStringW(L"go...............");
	AnimalUnit* unit = (AnimalUnit*) ((CCMenuItemSprite*)sender)->getUserData();
	CCPoint currentPosition = unit->getLocation();
	unit->go(Config::kqXucXac1+Config::kqXucXac2);

	//load effect
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(Config::disappearEffect_plist);
	CCSpriteBatchNode *effectSpriteSheet =  CCSpriteBatchNode::create(Config::disappearEffect_texture);
	char fn[128];
	CCAnimation* effectAnimation =CCAnimation::create();
	
	for (int i = 0; i <= 7; i++) 
	{
		sprintf(fn, "move-effect-%d.png", i);
		CCSpriteFrame* pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fn);
		effectAnimation->addSpriteFrame(pFrame);
	}
	
	
    effectAnimation->setDelayPerUnit(0.1f);
     //create sprite first frame from animation first frame
	CCSprite* effect = CCSprite::createWithSpriteFrameName(Config::disappearEffect_image);
	effect->setPosition(currentPosition);

	CCAction *effectAction = CCRepeat::create(CCAnimate::create(effectAnimation),1);
	//effectAction->setOriginalTarget(effect);
	effect->runAction(effectAction);
	this->addChild(effect);

	Config::kqXucXac1=Config::kqXucXac2=0;
	if(effectAction->isDone()) {
		effect->stopAction(effectAction);
		this->removeChild(effect, true);
	}
}


void ClassicGameLayer::effectActionDone (CCObject *sender){
	CCSprite* sprite = (CCSprite*) sender;
	sprite->release();
}
#endif