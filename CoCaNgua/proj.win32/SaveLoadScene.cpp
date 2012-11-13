#include "SaveLoadScene.h"
#include "Config.h"
#include "MusicHelper.h"
#include "GameScene.h"
#include "SaveLoad.h"
bool SaveLoadScene::init(){
	if( !CCScene::init()) return false;
	Config::loadGame = true;
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//set background
	CCSprite* background = CCSprite::create(Config::optionBackground);
	if(background){
		background->setPosition(ccp(size.width/2, size.height/2));
		this->addChild(background);
	}
	CCArray *menuArray = CCArray::create();

	CCMenuItemFont* pClassicButton = CCMenuItemFont::create(
										"Classic",
										this,
										menu_selector(SaveLoadScene::classicCallback));

	pClassicButton->setFontSizeObj(Config::objectFontSize);
	pClassicButton->setPosition(ccp(size.width/2, size.height/2 + 90));
	menuArray->addObject(pClassicButton);

	CCMenuItemFont* pAIButton = CCMenuItemFont::create(
										"AI",
										this,
										menu_selector(SaveLoadScene::AICallback));

	pAIButton->setFontSizeObj(Config::objectFontSize);
	pAIButton->setPosition(ccp(size.width/2, size.height/2 + 30));
	menuArray->addObject(pAIButton);

	CCMenuItemFont* pModernButton = CCMenuItemFont::create(
										"Modern",
										this,
										menu_selector(SaveLoadScene::modernCallback));

	pModernButton->setFontSizeObj(Config::objectFontSize);
	pModernButton->setPosition(ccp(size.width/2, size.height/2 - 30));
	menuArray->addObject(pModernButton);

	CCMenuItemFont* pRacingButton = CCMenuItemFont::create(
										"Racing",
										this,
										menu_selector(SaveLoadScene::racingCallback));

	pRacingButton->setFontSizeObj(Config::objectFontSize);
	pRacingButton->setPosition(ccp(size.width/2, size.height/2 - 90));
	menuArray->addObject(pRacingButton);

	CCMenuItemFont* menuButton = CCMenuItemFont::create(
										"Back to Menu",
										this,
										menu_selector(SaveLoadScene::menuCallback));

	menuButton->setFontSizeObj(Config::objectFontSize - 10);
	menuButton->setPosition(ccp(size.width/2, 120));
	menuArray->addObject(menuButton);

	CCMenu* pMenu = CCMenu::createWithArray(menuArray);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);
	
	return true;
}

void SaveLoadScene::menuCallback(CCObject* sender){
	MusicHelper::playEffect(MusicHelper::sfxButton, false);
	CCDirector::sharedDirector()->replaceScene(MenuScene::create());
	Config::loadGame = false;
}

void SaveLoadScene::classicCallback(CCObject* sender){
	MusicHelper::playEffect(MusicHelper::sfxButton, false);
	bool fileExist = SaveLoad::checkExist(SaveLoad::getFileName(CLASSIC));
	if(fileExist){
		Config::gameType = CLASSIC;
		CCDirector::sharedDirector()->replaceScene(GameScene::create());
	}else{
		showWarning();
	}
}

void SaveLoadScene::modernCallback(CCObject* sender){
	MusicHelper::playEffect(MusicHelper::sfxButton, false);
	bool fileExist = SaveLoad::checkExist(SaveLoad::getFileName(MODERN));
	if(fileExist){
		Config::gameType = MODERN;
		CCDirector::sharedDirector()->replaceScene(GameScene::create());
	}else{
		showWarning();
	}
}

void SaveLoadScene::AICallback(CCObject* sender){
	MusicHelper::playEffect(MusicHelper::sfxButton, false);
	bool fileExist = SaveLoad::checkExist(SaveLoad::getFileName(AI));
	if(fileExist){
		Config::gameType = AI;
		CCDirector::sharedDirector()->replaceScene(GameScene::create());
	}else{
		showWarning();
	}
}

void SaveLoadScene::racingCallback(CCObject* sender){
	MusicHelper::playEffect(MusicHelper::sfxButton, false);
	bool fileExist = SaveLoad::checkExist(SaveLoad::getFileName(RACING));
	if(fileExist){
		Config::gameType = RACING;
		CCDirector::sharedDirector()->replaceScene(GameScene::create());
	}else{
		showWarning();
	}
}

void SaveLoadScene::showWarning(){
	MessageBox( NULL, L"There are no saved game for this mode",L"Load",  MB_OK | MB_ICONWARNING);
}