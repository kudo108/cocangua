#include "HelloWorldScene.h"
#include "TrailerScene.h"
#include "Config.h"
#include "SimpleAudioEngine.h" 

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(Config::loader_plist);
	CCSpriteBatchNode* loaderSpriteSheet = CCSpriteBatchNode::batchNodeWithFile(Config::loader_texture);

	char fn[128];
	CCAnimation* loaderAnim =CCAnimation::create();
	
	for (int i = 1; i <= 6; i++) 
	{
		sprintf(fn, "%d.gif", i);
		CCSpriteFrame* pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fn);
		loaderAnim->addSpriteFrame(pFrame);
	}

	loaderAnim->setDelayPerUnit(0.01f);
	this->loader = CCSprite::createWithSpriteFrameName(Config::loader_image);
	
    bool bRet = false;
    do 
    {
		
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////
	
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		//background
		//char* _bg = Config::getFlashBackground();
		CCSprite* background = CCSprite::create(Config::flashBackground);
        if(background)
		{
			background->setPosition(ccp(size.width/2, size.height/2));
			this->addChild(background, 0);
		}
		//sleep(3);
	//	call_Trailer();
		
		this->runAction( CCSequence::create(
                                CCDelayTime::create(3),
                                CCCallFunc::create(this, 
                                callfunc_selector(HelloWorld::call_Trailer)),
                                NULL));
		bRet = true;
    } while (0);

	
    return bRet;
}


void HelloWorld::call_Trailer(){
	TrailerScene *trailerScene = TrailerScene::create();
	CCDirector::sharedDirector()->replaceScene(trailerScene);
}
