#pragma once
#include "GameLogic.h"

class RacingGameLogic : public GameLogic
{
public:
	static float goCallback(GameObject *gameObject, int tag);
	static void selectCallback(GameObject *gameObject);
};

