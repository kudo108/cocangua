#include "GameScene.h"
#include "cocos2d.h"
#include "Config.h"
#include "GameLayer.h"

using namespace cocos2d;

GameScene::GameScene(void)
{
}

GameScene::~GameScene(void)
{
}

bool GameScene::init()
{
	if(! CCScene::init() ) return false;
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	//background
	CCSprite* background = CCSprite::create(Config::classicGameBackground);
    if(background)
	{
		background->setScaleX(0.5859375);
		background->setScaleY(0.5859375);
		background->setPosition(ccp(size.width/2-100, size.height/2));
		this->addChild(background,-1);//uu tien (nam duoi cung)
	}
	//menu
	CCArray *menuArray = CCArray::create();
	int fontSize=Config::objectFontSize;
	int jump =60;
	//save game
	CCMenuItemFont* pSaveGameButton = CCMenuItemFont::create(
										"Save",
										this,
										menu_selector(GameLayer::saveGameCallback));

	pSaveGameButton->setFontSizeObj(fontSize);
	menuArray->addObject(pSaveGameButton);
	pSaveGameButton->setPosition(ccp(size.width-100, 3*jump));
	//Rule game
	CCMenuItemFont* pRuleGameButton = CCMenuItemFont::create(
										"Rule",
										this,
										menu_selector(GameLayer::ruleCallback));

	pRuleGameButton->setFontSizeObj(fontSize);
	menuArray->addObject(pRuleGameButton);
	pRuleGameButton->setPosition(ccp(size.width-100, 2*jump));
	//Quit game
	CCMenuItemFont* pQuitGameButton = CCMenuItemFont::create(
										"Quit",
										this,
										menu_selector(GameLayer::quitGameCallback));

	pQuitGameButton->setFontSizeObj(fontSize);
	menuArray->addObject(pQuitGameButton);
	pQuitGameButton->setPosition(ccp(size.width-100, jump));
	// Create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::createWithArray(menuArray);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu,100);//ngoai cung,tuong tac

	//200x200 xi ngau
	//call GameLayer::xoXiNgau() de xo xi ngau
	background = CCSprite::create(Config::xingau_init_image);
    if(background)
	{
		background->setPosition(ccp(size.width-100, size.height-100));
		this->addChild(background,90);
	}
	//sua lai cho nay la button = image, nhan vao thi goi call back ham so xi ngau ->amination 1s-> ra so nao thi the hien image do
	
	return true;
}

void GameScene::setGameType(int _t)
{
	this->gameType = _t;
}