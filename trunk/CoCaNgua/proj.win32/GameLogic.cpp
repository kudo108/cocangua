#include "GameLogic.h"
#include "MusicHelper.h"

GameLogic::GameLogic(GameObject* gObj)
{
	gameObject = gObj;
}

float GameLogic::goCallback()
{
	//bool holdCurrentTurn = false;
	if (gameObject->getCurrentSelectUnit()==NULL) return -1.0f;
	
	//delete lightup
	gameObject->deleteAllLightUp();
	
	//delete select
	gameObject->unSelect();

	//get current select unit
	AnimalUnit* unit = gameObject->getCurrentSelectUnit();
	//neu o trong chuong + ra quan dc=> ra quan
	if(unit->isOnInitLocation())
	{
		if(gameObject->canInitFromRollResult())
		{
			//xem thu co da dc ko
			AnimalUnit* unluckyUnit = gameObject->getUnitOnInitLocation(gameObject->getCurrentTurn()->getTeamNo());
			if(unluckyUnit != NULL)// co
			{
				if(unluckyUnit->getTeam()->getTeamNo() != unit->getTeam()->getTeamNo()) // khac team
				{
					unluckyUnit->die(-1);
					float time = unit->born();
					unit->kick(-1);
					checkForChangeTurn();
					return time;
				}else // cung team ko ra quan dc
				{
					return -1.0f;
					//holdCurrentTurn = true;//khong mat luot
				}
			}else
			{
				float time =unit->born();
				checkForChangeTurn();
				return time;
			}
		}else
		{
			return -1.0f;
		}
	}
	else if (unit->isOnWay())
	{
		if(unit->getPathWent() != 56)
		{
			int step = gameObject->getStepFromRollResult();
			if(unit->getPathWent() + step <= 56) //neu di thi ko qua chuong
			{
				int check = gameObject->havingUnitOnWay(step);
				if(check < 16)//khong co hoac co con o cuoi
				{
					if(check >= 0)// co con o cuoi
					{
						if(gameObject->getUnitByTag(check)->getTeam()->getTeamNo() == unit->getTeam()->getTeamNo())//cung team
						{
							return -1.0f;
							//holdCurrentTurn = true;//khong mat luot
						}else
						{
							gameObject->getUnitByTag(check)->die(step);
							float time = unit->go(step);
							unit->kick(step);
							checkForChangeTurn();
							return time;
						}
					}else {// check = -1 -> ko co
						//free to go
						float time = unit->go(step);
						checkForChangeTurn();
						return time;
					}
				}
				else// if (check == 100)// co qua nhieu
				{
					return -1.0f;
					//khong di dc
					//holdCurrentTurn = true;//khong mat luot
				}
			}else// neu di se qua chuong
			{
				return -1.0f;
			}
		}else // dung truoc cua chuong
		{
			int nextStep = unit->getFinishStep();
			int teamNo = unit->getTeam()->getTeamNo();
			if(gameObject->canFinishFromRollResult() && !gameObject->havingUnitOnFinish(teamNo, nextStep))
			{
				float time = unit->finish();
				checkForChangeTurn();
				return time;
			}else
			{
				return -1.0f;//khong mat luot
			}
		}
	}else
	{
		return -1.0f;
	}
	
}
void GameLogic::selectCallback()
{
	
	if(!gameObject->canSelectUnit())
	{
		MusicHelper::playEffect(MusicHelper::btWrong,false);
		return;
	}
	AnimalUnit* unit = gameObject->getCurrentSelectUnit();
	//clear another lightup
	gameObject->deleteAllLightUp();

	if(unit->getTeam() != gameObject->getCurrentTurn())
	{
		//unselect
		gameObject->unSelect();
		gameObject->resetCurrentUnit();
		return;//khac team ko cho di
	}
	
	MusicHelper::playEffect(unit->select_sound, false);

	CCLog("selected unit");
	//select amination unit
	gameObject->select(unit->getLocation());
	//light up
	if(unit->isOnInitLocation())
	{
		if(gameObject->canInitFromRollResult())
		{
			AnimalUnit* unluckyUnit = gameObject->getUnitOnInitLocation(unit->getTeam()->getTeamNo());
			if(unluckyUnit == NULL)// khong bi con nao chan
			{
				gameObject->lightUp(unit->getBornLocation());
			}else// co con chan
			{
				if(unluckyUnit->getTeam()->getTeamNo() != unit->getTeam()->getTeamNo())//khong cung team
				{
					gameObject->lightUp(unit->getBornLocation());
				}else
				{//khong di dc
				}
			}
		}
	}
	else if (unit->isOnWay())
	{
		CCLog("Check: Unit is on way");
		if(unit->getPathWent() != 56)
		{
			int step = gameObject->getStepFromRollResult();
			if(unit->getPathWent() + step <= 56) //neu di thi ko qua chuong
			{
				gameObject->getMap()->getNextLocationsInWay(unit->getLocation(), step);
				int check = gameObject->havingUnitOnWay(step);
				CCLog("Check: havingUnitOnWay = %d",check);
				if(check < 16) // ko co hoac co 1 con o cuoi cung
				{
					if(check >=0) // co con cuoi cung
					{
						if(gameObject->getUnitByTag(check)->getTeam()->getTeamNo() == unit->getTeam()->getTeamNo())//cung team
						{// => ko di dc => khong light up
						}else//light up
						{
							CCPointArray *next = gameObject->getMap()->getNextWay();
							for(int i = 0; i < step; i++)
							{
								gameObject->lightUp(next->getControlPointAtIndex(i));
							}
						}
					}
					else//khong co con nao
					{
						CCPointArray * next = gameObject->getMap()->getNextWay();
						for(int i = 0; i < step; i++)
						{
							gameObject->lightUp(next->getControlPointAtIndex(i));
						}
					}
				}
				else 
				{// co qua nhieu
					//khong light up
				}
			}else// neu di se bi qua chuong dich-> khong cho di
			{
			}
		} else
		{// dung truoc cong finish
			int nextStep = unit->getFinishStep();
			int teamNo = unit->getTeam()->getTeamNo();
			if(gameObject->canFinishFromRollResult())
			{
				if(gameObject->canFinishFromRollResult() && 
							!gameObject->havingUnitOnFinish(teamNo, nextStep))
				{
					gameObject->lightUp(gameObject->getMap()->getFinishLocation(teamNo,nextStep));
				}
			}
		}
	}
	
}
void GameLogic::checkForChangeTurn()
{
	if(! (gameObject->canContinueRollFromRollResult()))
	{
		//update turn
		gameObject->changeTurn();
	}
	gameObject->resetDice();
	gameObject->resetCurrentUnit();
}