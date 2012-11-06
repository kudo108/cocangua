#ifndef _GAME_LOGIC_H_
#define _GAME_LOGIC_H_

#include "GameObject.h"

class GameLogic
{
public:
	static float goCallback(GameObject *gameObject, int tag);
	static void selectCallback(GameObject *gameObject);

	static void checkForChangeTurn(GameObject *gameObject);
};

#endif