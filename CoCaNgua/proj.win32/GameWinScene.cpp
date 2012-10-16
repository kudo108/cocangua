#include "GameWinScene.h"
#include "Config.h"
#include "MenuScene.h"

using namespace cocos2d;

bool GameWinScene::init(){
	if( !CCScene::init()) return false;

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	//stop background music and play sound of game over
	Config::pauseBackgroundMusic();
	Config::setIdGameWin(Config::playEffect(Config::sfxGameWin, false));

	CCArray *menuArray = CCArray::create();

	CCMenuItemFont* winLabel = CCMenuItemFont::create("YOU WIN");

	
	winLabel->setFontSizeObj(Config::objectFontSize*1.5);
	winLabel->setPosition(ccp(size.width/2, size.height - 120));
	menuArray->addObject(winLabel);

	CCMenuItemFont* menuButton = CCMenuItemFont::create(
										"Back to Menu",
										this,
										menu_selector(GameWinScene::menuCallback));

	menuButton->setFontSizeObj(Config::objectFontSize - 10);
	menuButton->setPosition(ccp(size.width/2, 120));
	menuArray->addObject(menuButton);

	CCMenu* pMenu = CCMenu::createWithArray(menuArray);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);
	//load animation
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(Config::gameWin_plist);
	CCSpriteBatchNode *gameWinSpriteBatchNode =  CCSpriteBatchNode::create(Config::gameWin_texture);
	char fn[128];
	CCAnimation* gameWinAnimation =CCAnimation::create();
	
	for (int i = 0; i <= 9; i++) 
	{
		sprintf(fn, "gw%d.png", i);
		CCSpriteFrame* pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fn);
		gameWinAnimation->addSpriteFrame(pFrame);
	}
	
    gameWinAnimation->setDelayPerUnit(0.1f);
     //create sprite first frame from animation first frame
	CCSprite* gameWin = CCSprite::createWithSpriteFrameName(Config::gameWin_image);
	
	gameWin->setPosition(ccp(size.width/2, size.height/2));

	CCAction *xucxacAAminationAction = CCRepeatForever::create(CCAnimate::create(gameWinAnimation));
	xucxacAAminationAction->setOriginalTarget(gameWin);
	gameWin->runAction(xucxacAAminationAction);
	this->addChild(gameWin);
	
	return true;
}

void GameWinScene::menuCallback(CCObject* sender){
	Config::playEffect(Config::sfxButton, false);
	MenuScene *menuScene = MenuScene::create();
	CCDirector::sharedDirector()->replaceScene(menuScene);	
	Config::stopEffect(Config::getIdGameWin());
}