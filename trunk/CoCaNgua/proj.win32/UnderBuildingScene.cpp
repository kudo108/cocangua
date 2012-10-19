#include "UnderBuildingScene.h"
#include "Config.h"
#include "MenuScene.h"

using namespace cocos2d;

bool UnderBuildingScene::init()
{
	if(!CCScene::init()) return false;
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCArray *menuArray = CCArray::create();
	
	CCMenuItemFont* loseLabel = CCMenuItemFont::create("UNDER CONSTRUCTION");
	loseLabel->setFontSizeObj(Config::objectFontSize*1.5);
	//loseLabel->setColor(ccBLACK);
	loseLabel->setPosition(ccp(size.width/2, size.height/2 + 120));
	menuArray->addObject(loseLabel);

	CCMenuItemFont* menuButton = CCMenuItemFont::create(
										"Back to Menu",
										this,
										menu_selector(UnderBuildingScene::menuCallBack));
	menuButton->setFontSizeObj(Config::objectFontSize);
	//menuButton->setColor(ccBLACK);
	menuButton->setPosition(ccp(size.width/2, size.height/2 - 120));
	menuArray->addObject(menuButton);
	
	CCMenu* pMenu = CCMenu::createWithArray(menuArray);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);
	return true;
}

void UnderBuildingScene::menuCallBack(CCObject *sender){
	CCDirector::sharedDirector()->replaceScene(MenuScene::create());
}