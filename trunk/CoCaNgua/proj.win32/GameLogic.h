#ifndef _GAME_LOGIC_H_
#define _GAME_LOGIC_H_

#include "GameObject.h"

class GameLogic
{
public:
	static float goCallback(GameObject *gameObject);
	static void selectCallback(GameObject *gameObject);
private:
	static void checkForChangeTurn(GameObject *gameObject);
};

#endif