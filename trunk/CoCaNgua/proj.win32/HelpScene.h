#ifndef _HELP_SCENE_H_
#define _HELP_SCENE_H_

#include "cocos2d.h"

class HelpScene : public cocos2d::CCScene
{
public:
	HelpScene(void);
	~HelpScene(void);
	bool init();
	CREATE_FUNC(HelpScene);
private:
	void menuCallback(CCObject *sender);
};

#endif