#include "HelpScene.h"
#include "MenuScene.h"
#include "Config.h"

using namespace cocos2d;


bool HelpScene::init()
{
	if(!CCScene::init()) return false;

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	//create button
	CCMenuItemFont* pMenuButton = CCMenuItemFont::create(
										"Menu",
										this,
										menu_selector(HelpScene::menuCallback));
	
	pMenuButton->setFontSizeObj(Config::objectFontSize);
	pMenuButton->setPosition(ccp(size.width/2, 30));
	CCMenu* pMenu = CCMenu::createWithItem(pMenuButton);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);

	return true;
}
void HelpScene::menuCallback(CCObject *sender)
{
	MenuScene::playButtonEffect();
	MenuScene *menuScene = MenuScene::create();
	CCDirector::sharedDirector()->replaceScene(menuScene);	
}
