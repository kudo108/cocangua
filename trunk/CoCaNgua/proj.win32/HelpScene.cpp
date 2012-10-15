#include "HelpScene.h"
#include "MenuScene.h"
#include "Config.h"

using namespace cocos2d;


bool HelpScene::init()
{
	if(!CCScene::init()) return false;

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCArray *menuArray = CCArray::create();

	//create button
	CCMenuItemFont* previousButton = CCMenuItemFont::create(
										"<",
										this,
										menu_selector(HelpScene::previousCallBack));

	previousButton->setFontSizeObj(Config::objectFontSize);
	previousButton->setPosition(ccp(20, size.height/2));
	menuArray->addObject(previousButton);

	CCMenuItemFont* nextButton = CCMenuItemFont::create(
										">",
										this,
										menu_selector(HelpScene::nextCallBack));

	nextButton->setFontSizeObj(Config::objectFontSize);
	nextButton->setPosition(ccp(size.width - 20, size.height/2));
	menuArray->addObject(nextButton);

	CCMenuItemFont* pMenuButton = CCMenuItemFont::create(
										"Menu",
										this,
										menu_selector(HelpScene::menuCallback));
	
	pMenuButton->setFontSizeObj(Config::objectFontSize);
	pMenuButton->setPosition(ccp(size.width/2, 30));
	menuArray->addObject(pMenuButton);
	CCMenu* pMenu = CCMenu::createWithArray(menuArray);

	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);

	return true;
}

void HelpScene::previousCallBack(CCObject* sender){
	Config::playEffect(Config::sfxButton, false);
}

void HelpScene::nextCallBack(CCObject* sender){
	Config::playEffect(Config::sfxButton, false);
}

void HelpScene::menuCallback(CCObject *sender)
{
	Config::playEffect(Config::sfxButton, false);
	MenuScene *menuScene = MenuScene::create();
	CCDirector::sharedDirector()->replaceScene(menuScene);	
}
