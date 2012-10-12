#include "OptionScene.h"
#include "cocos2d.h"
#include "MenuScene.h"
#include "Config.h"
#include "SimpleAudioEngine.h"
#include "resource.h"

using namespace cocos2d;
using namespace CocosDenshion;

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

	CCArray *menuArray = CCArray::create();

	//create button
	CCMenuItemFont* pMusicButton = CCMenuItemFont::create(
										"Music",
										this,
										menu_selector(OptionScene::toggleMusic));
	
	pMusicButton->setFontSizeObj(Config::objectFontSize);
	pMusicButton->setPosition(ccp(size.width/2, size.height - 30));
	//pMusicButton->unselected();
	menuArray->addObject(pMusicButton);

	CCMenuItemFont* pSFXButton = CCMenuItemFont::create(
										"Sound",
										this,
										menu_selector(OptionScene::toggleSFX));
	
	pSFXButton->setFontSizeObj(Config::objectFontSize);
	pSFXButton->setPosition(ccp(size.width/2, size.height - 30));
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
	CCMenuItemFont* pMusicButton = (CCMenuItemFont*)sender;

	int isMusicPlaying = Config::getIsBgMusicPlaying();
	if(isMusicPlaying){
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}else{
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
	Config::setIsBgMusicPlaying(!isMusicPlaying);
}

//void OptionScene::toggleSFX(CCObject* sender){
//	CCMenuItemFont* pSFXButton = (CCMenuItemFont*)sender;
//
//	int isSFXPlaying = Config::getIsSFXEffectPlaying();
//	if(isSFXPlaying){
//		SimpleAudioEngine::sharedEngine()->pauseAllEffects();
//	}else{
//		SimpleAudioEngine::sharedEngine()->resumeAllEffects();
//	}
//	Config::setIsSFXEffectPlaying(!isSFXPlaying);
//}

void OptionScene::menuCallback(CCObject *sender)
{
	MenuScene::playButtonEffect();
	MenuScene *menuScene = MenuScene::create();
	CCDirector::sharedDirector()->replaceScene(menuScene);	
}

