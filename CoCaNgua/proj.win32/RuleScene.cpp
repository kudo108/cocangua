#include "RuleScene.h"
#include "Config.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "cocos2d.h"
#include "MusicHelper.h"

const int RuleScene::total = 3;

bool RuleScene::init(){
	if( !CCScene::init()) return false;

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCArray *menuArray = CCArray::create();	

	CCMenuItemFont* previousButton = CCMenuItemFont::create(
										"<",
										this,
										menu_selector(RuleScene::previousCallBack));

	previousButton->setFontSizeObj(Config::objectFontSize);
	previousButton->setPosition(ccp(20, size.height/2));
	previousButton->setColor(ccRED);
	menuArray->addObject(previousButton);

	CCMenuItemFont* nextButton = CCMenuItemFont::create(
										">",
										this,
										menu_selector(RuleScene::nextCallBack));

	nextButton->setFontSizeObj(Config::objectFontSize);
	nextButton->setPosition(ccp(size.width - 20, size.height/2));
	nextButton->setColor(ccRED);
	menuArray->addObject(nextButton);

	CCMenuItemFont* backButton = CCMenuItemFont::create(
										"Back to Game",
										this,
										menu_selector(RuleScene::menuCallBack));

	backButton->setFontSizeObj(20);
	backButton->setPosition(ccp(70, 20));
	menuArray->addObject(backButton);

	CCMenu* pMenu = CCMenu::createWithArray(menuArray);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 10);

	//rule sprite array
	cur = 1;
	sprite= NULL;
	loadSpriteAtCurrent();
	return true;
}


void RuleScene::menuCallBack(CCObject* sender){
	MusicHelper::playEffect(MusicHelper::sfxButton, false);
	GameScene *gameScene = GameScene::create();
	CCDirector::sharedDirector()->replaceScene(gameScene);
}
void RuleScene::previousCallBack(CCObject* sender){
	MusicHelper::playEffect(MusicHelper::sfxButton, false);
	if(cur <=1) cur = total;
	else cur--;
	loadSpriteAtCurrent();
}

void RuleScene::nextCallBack(CCObject* sender){
	MusicHelper::playEffect(MusicHelper::sfxButton, false);
	if(cur>=total) cur = 1;
	else cur++;
	loadSpriteAtCurrent();
}
void RuleScene::loadSpriteAtCurrent()
{
	char fn[128];
	sprintf(fn,"/image/rule/%d.png",cur);
	if(sprite != NULL)
	{
		sprite->removeFromParentAndCleanup(true);
		sprite->release();
	}
	CCLog("help created: %s",fn);
	sprite = CCSprite::create(fn);
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	if(sprite)
	{
		sprite->setPosition(ccp(size.width/2,size.height/2));
		this->addChild(sprite,cur);
		sprite->retain();
	}
}