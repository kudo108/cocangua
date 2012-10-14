#include "GameScene.h"
#include "Config.h"
#include "ClassicGameLayer.h"
#include "MenuScene.h"

using namespace cocos2d;

GameScene::GameScene(void)
{
	//Create map manager
	map = new MapLocation(600);

	isCalledXucXac = FALSE;

	xucxac1 = CCSprite::create(Config::xucxac_texture1);
	
	int gameType = -1;

	
	
}

GameScene::~GameScene(void)
{
	//delete map;
	//map=NULL;
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
	//menu border
	CCSprite* menuBorder = CCSprite::create(Config::menuBorder);
    if(menuBorder)
	{
		menuBorder->setPosition(ccp(size.width-100, size.height/2));
		this->addChild(menuBorder,-1);//uu tien (nam duoi cung)
	}
	//menu
	CCArray *menuArray = CCArray::create();
	int fontSize=Config::objectFontSize;
	int jump =60;
	//save game
	CCMenuItemFont* pSaveGameButton = CCMenuItemFont::create(
										"Save",
										this,
										menu_selector(GameScene::saveGameCallback));
	pSaveGameButton->setFontSizeObj(fontSize);
	menuArray->addObject(pSaveGameButton);
	pSaveGameButton->setPosition(ccp(size.width-100, 3*jump));
	//Rule game
	CCMenuItemFont* pRuleGameButton = CCMenuItemFont::create(
										"Rule",
										this,
										menu_selector(GameScene::ruleCallback));
	pRuleGameButton->setColor(ccColor3B());
	pRuleGameButton->setFontSizeObj(fontSize);
	menuArray->addObject(pRuleGameButton);
	pRuleGameButton->setPosition(ccp(size.width-100, 2*jump));
	//Quit game
	CCMenuItemFont* pQuitGameButton = CCMenuItemFont::create(
										"Quit",
										this,
										menu_selector(GameScene::quitGameCallback));
	pQuitGameButton->setFontSizeObj(fontSize);
	menuArray->addObject(pQuitGameButton);
	pQuitGameButton->setPosition(ccp(size.width-100, jump));
	
	//button 1
	float numberButtonPositionY = 4*jump;
	CCMenuItemFont* p1Button = CCMenuItemFont::create(
										"1",
										this,
										menu_selector(ClassicGameLayer::go1Callback));
	p1Button->setFontSizeObj(fontSize);
	menuArray->addObject(p1Button);
	p1Button->setPosition(ccp(size.width-200 + 25, numberButtonPositionY));
	//button 2
	CCMenuItemFont* p2Button = CCMenuItemFont::create(
										"2",
										this,
										menu_selector(ClassicGameLayer::go2Callback));
	p2Button->setFontSizeObj(fontSize);
	menuArray->addObject(p2Button);
	p2Button->setPosition(ccp(size.width-200+75, numberButtonPositionY));
	//button 3
	CCMenuItemFont* p3Button = CCMenuItemFont::create(
										"3",
										this,
										menu_selector(ClassicGameLayer::go3Callback));
	p3Button->setFontSizeObj(fontSize);
	menuArray->addObject(p3Button);
	p3Button->setPosition(ccp(size.width-200+125, numberButtonPositionY));
	//button 4
	CCMenuItemFont* p4Button = CCMenuItemFont::create(
										"4",
										this,
										menu_selector(ClassicGameLayer::go4Callback));
	p4Button->setFontSizeObj(fontSize);
	menuArray->addObject(p4Button);
	p4Button->setPosition(ccp(size.width-200+175, numberButtonPositionY));
	
	//xuc xac button
	CCMenuItemSprite *xucxacButton = CCMenuItemSprite::create(xucxac1,xucxac1,xucxac1,this,menu_selector(GameScene::xucxacCallback));
	xucxacButton->setPosition(ccp(size.width-100, size.height-100));
	menuArray->addObject(xucxacButton);
	
	// Create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::createWithArray(menuArray);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu,100);//ngoai cung,tuong tac
	
	
	//set xucxac and xucxacAction
//	CCSize size = CCDirector::sharedDirector()->getWinSize();
	//xuc xac
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(Config::xucxac_plist);
	CCSpriteBatchNode *xucxacSpriteBatchNode =  CCSpriteBatchNode::batchNodeWithFile(Config::xucxac_texture);
	char fn[128];
	CCAnimation* xucxacAnim =CCAnimation::create();
	
	for (int i = 1; i <= 6; i++) 
	{
		sprintf(fn, "%d.gif", i);
		CCSpriteFrame* pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fn);
		xucxacAnim->addSpriteFrame(pFrame);
	}
	
    xucxacAnim->setDelayPerUnit(0.01f);
     //create sprite first frame from animation first frame
	this->xucxac = CCSprite::createWithSpriteFrameName("1.gif");
	this->xucxac->retain();
	xucxac->setPosition(ccp(size.width-100, size.height-100));
	CCAnimate *xucxacAnimate = CCAnimate::create(xucxacAnim);
	//CCFiniteTimeAction* xucxacAmination =CCRepeatForever::create(xucxacAnimate);

    xucxacAminationAction = CCRepeatForever::create(xucxacAnimate);
	xucxacAminationAction->setOriginalTarget(xucxac);
	xucxacAminationAction->retain();
	//xucxac->runAction(xucxacAminationAction);
	this->addChild(xucxac,101);
	return true;
}

void GameScene::setGameType(int _t)
{
	this->gameType = _t;
}


void GameScene::saveGameCallback(CCObject *sender)
{
	//save game
}
void GameScene::quitGameCallback(CCObject *sender)
{
	MenuScene *menuScene = MenuScene::create();
	CCDirector::sharedDirector()->replaceScene(menuScene);
	//back to menu
}
void GameScene::ruleCallback(CCObject *sender)
{
	//show rule
}
int GameScene::soXucXac()
{
	srand ( time(NULL) );
	return rand()%6+1;
}

void GameScene::xucxacCallback(CCObject *sender)
{	
	if(!isCalledXucXac)
	{
		isCalledXucXac = TRUE;
		xucxac->stopAllActions();
		xucxac->runAction( xucxacAminationAction);
	}else
	{
		xucxac->pauseSchedulerAndActions();
		char fn[128];
		int ketqua = soXucXac();
		sprintf(fn, "%d.gif", 7-ketqua);
		xucxac->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fn));
		isCalledXucXac =FALSE;
	}
}