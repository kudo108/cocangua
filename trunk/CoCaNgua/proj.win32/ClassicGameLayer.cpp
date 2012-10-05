#ifndef _CLASSIC_GAME_SCENE_H_
#define _CLASSIC_GAME_SCENE_H_

#include "ClassicGameLayer.h"
#include "Config.h"
#include "MenuScene.h"
#include "cocos2d.h"
#include "GameLayer.h"

using namespace cocos2d;

ClassicGameLayer::ClassicGameLayer(void)
{
}


ClassicGameLayer::~ClassicGameLayer(void)
{
}

bool ClassicGameLayer::init()
{
	if(! CCLayer::init()) return false;


	return true;
}

#endif