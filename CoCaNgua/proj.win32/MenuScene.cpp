#ifndef _MENU_SCENE_H_
#define _MENU_SCENE_H_H

#include <windows.h>
#include "MenuScene.h"
#include "GameScene.h"
#include "AboutScene.h"
#include "HelpScene.h"
#include "OptionScene.h"
#include "Config.h"
#include "UnderBuildingScene.h"
#include "MapLocation.h"

using namespace cocos2d;
//using namespace CocosDenshion;


bool MenuScene::init()
{
	// Init super first.
	if ( !CCScene::init() ) return false;
	//play background music(if haven't play yet)
	if(!Config::getIsBgMusicPlaying() && !Config::getHasTurnOffMusic()){

		Config::playBackgroundMusic(Config::backgroundMusic, BG_MUSIC);
	}
	//
	
	//

	int jump=40;
	//get window size
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//background
	CCSprite* background = CCSprite::create(Config::menuBackground);
	if(background)
	{
		background->setPosition(ccp(size.width/2, size.height/2));
		this->addChild(background);
	}
	// Create menu button.
	CCArray *menuArray = CCArray::create();
	int objectFontSize=Config::objectFontSize;
	//classic game
	CCMenuItemFont* pClassicGameButton = CCMenuItemFont::create(
										"Classic Game",
										this,
										menu_selector(MenuScene::menuClassicGameCallback));

	pClassicGameButton->setFontSizeObj(objectFontSize);
	pClassicGameButton->setPosition(ccp(size.width / 2, size.height/2 + 3.5*jump));
	menuArray->addObject(pClassicGameButton);
	// Modern Game
	CCMenuItemFont* pModernGameButton = CCMenuItemFont::create(
										"Modern Game",
										this,
										menu_selector(MenuScene::menuModernGameCallback));

	pModernGameButton->setFontSizeObj(objectFontSize);
	menuArray->addObject(pModernGameButton);
	pModernGameButton->setPosition(ccp(size.width / 2, size.height/2 + 2.5*jump));
	// AI game
	CCMenuItemFont* pAIGameButton = CCMenuItemFont::create(
										"AI Game",
										this,
										menu_selector(MenuScene::menuAIGameCallback));

	pAIGameButton->setFontSizeObj(objectFontSize);
	menuArray->addObject(pAIGameButton);
	pAIGameButton->setPosition(ccp(size.width / 2, size.height/2 + 1.5*jump));
	//Load saved game
	CCMenuItemFont* pLoadGameButton = CCMenuItemFont::create(
										"Load Game",
										this,
										menu_selector(MenuScene::menuLoadGameCallback));

	pLoadGameButton->setFontSizeObj(objectFontSize);
	menuArray->addObject(pLoadGameButton);
	pLoadGameButton->setPosition(ccp(size.width / 2, size.height/2 + 0.5*jump));
	//Option
	CCMenuItemFont* pOptionButton = CCMenuItemFont::create(	
										"Option",
										this,
										menu_selector(MenuScene::menuOptionCallback));
	pOptionButton->setFontSizeObj(objectFontSize);
	menuArray->addObject(pOptionButton);
	pOptionButton->setPosition(ccp(size.width / 2, size.height/2 - 0.5*jump));
	//About
	CCMenuItemFont* pAboutButton = CCMenuItemFont::create(
										"About",
										this,
										menu_selector(MenuScene::menuAboutCallback));

	pAboutButton->setFontSizeObj(objectFontSize);
	menuArray->addObject(pAboutButton);
	pAboutButton->setPosition(ccp(size.width / 2, size.height/2 - 1.5*jump));
	//help
	CCMenuItemFont* pHelpButton = CCMenuItemFont::create(
										"Help",
										this,
										menu_selector(MenuScene::menuHelpCallback));

	pHelpButton->setFontSizeObj(objectFontSize);
	menuArray->addObject(pHelpButton);
	pHelpButton->setPosition(ccp(size.width / 2, size.height/2 - 2.5*jump));
	//Exit
	CCMenuItemFont* pExitButton = CCMenuItemFont::create(
										"Exit",
										this,
										menu_selector(MenuScene::menuExitCallback));

	pExitButton->setFontSizeObj(objectFontSize);
	menuArray->addObject(pExitButton);
	pExitButton->setPosition(ccp(size.width / 2, size.height/2 - 3.5*jump));
	

	// Create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::createWithArray(menuArray);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);

	return true;
}

void MenuScene::menuClassicGameCallback(CCObject* sender)
{
	Config::playEffect(Config::sfxButton, false);
	CCDirector::sharedDirector()->replaceScene(GameScene::create());
}
void MenuScene::menuModernGameCallback(CCObject* sender)
{
	Config::playEffect(Config::sfxButton, false);
	CCDirector::sharedDirector()->replaceScene(UnderBuildingScene::create());
}
void MenuScene::menuAIGameCallback(CCObject* sender)
{
	Config::playEffect(Config::sfxButton, false);
	CCDirector::sharedDirector()->replaceScene(UnderBuildingScene::create());
}
void MenuScene::menuLoadGameCallback(CCObject* sender)
{
	Config::playEffect(Config::sfxButton, false);
	CCDirector::sharedDirector()->replaceScene(UnderBuildingScene::create());
}
void MenuScene::menuAboutCallback(CCObject* sender)
{
	Config::playEffect(Config::sfxButton, false);
	CCDirector::sharedDirector()->replaceScene(AboutScene::create());		
}
void MenuScene::menuHelpCallback(CCObject* sender)
{
	Config::playEffect(Config::sfxButton, false);
	CCDirector::sharedDirector()->replaceScene(HelpScene::create());
}
void MenuScene::menuOptionCallback(CCObject* sender)
{
	Config::playEffect(Config::sfxButton, false);
	CCDirector::sharedDirector()->replaceScene(OptionScene::create());
}
void MenuScene::menuExitCallback(CCObject* sender)
{
	Config::playEffect(Config::sfxButton, false);
	if(MessageBox( NULL, L"Are you sure ? ",L"Quit", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES){
		this->cleanup();
		this->autorelease();
		CCDirector::sharedDirector()->end();
		//exit(1);
	}
}


#endif