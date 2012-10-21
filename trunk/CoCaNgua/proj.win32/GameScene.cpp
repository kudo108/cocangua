
#include "GameScene.h"
#include "Config.h"
#include "ClassicGameLayer.h"
#include "MenuScene.h"
#include "RuleScene.h"
//test
#include "GameOverScene.h"
#include "GameWinScene.h"


using namespace CocosDenshion;
using namespace cocos2d;


bool GameScene::init()
{
	if(! CCScene::init() ) return false;
	

	isCalledXucXac = FALSE;
	int gameType = -1;

	if(!Config::getHasTurnOffMusic()){
		Config::stopBackgroundMusic();
		Config::playBackgroundMusic(Config::gameplayMusic, GP_MUSIC);
	}


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
	//demo game win
	CCMenuItemFont* pButtonGameWin = CCMenuItemFont::create(
										"GameWin(demo)",
										this,
										menu_selector(GameScene::gameWinCallback));
	pButtonGameWin->setFontSizeObj(fontSize/1.5);
	menuArray->addObject(pButtonGameWin);
	pButtonGameWin->setPosition(ccp(size.width-100, 4*jump));

	CCMenuItemFont* pSaveGameButton = CCMenuItemFont::create(
										"GameOver(demo)",
										this,
										menu_selector(GameScene::gameOverCallback));
	pSaveGameButton->setFontSizeObj(fontSize/1.5);
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
			
	//set xucxac and xucxacAction
	//xuc xac
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(Config::xucxac_plist);
	CCSpriteBatchNode *xucxacSpriteBatchNode =  CCSpriteBatchNode::create(Config::xucxac_texture);
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
	this->xucxacA = CCSprite::createWithSpriteFrameName("1.gif");
	this->xucxacA->retain();
	
	xucxacA->setPosition(ccp(size.width-100-40, size.height-100));

    xucxacAAminationAction = CCRepeatForever::create(CCAnimate::create(xucxacAnim));
	xucxacAAminationAction->setOriginalTarget(xucxacA);
	xucxacAAminationAction->retain();
	this->addChild(xucxacA,101);
	 //create sprite first frame from animation first frame
	this->xucxacB = CCSprite::createWithSpriteFrameName("1.gif");
	this->xucxacB->retain();
	xucxacB->setPosition(ccp(size.width-100+40, size.height-100));

    xucxacBAminationAction = CCRepeatForever::create(CCAnimate::create(xucxacAnim));
	xucxacBAminationAction->setOriginalTarget(xucxacB);
	xucxacBAminationAction->retain();
	//xucxac->runAction(xucxacAminationAction);
	this->addChild(xucxacB,101);
	//xuc xac button 1
	CCSprite *xucxac1 = CCSprite::create(Config::xucxac_texture1);
	CCMenuItemSprite *xucxacButton1 = CCMenuItemSprite::create(xucxac1,xucxac1,xucxac1,this,menu_selector(GameScene::xucxacCallback));
	xucxacButton1->setPosition(xucxacA->getPosition());
	menuArray->addObject(xucxacButton1);
	//xuc xac button 2
	CCSprite *xucxac2 = CCSprite::create(Config::xucxac_texture1);
	CCMenuItemSprite *xucxacButton2 = CCMenuItemSprite::create(xucxac2,xucxac2,xucxac2,this,menu_selector(GameScene::xucxacCallback));
	xucxacButton2->setPosition(xucxacB->getPosition());
	menuArray->addObject(xucxacButton2);

	// Create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::createWithArray(menuArray);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu,1);//ngoai cung,tuong tac
	
	ClassicGameLayer *classic = ClassicGameLayer::create();
	this->addChild(classic, 100);

	return true;
}

void GameScene::setGameType(int _t)
{
	this->gameType = _t;
}

//test
void GameScene::gameOverCallback(CCObject *sender){
	//save game
	Config::playEffect(Config::sfxButton, false);
	Config::stopAllEffect();
	GameOverScene *menuScene = GameOverScene::create();
	CCDirector::sharedDirector()->replaceScene(menuScene);
	
}

void GameScene::gameWinCallback(CCObject* sender){
	//save game
	Config::playEffect(Config::sfxButton, false);
	Config::stopAllEffect();
	GameWinScene *menuScene = GameWinScene::create();
	CCDirector::sharedDirector()->replaceScene(menuScene);
}

void GameScene::saveGameCallback(CCObject *sender)
{
	//save game
	Config::playEffect(Config::sfxButton, false);
	Config::stopAllEffect();
}
void GameScene::quitGameCallback(CCObject *sender)
{
	//back to menu
	Config::playEffect(Config::sfxButton, false);
	MenuScene *menuScene = MenuScene::create();
	CCDirector::sharedDirector()->replaceScene(menuScene);
	Config::stopAllEffect();
}
void GameScene::ruleCallback(CCObject *sender)
{
	//show rule
	Config::playEffect(Config::sfxButton, false);
	RuleScene *ruleScene = RuleScene::create();
	CCDirector::sharedDirector()->replaceScene(ruleScene);
	Config::stopAllEffect();
}

void GameScene::xucxacCallback(CCObject *sender)
{	
	if(!isCalledXucXac)
	{
		Config::setIdDice(Config::playEffect(Config::sfxDice, true));
		isCalledXucXac = TRUE;
		xucxacA->stopAllActions();
		xucxacA->runAction( xucxacAAminationAction);
		xucxacB->stopAllActions();
		xucxacB->runAction(xucxacBAminationAction);
		Config::kqXucXac1=Config::kqXucXac2=0;
	}else
	{
		Config::stopEffect(Config::getIdDice());
		
		char fn[128];
		srand ( time(NULL));
		int kq=rand()%6+1;

		xucxacA->pauseSchedulerAndActions();
		sprintf(fn, "%d.gif", 7-kq);
		Config::kqXucXac1=kq;
		xucxacA->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fn));

		kq=rand()%6+1;
		xucxacB->pauseSchedulerAndActions();
		sprintf(fn, "%d.gif", 7-kq);
		Config::kqXucXac2=kq;
		xucxacB->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fn));

		isCalledXucXac =FALSE;
	}
}
