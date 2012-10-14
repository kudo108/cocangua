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
	
	pMusicButton->setFontSizeObj(Config::objectFontSize);
	pMusicButton->setPosition(ccp(size.width/2, size.height/2 + 30));
	//pMusicButton->unselected();
	menuArray->addObject(pMusicButton);

	CCMenuItemFont* pSFXButton = CCMenuItemFont::create(
										"Sound",
										this,
										menu_selector(OptionScene::toggleSFX));
	
	pSFXButton->setFontSizeObj(Config::objectFontSize);
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
	HelloWorld::playEffect(Config::sfxButton, false);
	CCMenuItemFont* pMusicButton = (CCMenuItemFont*)sender;

	bool isMusicPlaying = Config::getIsBgMusicPlaying();
	if(isMusicPlaying){
		HelloWorld::pauseBackgroundMusic();
	}else{
		HelloWorld::resumeBackgroundMusic();
	}
	Config::setIsBgMusicPlaying(!isMusicPlaying);
}

void OptionScene::toggleSFX(CCObject* sender){
	HelloWorld::playEffect(Config::sfxButton, false);
	CCMenuItemFont* pSFXButton = (CCMenuItemFont*)sender;
	
	bool isSFXPlaying = Config::getIsSFXEffectPlaying();
	//OutputDebugStringW(L"My output string.");
	Config::setIsSFXEffectPlaying(!isSFXPlaying);
}

void OptionScene::menuCallback(CCObject *sender)
{
	HelloWorld::playEffect(Config::sfxButton, false);
	MenuScene *menuScene = MenuScene::create();
	CCDirector::sharedDirector()->replaceScene(menuScene);	
}

