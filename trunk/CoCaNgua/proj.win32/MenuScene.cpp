#ifndef _MENU_SCENE_H_
#define _MENU_SCENE_H_H

#include <windows.h>
#include "MenuScene.h"
#include "cocos2d.h"
#include "GameScene.h"
#include "AboutScene.h"
#include "HelpScene.h"
#include "OptionScene.h"
#include "Config.h"

using namespace cocos2d;


MenuScene::MenuScene(void)
{
}

MenuScene::~MenuScene(void)
{
}

bool MenuScene::init()
{
	// Init super first.
	if ( !CCScene::init() ) return false;
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
	menuArray->addObject(pClassicGameButton);
	pClassicGameButton->setPosition(ccp(size.width / 2, size.height/2 + 3.5*jump));
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
	GameScene *gameScene = GameScene::create();
	CCDirector::sharedDirector()->replaceScene(gameScene);
}
void MenuScene::menuModernGameCallback(CCObject* sender)
{
	GameScene *gameScene = GameScene::create();
	CCDirector::sharedDirector()->replaceScene(gameScene);
}
void MenuScene::menuAIGameCallback(CCObject* sender)
{
	GameScene *gameScene = GameScene::create();
	CCDirector::sharedDirector()->replaceScene(gameScene);
}
void MenuScene::menuLoadGameCallback(CCObject* sender)
{
	GameScene *gameScene = GameScene::create();
	CCDirector::sharedDirector()->replaceScene(gameScene);
}
void MenuScene::menuAboutCallback(CCObject* sender)
{
	AboutScene *aboutScene = AboutScene::create();
	CCDirector::sharedDirector()->replaceScene(aboutScene);		
}
void MenuScene::menuHelpCallback(CCObject* sender)
{
	HelpScene *helpScene = HelpScene::create();
	CCDirector::sharedDirector()->replaceScene(helpScene);
}
void MenuScene::menuOptionCallback(CCObject* sender)
{
	OptionScene *optionScene = OptionScene::create();
	CCDirector::sharedDirector()->replaceScene(optionScene);
}
void MenuScene::menuExitCallback(CCObject* sender)
{
	if(MessageBox( NULL, L"Are you sure ? ",NULL, MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES){
		this->cleanup();
		this->autorelease();
		exit(1);
	}
}
#endif