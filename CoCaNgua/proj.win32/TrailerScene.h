#ifndef _TRAILER_SCENE_H_
#define _TRAILER_SCENE_H_

#include "cocos2d.h"

class TrailerLayer : public cocos2d::CCLayer
{
public:
	TrailerLayer(void);
	~TrailerLayer(void);
	bool init();
	CREATE_FUNC(TrailerLayer);
	void load_Trailer();
	void callMenu();//neu ai do nhan nut thi thoat va chay callMenu

};


class TrailerScene :public cocos2d::CCScene
{
public:
	TrailerScene(void);
	~TrailerScene(void);
	bool init();
	CREATE_FUNC(TrailerScene);
};

#endif