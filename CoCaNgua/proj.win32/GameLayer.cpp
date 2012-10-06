#include "MenuScene.h"
#include "GameLayer.h"
#include "cocos2d.h"

using namespace cocos2d;

GameLayer::GameLayer(void)
{
}

GameLayer::~GameLayer(void)
{
}

bool GameLayer::init()
{
	if(!CCLayer::init()) return false;

	return true;
}

void GameLayer::saveGameCallback(CCObject *sender)
{
	//save game
}
void GameLayer::quitGameCallback(CCObject *sender)
{
	MenuScene *menuScene = MenuScene::create();
	CCDirector::sharedDirector()->replaceScene(menuScene);
	//back to menu
}
void GameLayer::ruleCallback(CCObject *sender)
{
	//show menu
}
int GameLayer::soXiNgau()
{
	srand ( time(NULL) );
	return rand()%6+1;
}

void GameLayer::xingauCallback(CCObject *sender)
{
}