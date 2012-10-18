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
	if (!CCLayer::init()) return false;
    do 
    {
		
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

      //  CC_BREAK_IF(! CCLayer::init());

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
		//loader animation
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(Config::loader_plist);
		CCSpriteBatchNode *xucxacSpriteBatchNode =  CCSpriteBatchNode::create(Config::loader_texture);
		char fn[128];
		CCAnimation* loaderAnimation = CCAnimation::create();
	
		for (int i = 0; i <= 7; i++) 
		{
			sprintf(fn, "IMG0000%d.png", i);
			CCSpriteFrame* pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fn);
			loaderAnimation->addSpriteFrame(pFrame);
		}
	
		loaderAnimation->setDelayPerUnit(0.1f);
		 //create sprite first frame from animation first frame
		CCSprite* loader = CCSprite::createWithSpriteFrameName(Config::loader_image);
	
		loader->setPosition(ccp(20, 20));

		CCAction* loadAction = CCRepeatForever::create(CCAnimate::create(loaderAnimation));
		loadAction->setOriginalTarget(loader);
		loader->runAction(loadAction);
		this->addChild(loader);
		
		this->runAction( CCSequence::create(
                                CCDelayTime::create(2),
                                CCCallFunc::create(this, 
                                callfunc_selector(HelloWorld::call_Trailer)),
                                NULL));
    } while (0);

	
    return true;
}


void HelloWorld::call_Trailer(){
	TrailerScene *trailerScene = TrailerScene::create();
	CCDirector::sharedDirector()->replaceScene(trailerScene);
}
