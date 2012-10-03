#ifndef __CLASSICGAME_SCENE_H__
#define __CLASSICGAME_SCENE_H__

#include "cocos2d.h"

class ClassicGameLayer: public cocos2d::CCLayer
{
public:
	ClassicGameLayer(void);
	~ClassicGameLayer(void);
	bool init();
	CREATE_FUNC(ClassicGameLayer);
};
class ClassicGameScene: public cocos2d::CCScene
{
public:
	ClassicGameScene(void);
	~ClassicGameScene(void);
	bool init();
	CREATE_FUNC(ClassicGameScene);
};

#endif