#ifndef _GAME_LOGIC_H_
#define _GAME_LOGIC_H_

#include "GameObject.h"
class GameLogic
{
public:
	GameLogic(GameObject* _gObj);
	float goCallback();
	void selectCallback();
private:
	GameObject* gameObject;
	void checkForChangeTurn();
};

#endif