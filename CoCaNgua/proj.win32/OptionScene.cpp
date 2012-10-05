#include "OptionScene.h"
#include "cocos2d.h"
#include "MenuScene.h"
#include "Config.h"

using namespace cocos2d;

OptionScene::OptionScene(void)
{
}


OptionScene::~OptionScene(void)
{
}

bool OptionScene::init()
{
	if( !CCScene::init()) return false;
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//create button
	CCMenuItemFont* pMenuButton = CCMenuItemFont::create(
										"Menu",
										this,
										menu_selector(OptionScene::menuCallback));
	
	pMenuButton->setFontSizeObj(Config::objectFontSize);
	pMenuButton->setPosition(ccp(size.width/2, 30));
	CCMenu* pMenu = CCMenu::createWithItem(pMenuButton);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);
	
	return true;
}
void OptionScene::menuCallback(CCObject *sender)
{
	MenuScene *menuScene = MenuScene::create();
	CCDirector::sharedDirector()->replaceScene(menuScene);	
}
