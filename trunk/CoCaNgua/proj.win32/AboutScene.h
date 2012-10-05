#ifndef _ABOUT_SCENE_H_
#define _ABOUT_SCENE_H_

#include "cocos2d.h"
#include "MenuScene.h"

using namespace cocos2d;


class AboutScene : public cocos2d::CCScene
{
public:
	AboutScene(void);
	~AboutScene(void);
	bool init();
	CREATE_FUNC(AboutScene);
private:
	void menuCallback(CCObject *sender);
};

#endif
