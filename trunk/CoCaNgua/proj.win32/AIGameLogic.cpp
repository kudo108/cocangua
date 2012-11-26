#include "AIGameLogic.h"
#include "cocos2d.h"
#include "MapLocation.h"

#define CUA_CHUONG 56

// ham tra ve quan cua team khac nam o vi tri cuoi duong khong de kick
AnimalUnit* AIGameLogic::otherUnitAtEndWay(GameObject* gameObject, AnimalUnit* unitCurr, int step){
	MapLocation* map = new MapLocation(600, unitCurr->getSprite()->getParent());
	int indexCurrPosition = map->getIndexLocation(unitCurr->getLocation());
	for(int i = 0; i < 4; i++){
		Animals* animalTeam = gameObject->getAnimal(i);
		for(int j = 0; j < 4; j++){
			AnimalUnit* unit = animalTeam->getUnit(j);
			if(unit->isOnWay()){
				int indexOfUnit = map->getIndexLocation(unit->getLocation());
				if(((indexCurrPosition + step) == indexOfUnit) || ((indexCurrPosition + step - 56) == indexOfUnit))
					return unit;
			}
		}
	}
	return NULL;
}
// ham kiem tra co quan nao chan duong di khong trong step buoc
bool AIGameLogic::haveUnitOnWay(GameObject* gameObject, AnimalUnit* unitCurr, int step){
	MapLocation* map = new MapLocation(600, unitCurr->getSprite()->getParent());
	int indexCurrPosition = map->getIndexLocation(unitCurr->getLocation());
	for(int i = 0; i < 4; i++){
		Animals* animalTeam = gameObject->getAnimal(i);
		for(int j = 0;j < 4;j++){
			AnimalUnit* unit = animalTeam->getUnit(j);
			if(unit->isOnWay()){ // kiem tra unit dang tren duong xem co can unit dang di ko
				int indexOfUnit = map->getIndexLocation(unit->getLocation());
				CCLog("kiem tra unit %d cua team %d co can duong di khong",j, i);
				if(indexOfUnit != indexCurrPosition){
					CCLog("index of unit %d. index of curr %d, step = %d",indexOfUnit, indexCurrPosition, step);
					if((indexCurrPosition + step) > indexOfUnit && indexOfUnit > indexCurrPosition) 
						return TRUE;
					if(indexCurrPosition + step > 56){
						if(indexOfUnit > indexCurrPosition && (indexOfUnit - 56) < (indexCurrPosition + step - 56))
							return TRUE;
						if(indexOfUnit + 56 > indexCurrPosition && indexOfUnit < indexCurrPosition + step - 56)
							return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}
bool AIGameLogic::haveAnyUnitAtStartPosition(Animals* animals){
	for(int i=0; i<4; i++){
		AnimalUnit* unit = animals->getUnit(i);
		if(unit->isOnStartPosition(unit, unit->getTeam()->getTeamNo()))
			return TRUE;
	}
	return FALSE;
}

bool AIGameLogic::isHaveUnitOnInitLocation(Animals* team){
	for(int i = 0; i < 4; i++){
		if(team->getUnit(i)->isOnInitLocation())
			return TRUE;
	}
	return FALSE;
}

float AIGameLogic::goCallback(GameObject* gameObject,AnimalUnit* unitSelected, int tag){
	//bool holdCurrentTurn = false;
	//if (gameObject->getCurrentSelectUnit()==NULL) return -1.0f;

	//delete lightup
	gameObject->deleteAllLightUpWay();

	//delete select
	gameObject->unSelect();

	//delete lightup Go
	gameObject->removeButtonGo();

	//neu o trong chuong + ra quan dc=> ra quan
	if(unitSelected->isOnInitLocation()){
		if(gameObject->canInitFromRollResult()){
			//xem thu co da dc ko
			AnimalUnit* unluckyUnit = gameObject->getUnitOnInitLocation(gameObject->getCurrentTurn()->getTeamNo());
			if(unluckyUnit != NULL){
				if(unluckyUnit->getTeam()->getTeamNo() != unitSelected->getTeam()->getTeamNo()){ // khac team
					unluckyUnit->die(-1);
					float time = unitSelected->born();
					unitSelected->kick(-1);
					return time;
				}
				else // cung team ko ra quan dc
					return -1.0f;
			}
			else{
				float time = unitSelected->born();
				return time;
			}
		}
		else // khong duoc xuat quan
			return -1.0f;
	}
	else if (unitSelected->isOnWay()){
		if(unitSelected->getPathWent() != CUA_CHUONG){
			int step = gameObject->getStepFromRollResult(tag);
			CCLOG("Go with tag = %d, step = %d",tag,step);
			if(unitSelected->getPathWent() + step <= 56){ //neu di thi ko qua chuong
				AnimalUnit* unLuckyUnit = otherUnitAtEndWay(gameObject, unitSelected, step);
				if(unLuckyUnit != NULL)// co con team khac nam cuoi vi tri di
					if(unLuckyUnit->getTeam()->getTeamNo() != unitSelected->getTeam()->getTeamNo()) // khac team -> da no ve chuong
						unLuckyUnit->die(step);
					else// cung team -> khong di duoc
						return -1.0;
				return unitSelected->go(step);
			}
			else// neu di se qua chuong
				return -1.0f;
		}
		
		else{ // dung truoc cua chuong
			int nextStep = unitSelected->getFinishStep();
			int teamNo = unitSelected->getTeam()->getTeamNo();
			if(gameObject->canFinishFromRollResult() && !gameObject->havingUnitOnFinish(teamNo, nextStep))
				return unitSelected->finish();
			else
				return -1.0f;//khong mat luot
		}
	}
	else
		return -1.0f;
}