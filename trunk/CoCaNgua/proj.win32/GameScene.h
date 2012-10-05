#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"

class GameScene : public cocos2d::CCScene
{
public:
	GameScene(void);
	~GameScene(void);
	bool init();
	CREATE_FUNC(GameScene);
	void setGameType(int _t);//1 = classic, 2 = modern, 3 = AI
private:
	int gameType;
};

#endif