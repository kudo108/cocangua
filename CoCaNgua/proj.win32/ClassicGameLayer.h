#ifndef __CLASSICGAME_LAYER_H__
#define __CLASSICGAME_LAYER_H__

#include "cocos2d.h"

class ClassicGameLayer: public cocos2d::CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(ClassicGameLayer);
	void go1Callback(CCObject *sender);
	void go2Callback(CCObject *sender);
	void go3Callback(CCObject *sender);
	void go4Callback(CCObject *sender);
};

#endif