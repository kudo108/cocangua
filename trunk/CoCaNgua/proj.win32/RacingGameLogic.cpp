#include "RacingGameLogic.h"
#include "MusicHelper.h"


float RacingGameLogic::goCallback(GameObject* gameObject, int tag)
{
	//bool holdCurrentTurn = false;
	if (gameObject->getCurrentSelectUnit()==NULL) return -1.0f;
	
	//delete lightup
	gameObject->deleteAllLightUpWay();
	
	//delete select
	gameObject->unSelect();

	//delete lightup Go
	gameObject->removeButtonGo();

	//get current select unit
	AnimalUnit* unit = gameObject->getCurrentSelectUnit();
	
	//neu o trong chuong + ra quan dc=> ra quan
	if(unit->isOnInitLocation())
	{
		if(canInitFromRollResult(gameObject))
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
					checkForChangeTurn(gameObject);
					return time;
				}else // cung team ko ra quan dc
				{
					return -1.0f;
					//holdCurrentTurn = true;//khong mat luot
				}
			}else
			{
				float time =unit->born();
				checkForChangeTurn(gameObject);
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
			int step = gameObject->getStepFromRollResult(tag);
			CCLOG("Go with tag = %d, step = %d",tag,step);
			if(unit->getPathWent() + step <= 56) //neu di thi ko qua chuong
			{
				AnimalUnit * unluckyUnit = havingUnitAtPosition(gameObject,
						gameObject->getMap()->getNextWay()->getControlPointAtIndex(step-1));
					if(unluckyUnit == NULL) //khong co
					{
						float time = unit->go(step);
						checkForChangeTurn(gameObject);
						return time;
					}else //co 
					{
						//kiem tra cung team
						if(unluckyUnit->getTeam()->getTeamNo() == unit->getTeam()->getTeamNo())//cung team
						{
							return -1.0f;
						}//khong lam gi ca
						else
						{
							unluckyUnit->die(step);
							float time = unit->go(step);
							unit->kick(step);
							checkForChangeTurn(gameObject);
							return time;
						}
					}
				
			}else// neu di se qua chuong
			{
				return -1.0f;
			}
			
		}else // dung truoc cua chuong
		{
			int nextStep = unit->getFinishStep();
			if (nextStep >= 6)
			{
				return -1.0f;
			}
			int teamNo = unit->getTeam()->getTeamNo();
			if(canFinishFromRollResult(gameObject) && !gameObject->havingUnitOnFinish(teamNo, nextStep))
			{
				float time = unit->finish();
				checkForChangeTurn(gameObject);
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
void RacingGameLogic::selectCallback(GameObject* gameObject)
{
	CCLOG("select by RacingGame");	
	if(!gameObject->canSelectUnit())
	{
		MusicHelper::playEffect(MusicHelper::btWrong,false);
		return;
	}
	AnimalUnit* unit = gameObject->getCurrentSelectUnit();
	//clear another lightup
	gameObject->deleteAllLightUpWay();
	gameObject->removeButtonGo();

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
		if(canInitFromRollResult(gameObject))
		{
			AnimalUnit* unluckyUnit = gameObject->getUnitOnInitLocation(unit->getTeam()->getTeamNo());
			if(unluckyUnit == NULL)// khong bi con nao chan
			{
				//gameObject->lightUpWay(unit->getBornLocation());
				gameObject->createButtonGo(unit->getBornLocation(),0);
			}else// co con chan
			{
				if(unluckyUnit->getTeam()->getTeamNo() != unit->getTeam()->getTeamNo())//khong cung team
				{
					//gameObject->lightUpWay(unit->getBornLocation());
					gameObject->createButtonGo(unit->getBornLocation(),0);
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
			for(int tag = 1; tag <=3; tag ++)
			{
				int step = gameObject->getStepFromRollResult(tag);
				if(unit->getPathWent() + step <= 56) //neu di thi ko qua chuong
				{
					gameObject->getMap()->getNextLocationsInWay(unit->getLocation(), step);
					AnimalUnit * unluckyUnit = havingUnitAtPosition(gameObject,
						gameObject->getMap()->getNextWay()->getControlPointAtIndex(step-1));
					if(unluckyUnit == NULL) //khong co
					{
						CCPointArray *next = gameObject->getMap()->getNextWay();
						for(int i = 0; i < step-1; i++)
						{
							gameObject->lightUpWay(next->getControlPointAtIndex(i));
						}
						//create Go button
						gameObject->createButtonGo(next->getControlPointAtIndex(step-1),tag);
					}else //co 
					{
						//kiem tra cung team
						if(unluckyUnit->getTeam()->getTeamNo() == unit->getTeam()->getTeamNo())//cung team
						{
						}//khong lam gi ca
						else
						{
							CCPointArray *next = gameObject->getMap()->getNextWay();
							for(int i = 0; i < step-1; i++)
							{
								gameObject->lightUpWay(next->getControlPointAtIndex(i));
							}
							//create Go button
							gameObject->createButtonGo(next->getControlPointAtIndex(step-1),tag);
						}
					}
					
				}else// neu di se bi qua chuong dich-> khong cho di
				{
				}
			}
		} else
		{// dung truoc cong finish
			int nextStep = unit->getFinishStep();
			if(nextStep >= 6) return;
			int teamNo = unit->getTeam()->getTeamNo();
			if(canFinishFromRollResult(gameObject) && 
						!gameObject->havingUnitOnFinish(teamNo, nextStep))
			{
				//gameObject->lightUpWay(gameObject->getMap()->getFinishLocation(teamNo,nextStep));
				gameObject->createButtonGo(gameObject->getMap()->getFinishLocation(teamNo,nextStep),0);
			}
		}
	}
	
}
AnimalUnit* RacingGameLogic::havingUnitAtPosition(GameObject* gameObject, CCPoint point)
{
	for(int i = 0; i < 16; i++)
	{
		AnimalUnit* unit = gameObject->getUnitByTag(i);
		if(unit->getLocation().equals(point)) return unit;
	}
	return NULL;
}
bool RacingGameLogic::canInitFromRollResult(GameObject* gameObject)
{
	int dice1 = gameObject->getDiceResult1();
	if(dice1 == 1 || dice1 == 6) return true;
	int dice2 = gameObject->getDiceResult2();
	if(dice2 == 1 || dice2 == 6) return true;
	if(dice1 == dice2) return true;
	return false;
}
bool RacingGameLogic::canFinishFromRollResult(GameObject* gameObject)
{
	return canInitFromRollResult(gameObject);
}