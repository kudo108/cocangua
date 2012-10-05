#ifndef __CLASSICGAME_LAYER_H__
#define __CLASSICGAME_LAYER_H__

#include "cocos2d.h"

class ClassicGameLayer: public cocos2d::CCLayer
{
public:
	ClassicGameLayer(void);
	~ClassicGameLayer(void);
	bool init();
	CREATE_FUNC(ClassicGameLayer);
};

#endif