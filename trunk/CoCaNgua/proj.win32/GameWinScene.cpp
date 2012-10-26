#include "GameWinScene.h"
#include "Config.h"
#include "MenuScene.h"
#include "MusicHelper.h"

using namespace cocos2d;

bool GameWinScene::init(){
	if( !CCScene::init()) return false;

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	//stop background music and play sound of game over
	MusicHelper::pauseBackgroundMusic();
	MusicHelper::playEffect(MusicHelper::sfxGameWin, false);
	MusicHelper::playEffect(MusicHelper::sfxFireworks, true);
	
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
	//gangnam
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(Config::fireWorks_plist);
//	CCSpriteBatchNode *gameWinSpriteSheet =  CCSpriteBatchNode::create(Config::fireWorks_texture);
	char fn[128];
	CCAnimation* gameWinAnimation =CCAnimation::create();
	
	for (int i = 1; i <= 21; i++) 
	{
		sprintf(fn, "fw%d.png", i);
		CCSpriteFrame* pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fn);
		gameWinAnimation->addSpriteFrame(pFrame);
	}
	
    gameWinAnimation->setDelayPerUnit(0.1f);
     //create sprite first frame from animation first frame
	CCSprite* gameWin = CCSprite::createWithSpriteFrameName(Config::fireWorks_image);
	
	gameWin->setPosition(ccp(size.width/2, size.height/2));

	CCAction *gameWinAction = CCRepeatForever::create(CCAnimate::create(gameWinAnimation));
	gameWinAction->setOriginalTarget(gameWin);
	gameWin->runAction(gameWinAction);
	this->addChild(gameWin);
	return true;
}

void GameWinScene::menuCallback(CCObject* sender){
	MusicHelper::playEffect(MusicHelper::sfxButton, false);
	MenuScene *menuScene = MenuScene::create();
	CCDirector::sharedDirector()->replaceScene(menuScene);
	MusicHelper::stopAllEffect();
}