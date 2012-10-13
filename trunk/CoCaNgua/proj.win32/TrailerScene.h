#ifndef _TRAILER_SCENE_H_
#define _TRAILER_SCENE_H_

#include "cocos2d.h"

class TrailerScene :public cocos2d::CCScene
{
public:
	virtual bool init();
	CREATE_FUNC(TrailerScene);
	void load_Trailer();
	void callMenu();//neu ai do nhan nut thi thoat va chay callMenu
};

#endif