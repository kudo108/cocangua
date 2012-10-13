#ifndef _CLASSIC_GAME_SCENE_H_
#define _CLASSIC_GAME_SCENE_H_

#include "ClassicGameLayer.h"
#include "Config.h"
#include "MenuScene.h"
#include "GameLayer.h"

using namespace cocos2d;


bool ClassicGameLayer::init()
{
	if(! CCLayer::init()) return false;


	return true;
}

void ClassicGameLayer::go1Callback(CCObject *sender)
{
}
void ClassicGameLayer::go2Callback(CCObject *sender)
{
}
void ClassicGameLayer::go3Callback(CCObject *sender)
{
}
void ClassicGameLayer::go4Callback(CCObject *sender)
{
}

#endif