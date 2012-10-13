#include "TrailerScene.h"
#include "MenuScene.h"

using namespace cocos2d;


void TrailerScene::load_Trailer()
{
}

void TrailerScene::callMenu()
{
	MenuScene *menuScene = MenuScene::create();
	CCDirector::sharedDirector()->replaceScene(menuScene);
}

bool TrailerScene::init()
{
	//sau nay bo cai nay
	this->runAction( CCSequence::create(
                                CCDelayTime::create(1),
                                CCCallFunc::create(this, 
                                callfunc_selector(TrailerScene::callMenu)),
                                NULL));//callMenu();
	return true;
}
