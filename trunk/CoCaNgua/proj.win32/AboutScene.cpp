#include "AboutScene.h"
#include "MenuScene.h"
#include "Config.h"

using namespace cocos2d;

bool AboutScene::init()
{
	if (!CCScene::init()) return false;
	//background
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSprite* background = CCSprite::create(Config::aboutBackground);
	if(background)
	{
		background->setPosition(ccp(size.width/2, size.height/2));
		this->addChild(background);
	}
	//button
	CCMenuItemFont* pMenuButton = CCMenuItemFont::create(
										"Menu",
										this,
										menu_selector(AboutScene::menuCallback));
	pMenuButton->setFontSizeObj(Config::objectFontSize);
	pMenuButton->setPosition(ccp(size.width/2, 30));
	// Create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::createWithItem(pMenuButton);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);
	
	return true;
}

void AboutScene::menuCallback(CCObject *sender)
{
	MenuScene::playButtonEffect();
	MenuScene *menuScene = MenuScene::create();
	CCDirector::sharedDirector()->replaceScene(menuScene);	
}
