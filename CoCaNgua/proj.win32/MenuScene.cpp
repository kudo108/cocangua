#ifndef _MENU_SCENE_H_
#define _MENU_SCENE_H_H

#include "MenuScene.h"
#include "cocos2d.h"

using namespace cocos2d;

MenuLayer::MenuLayer(void)
{
}

MenuLayer::~MenuLayer(void)
{
}

bool MenuLayer::init()
{
	return true;
}

MenuScene::MenuScene(void)
{
}

MenuScene::~MenuScene(void)
{
}

bool MenuScene::init()
{
	// Init super first.
	if ( !CCScene::init() )
	{
		return false;
	}
	//get window size
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCArray *menuArray = CCArray::create();
	// Create menu button.
	//classic game
	CCMenuItemFont* pClassicGameButton = CCMenuItemFont::create(
										"Classic Game",
										this,
										menu_selector(MenuScene::menuClassicGameCallback));

	pClassicGameButton->setFontSizeObj(50);
	menuArray->addObject(pClassicGameButton);
	pClassicGameButton->setPosition(ccp(winSize.width / 2, winSize.height/2 + 210));
	// Modern Game
	CCMenuItemFont* pModernGameButton = CCMenuItemFont::create(
										"Modern Game",
										this,
										menu_selector(MenuScene::menuModernGameCallback));

	pModernGameButton->setFontSizeObj(50);
	menuArray->addObject(pModernGameButton);
	pModernGameButton->setPosition(ccp(winSize.width / 2, winSize.height/2 + 150));
	// AI game
	CCMenuItemFont* pAIGameButton = CCMenuItemFont::create(
										"AI Game",
										this,
										menu_selector(MenuScene::menuAIGameCallback));

	pAIGameButton->setFontSizeObj(50);
	menuArray->addObject(pAIGameButton);
	pAIGameButton->setPosition(ccp(winSize.width / 2, winSize.height/2 + 90));
	//Load saved game
	CCMenuItemFont* pLoadGameButton = CCMenuItemFont::create(
										"Load Game",
										this,
										menu_selector(MenuScene::menuLoadGameCallback));

	pLoadGameButton->setFontSizeObj(50);
	menuArray->addObject(pLoadGameButton);
	pLoadGameButton->setPosition(ccp(winSize.width / 2, winSize.height/2 + 30));
	//Option
	CCMenuItemFont* pOptionButton = CCMenuItemFont::create(	
										"Option",
										this,
										menu_selector(MenuScene::menuOptionCallback));
	pOptionButton->setFontSizeObj(50);
	menuArray->addObject(pOptionButton);
	pOptionButton->setPosition(ccp(winSize.width / 2, winSize.height/2 - 30));
	//About
	CCMenuItemFont* pAboutButton = CCMenuItemFont::create(
										"About",
										this,
										menu_selector(MenuScene::menuAboutCallback));

	pAboutButton->setFontSizeObj(50);
	menuArray->addObject(pAboutButton);
	pAboutButton->setPosition(ccp(winSize.width / 2, winSize.height/2 - 90));
	//help
	CCMenuItemFont* pHelpButton = CCMenuItemFont::create(
										"Help",
										this,
										menu_selector(MenuScene::menuHelpCallback));

	pHelpButton->setFontSizeObj(50);
	menuArray->addObject(pHelpButton);
	pHelpButton->setPosition(ccp(winSize.width / 2, winSize.height/2 - 150));
	//Exit
	CCMenuItemFont* pExitButton = CCMenuItemFont::create(
										"Exit",
										this,
										menu_selector(MenuScene::menuExitCallback));

	pExitButton->setFontSizeObj(50);
	menuArray->addObject(pExitButton);
	pExitButton->setPosition(ccp(winSize.width / 2, winSize.height/2 - 210));
	

	// Create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::createWithArray(menuArray);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);
	return true;
}
void MenuScene::menuClassicGameCallback()
{
}
void MenuScene::menuModernGameCallback()
{
}
void MenuScene::menuLoadGameCallback()
{
}
void MenuScene::menuAboutCallback()
{
}
void MenuScene::menuHelpCallback()
{
}
void MenuScene::menuOptionCallback()
{
}
void MenuScene::menuExitCallback()
{
	exit(1);
}
void MenuScene::menuAIGameCallback()
{
}
#endif