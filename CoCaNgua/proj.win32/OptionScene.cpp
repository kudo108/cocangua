#include "OptionScene.h"
#include "MenuScene.h"
#include "Config.h"
#include "resource.h"

using namespace cocos2d;

bool OptionScene::init()
{
	if( !CCScene::init()) return false;
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCArray *menuArray = CCArray::create();

	//create button
	CCMenuItemFont* pMusicButton = CCMenuItemFont::create(
										"Music",
										this,
										menu_selector(OptionScene::toggleMusic));
	if(Config::getIsBgMusicPlaying()){
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
	
	if(Config::getIsSFXEffectPlaying()){
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
	Config::playEffect(Config::sfxButton, false);
	CCMenuItemFont* pMusicButton = (CCMenuItemFont*)sender;
	
	bool isMusicPlaying = Config::getIsBgMusicPlaying();
	if(isMusicPlaying){
		Config::pauseBackgroundMusic();
		pMusicButton->setFontSizeObj(Config::objectFontSize - 10);
		pMusicButton->setColor(ccGRAY);
	}else{
		Config::resumeBackgroundMusic();
		pMusicButton->setFontSizeObj(Config::objectFontSize);
		pMusicButton->setColor(ccWHITE);
	}
	Config::setIsBgMusicPlaying(!isMusicPlaying);
	Config::setHasTurnOffMusic(!Config::getHasTurnOffMusic());
}

void OptionScene::toggleSFX(CCObject* sender){
	Config::playEffect(Config::sfxButton, false);
	CCMenuItemFont* pSFXButton = (CCMenuItemFont*)sender;
	
	bool isSFXPlaying = Config::getIsSFXEffectPlaying();
	if(isSFXPlaying){
		pSFXButton->setFontSizeObj(Config::objectFontSize - 10);
		pSFXButton->setColor(ccGRAY);
	}else{
		pSFXButton->setFontSizeObj(Config::objectFontSize);
		pSFXButton->setColor(ccWHITE);
	}
	Config::setIsSFXEffectPlaying(!isSFXPlaying);
}

void OptionScene::menuCallback(CCObject *sender)
{
	Config::playEffect(Config::sfxButton, false);
	MenuScene *menuScene = MenuScene::create();
	CCDirector::sharedDirector()->replaceScene(menuScene);	
}

