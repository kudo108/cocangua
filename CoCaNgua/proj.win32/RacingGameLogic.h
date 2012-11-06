#pragma once
#include "GameLogic.h"

class RacingGameLogic : public GameLogic
{
public:
	static float goCallback(GameObject *gameObject, int tag);
	static void selectCallback(GameObject *gameObject);
private:
	static AnimalUnit* havingUnitAtPosition(GameObject* gameObject, CCPoint point);
	static bool canInitFromRollResult(GameObject* gameObject);
	static bool canFinishFromRollResult(GameObject* gameObject);

};

