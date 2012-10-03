#include "TrailerScene.h"
#include "MenuScene.h"
#include "cocos2d.h"

using namespace cocos2d;

TrailerLayer::TrailerLayer(void)
{
}


TrailerLayer::~TrailerLayer(void)
{
}

bool TrailerLayer::init()
{
	return true;
}

void TrailerLayer::load_Trailer()
{
}

void TrailerLayer::callMenu()
{
	MenuScene *menuScene = MenuScene::create();
	CCDirector::sharedDirector()->replaceScene(menuScene);
}
TrailerScene::TrailerScene(void)
{
}


TrailerScene::~TrailerScene(void)
{
}

bool TrailerScene::init()
{
	//sau nay bo cai nay
	this->runAction( CCSequence::create(
                                CCDelayTime::create(3),
                                CCCallFunc::create(this, 
                                callfunc_selector(TrailerLayer::callMenu)),
                                NULL));//callMenu();
	return true;
}
