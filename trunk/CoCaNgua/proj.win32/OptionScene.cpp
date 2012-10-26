#include "OptionScene.h"
#include "MenuScene.h"
#include "Config.h"
#include "resource.h"
#include "MusicHelper.h"

using namespace cocos2d;

bool OptionScene::init()
{
	if( !CCScene::init()) return false;
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//set background
	CCSprite* background = CCSprite::create(Config::optionBackground);
	if(background){
		background->setPosition(ccp(size.width/2, size.height/2));
		this->addChild(background);
	}

	CCArray *menuArray = CCArray::create();

	//create button
	CCMenuItemFont* pMusicButton = CCMenuItemFont::create(
										"Music",
										this,
										menu_selector(OptionScene::toggleMusic));
	if(MusicHelper::getIsBgMusicPlaying()){
		pMusicButton->setFontSizeObj(Config::objectFontSize);
		pMusicButton->setColor(ccWHITE);
	}else{
		pMusicButton->setFontSizeObj(Config::objectFontSize - 10);
		pMusicButton->setColor(ccGRAY);
	}
	pMusicButton->setPosition(ccp(size.width/2, size.height/2 + 30));
	menuArray->addObject(pMusicButton);

	CCMenuItemFont* pSFXButton = CCMenuItemFont::create(
										"Sound",
										this,
										menu_selector(OptionScene::toggleSFX));
	
	if(MusicHelper::getIsSFXEffectPlaying()){
		pSFXButton->setFontSizeObj(Config::objectFontSize);
		pSFXButton->setColor(ccWHITE);
	}else{
		pSFXButton->setFontSizeObj(Config::objectFontSize - 10);
		pSFXButton->setColor(ccGRAY);
	}
	pSFXButton->setPosition(ccp(size.width/2, size.height/2 - 30));
	//pMusicButton->unselected();
	menuArray->addObject(pSFXButton);

	CCMenuItemFont* pMenuButton = CCMenuItemFont::create(
										"Menu",
										this,
										menu_selector(OptionScene::menuCallback));
	
	pMenuButton->setFontSizeObj(Config::objectFontSize);
	pMenuButton->setPosition(ccp(size.width/2, 30));
	menuArray->addObject(pMenuButton);

	CCMenu* pMenu = CCMenu::createWithArray(menuArray);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);
	
	return true;
}

void OptionScene::toggleMusic(CCObject *sender){
	MusicHelper::playEffect(MusicHelper::sfxButton, false);
	CCMenuItemFont* pMusicButton = (CCMenuItemFont*)sender;
	
	bool isMusicPlaying = MusicHelper::getIsBgMusicPlaying();
	if(isMusicPlaying){
		MusicHelper::pauseBackgroundMusic();
		pMusicButton->setFontSizeObj(Config::objectFontSize - 10);
		pMusicButton->setColor(ccGRAY);
	}else{
		MusicHelper::resumeBackgroundMusic();
		pMusicButton->setFontSizeObj(Config::objectFontSize);
		pMusicButton->setColor(ccWHITE);
	}
	MusicHelper::setIsBgMusicPlaying(!isMusicPlaying);
	MusicHelper::setHasTurnOffMusic(!MusicHelper::getHasTurnOffMusic());
}

void OptionScene::toggleSFX(CCObject* sender){
	MusicHelper::playEffect(MusicHelper::sfxButton, false);
	CCMenuItemFont* pSFXButton = (CCMenuItemFont*)sender;
	
	bool isSFXPlaying = MusicHelper::getIsSFXEffectPlaying();
	if(isSFXPlaying){
		pSFXButton->setFontSizeObj(Config::objectFontSize - 10);
		pSFXButton->setColor(ccGRAY);
	}else{
		pSFXButton->setFontSizeObj(Config::objectFontSize);
		pSFXButton->setColor(ccWHITE);
	}
	MusicHelper::setIsSFXEffectPlaying(!isSFXPlaying);
}

void OptionScene::menuCallback(CCObject *sender)
{
	MusicHelper::playEffect(MusicHelper::sfxButton, false);
	MenuScene *menuScene = MenuScene::create();
	CCDirector::sharedDirector()->replaceScene(menuScene);	
}

