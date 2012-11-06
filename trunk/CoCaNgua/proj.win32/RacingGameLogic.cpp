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
							checkForChangeTurn(gameObject);
							return time;
						}
					}else {// check = -1 -> ko co
						//free to go
						float time = unit->go(step);
						checkForChangeTurn(gameObject);
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
		if(gameObject->canInitFromRollResult())
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
								for(int i = 0; i < step-1; i++)
								{
									gameObject->lightUpWay(next->getControlPointAtIndex(i));
								}
								//create Go button
								gameObject->createButtonGo(next->getControlPointAtIndex(step-1),tag);
							}
						}
						else//khong co con nao
						{
							CCPointArray * next = gameObject->getMap()->getNextWay();
							for(int i = 0; i < step-1; i++)
							{
								gameObject->lightUpWay(next->getControlPointAtIndex(i));
							}
							gameObject->createButtonGo(next->getControlPointAtIndex(step-1),tag);
						}
					}
					else 
					{// co qua nhieu
						//khong light up
					}
				}else// neu di se bi qua chuong dich-> khong cho di
				{
				}
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
					//gameObject->lightUpWay(gameObject->getMap()->getFinishLocation(teamNo,nextStep));
					gameObject->createButtonGo(gameObject->getMap()->getFinishLocation(teamNo,nextStep),0);
				}
			}
		}
	}
	
}