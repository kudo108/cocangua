#include "RuleScene.h"
#include "Config.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "cocos2d.h"
#include "MusicHelper.h"

bool RuleScene::init(){
	if( !CCScene::init()) return false;

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCArray *menuArray = CCArray::create();

	

	

	CCMenuItemFont* backButton = CCMenuItemFont::create(
										"Back to Game",
										this,
										menu_selector(RuleScene::menuCallBack));

	backButton->setFontSizeObj(20);
	backButton->setPosition(ccp(70, 20));
	menuArray->addObject(backButton);

	CCMenu* pMenu = CCMenu::createWithArray(menuArray);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);

	return true;
}


void RuleScene::menuCallBack(CCObject* sender){
	MusicHelper::playEffect(MusicHelper::sfxButton, false);
	GameScene *gameScene = GameScene::create();
	CCDirector::sharedDirector()->replaceScene(gameScene);
}
