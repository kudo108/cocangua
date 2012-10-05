#ifndef _OPTION_SCENE_H_
#define _OPTION_SCENE_H_

#include "cocos2d.h"


class OptionScene : public cocos2d::CCScene
{
public:
	OptionScene(void);
	~OptionScene(void);
	bool init();
	CREATE_FUNC(OptionScene);
private:
	void menuCallback(CCObject *sender);
};

#endif