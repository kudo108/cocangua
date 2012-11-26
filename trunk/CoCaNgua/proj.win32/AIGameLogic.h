#pragma once
#include "GameLogic.h"
#include "Animals.h"

class AIGameLogic : public GameLogic
{
public:
	static float goCallback(GameObject* gameObject, AnimalUnit* unitSelected, int tag);
	static bool isHaveUnitOnInitLocation(Animals* team);
	static bool haveAnyUnitAtStartPosition(Animals* animals);
	static bool haveUnitOnWay(GameObject*gameObject, AnimalUnit*unitCurr, int step);
	static AnimalUnit* otherUnitAtEndWay(GameObject* gameObject, AnimalUnit* unitCurr, int step);
};

