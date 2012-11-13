#pragma once
#include <fstream>
#include <iostream>
#include "cocos2d.h"
#include "GameObject.h"
#include "Animals.h"
#include "AnimalUnit.h"
#include <string>
using std::string;
typedef struct _Data{
	int gameType;
	int diceResult1;
	int diceResult2;
	bool lockDice;
	bool lockUser;
	int currentTurn;
	int point[4];
	int teamNo[4];
	int unitFinished[4];
	bool onWay[4][4];
	int finishedStep[4][4];
	int pathWent[4][4];
	CCPoint location[4][4];
	bool isCalledDice;
}Data;
class SaveLoad
{
public:
	SaveLoad(void);
	~SaveLoad(void);
	static Data loadFromFile(int mode);
	static void saveToFile(Data data, int mode);
	static string getFileName(int mode);
	static bool checkExist(string fileName);
};

