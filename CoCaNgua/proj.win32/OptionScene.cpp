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
	int isMusicPlaying = Config::getVolume();
	if(isMusicPlaying){
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		//pMusicButton->unselected();
	}else{
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		//pMusicButton->selected();
	}
	Config::setVolume(!isMusicPlaying);
	
}

void OptionScene::menuCallback(CCObject *sender)
{
	MenuScene::playButtonEffect();
	MenuScene *menuScene = MenuScene::create();
	CCDirector::sharedDirector()->replaceScene(menuScene);	
}
