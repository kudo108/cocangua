#include "HelpScene.h"
#include "MenuScene.h"
#include "Config.h"
#include "MusicHelper.h"

using namespace cocos2d;

const int HelpScene::total = 9;

bool HelpScene::init()
{
	if(!CCScene::init()) return false;

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCArray *menuArray = CCArray::create();

	//create button
	CCMenuItemFont* previousButton = CCMenuItemFont::create(
										"<",
										this,
										menu_selector(HelpScene::previousCallBack));

	previousButton->setFontSizeObj(Config::objectFontSize);
	previousButton->setPosition(ccp(20, size.height/2));
	previousButton->setColor(ccRED);
	menuArray->addObject(previousButton);

	CCMenuItemFont* nextButton = CCMenuItemFont::create(
										">",
										this,
										menu_selector(HelpScene::nextCallBack));

	nextButton->setFontSizeObj(Config::objectFontSize);
	nextButton->setPosition(ccp(size.width - 20, size.height/2));
	nextButton->setColor(ccRED);
	menuArray->addObject(nextButton);

	CCMenuItemFont* pMenuButton = CCMenuItemFont::create(
										"Menu",
										this,
										menu_selector(HelpScene::menuCallback));
	
	pMenuButton->setFontSizeObj(Config::objectFontSize);
	pMenuButton->setPosition(ccp(size.width/2, 30));
	pMenuButton->setColor(ccRED);
	menuArray->addObject(pMenuButton);
	CCMenu* pMenu = CCMenu::createWithArray(menuArray);

	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu,100);

	//help sprite array
	cur = 1;
	sprite= NULL;
	loadSpriteAtCurrent();
	return true;
}

void HelpScene::previousCallBack(CCObject* sender){
	MusicHelper::playEffect(MusicHelper::sfxButton, false);
	if(cur <=1) cur = total;
	else cur--;
	loadSpriteAtCurrent();
}

void HelpScene::nextCallBack(CCObject* sender){
	MusicHelper::playEffect(MusicHelper::sfxButton, false);
	if(cur>=total) cur = 1;
	else cur++;
	loadSpriteAtCurrent();
}

void HelpScene::menuCallback(CCObject *sender)
{
	MusicHelper::playEffect(MusicHelper::sfxButton, false);
	MenuScene *menuScene = MenuScene::create();
	CCDirector::sharedDirector()->replaceScene(menuScene);	
}
void HelpScene::loadSpriteAtCurrent()
{
	char fn[128];
	sprintf(fn,"/image/help/%d.png",cur);
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