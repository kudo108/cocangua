#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_

#include "cocos2d.h"

class GameLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
	
private:
};

#endif