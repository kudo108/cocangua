#pragma once
#include "GameLogic.h"
#include "Animals.h"

class AIGameLogic : public GameLogic
{
public:
	static float goCallback(GameObject* gameObject, AnimalUnit* unitSelected, int tag, CCNode* scene);
	static bool isHaveUnitOnInitLocation(Animals* team);
	static bool haveAnyUnitAtStartPosition(Animals* animals);
	static bool isContinueRollDice(GameObject* gameObj);
	static bool haveUnitOnWay(GameObject*gameObject, AnimalUnit*unitCurr, int step);
	static AnimalUnit* otherUnitAtEndWay(GameObject* gameObject, AnimalUnit* unitCurr, int step);
};

