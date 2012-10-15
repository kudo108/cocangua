#include "GameOverScene.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "Config.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

bool GameOverScene::init(){
	if( !CCScene::init()) return false;
	//stop background music and play sound of game over
	Config::stopBackgroundMusic();
	Config::setIdGameOver(SimpleAudioEngine::sharedEngine()->playEffect(Config::sfxGameOver));

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	//background
	CCSprite* background = CCSprite::create(Config::gameOverBackground);
	if(background){
		background->setPosition(ccp(size.width/2, size.height/2));
		this->addChild(background);
	}

	CCArray *menuArray = CCArray::create();

	CCMenuItemFont* loseLabel = CCMenuItemFont::create(
										"YOU LOSE",
										this,
										menu_selector(GameOverScene::menuCallBack));

	loseLabel->setFontSizeObj(Config::objectFontSize*1.5);
	loseLabel->setColor(ccBLACK);
	loseLabel->setPosition(ccp(size.width/2, size.height/2 + 120));
	menuArray->addObject(loseLabel);

	CCMenuItemFont* restartButton = CCMenuItemFont::create(
										"Restart?",
										this,
										menu_selector(GameOverScene::restartCallBack));

	restartButton->setFontSizeObj(Config::objectFontSize);
	restartButton->setColor(ccBLACK);
	restartButton->setPosition(ccp(size.width/2, size.height/2 - 60));
	menuArray->addObject(restartButton);

	CCMenuItemFont* menuButton = CCMenuItemFont::create(
										"Back to Menu",
										this,
										menu_selector(GameOverScene::menuCallBack));

	menuButton->setFontSizeObj(Config::objectFontSize);
	menuButton->setColor(ccBLACK);
	menuButton->setPosition(ccp(size.width/2, size.height/2 - 120));
	menuArray->addObject(menuButton);
	
	CCMenu* pMenu = CCMenu::createWithArray(menuArray);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);
	
	

	return true;
}

void GameOverScene::restartCallBack(CCObject* sender){
	Config::playEffect(Config::sfxButton, false);
	GameScene *gameScene = GameScene::create();
	CCDirector::sharedDirector()->replaceScene(gameScene);
	Config::stopEffect(Config::getIdGameOver());
}

void GameOverScene::menuCallBack(CCObject *sender){
	Config::playEffect(Config::sfxButton, false);
	MenuScene *menuScene = MenuScene::create();
	CCDirector::sharedDirector()->replaceScene(menuScene);	
	Config::stopEffect(Config::getIdGameOver());
}