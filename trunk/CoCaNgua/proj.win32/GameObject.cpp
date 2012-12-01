#include "GameObject.h"
#include "Config.h"
#include "GameScene.h"
#include "GameLogic.h"
#include "RacingGameLogic.h"
#include "AIGameLogic.h"

using namespace cocos2d;

GameObject::GameObject(CCNode* _parent)
{
	this->parent = _parent;
	map = new MapLocation(600, parent);

	//init animals
	animal0 = new Animals(0,parent,map);
	animal1 = new Animals(1,parent,map);
	animal2 = new Animals(2,parent,map);
	animal3 = new Animals(3,parent,map);
	
	currentTurn=animal0;
	currentSelectUnit = NULL;
	//buttonGo = NULL;
	buttonGoArray = CCArray::create();
	buttonGoArray->retain();
	//dice
	resetDice();
	lockDice = false;
	lockUser = false;

	//setup LightupAction
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(Config::lightup_way_plist);
	//CCSpriteBatchNode *lightupSpriteSheet =  CCSpriteBatchNode::create(Config::lightup_way_image);
	char fn[128];
	CCAnimation* lightupAnimation =CCAnimation::create();
	for (int i = 1; i <= 2; i++) 
	{
		sprintf(fn, "way%d.png", i);
		CCSpriteFrame* pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fn);
		lightupAnimation->addSpriteFrame(pFrame);
	}
    lightupAnimation->setDelayPerUnit(0.2f);
	lightupAction = CCRepeatForever::create( CCAnimate::create(lightupAnimation));
	lightupAction->retain();

	//setup lightup Array
	lightupArray = CCArray::create();
	lightupArray->retain();

	//setup select amination
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(Config::select_plist);
//	CCSpriteBatchNode *selectSpriteSheet =  CCSpriteBatchNode::create(Config::select_image);
	CCAnimation* selectAnimation =CCAnimation::create();
	for (int i = 1; i <= 3; i++) 
	{
		sprintf(fn, "select%d.png", i);
		CCSpriteFrame* pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fn);
		selectAnimation->addSpriteFrame(pFrame);
	}
    selectAnimation->setDelayPerUnit(0.2f);
	selectAction = CCRepeatForever::create( CCAnimate::create(selectAnimation));
	selectAction->retain();

	//selectedSprite
	selectedSprite = NULL;

	//button go
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(Config::lightup_go_plist);
//	CCSpriteBatchNode *selectSpriteSheet =  CCSpriteBatchNode::create(Config::lightup_go_image);
	CCAnimation* buttonGoAnimation =CCAnimation::create();
	for (int i = 1; i <= 3; i++) 
	{
		sprintf(fn, "lightup%d.png", i);
		CCSpriteFrame* pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fn);
		buttonGoAnimation->addSpriteFrame(pFrame);
	}
    buttonGoAnimation->setDelayPerUnit(0.2f);
	buttonGoAction = CCRepeatForever::create( CCAnimate::create(buttonGoAnimation));
	buttonGoAction->retain();
	
}

GameObject::GameObject(){
}

void GameObject::buttonGoCallback(CCObject* sender)
{
	int tag = ((CCMenuItemSprite*)sender)->getTag();
	CCLOG("buttonGoCallback with tag = %d",tag);
	float time ;//= GameLogic::goCallback(this,tag);
	switch (Config::gameType)
	{
	case CLASSIC:
		time = GameLogic::goCallback(this,tag);
		break;
	case MODERN:
		break;
	case AI:
		time = AIGameLogic::goCallback(this, this->getCurrentSelectUnit(), tag, parent);
		break;
	case RACING:
		time = RacingGameLogic::goCallback(this,tag);
		break;
	default:
		break;
	}
	CCLog("wait time = %f",time);
	if (time > 0.0f)
	{
		setLockUser(true);
		setLockDice(false);
		CCFiniteTimeAction * callfunc = CCCallFunc::create(this,callfunc_selector( GameObject::releaseLockUser));
		CCAction * action = CCSequence::createWithTwoActions(CCDelayTime::create(time),callfunc);
		parent->runAction(action);
	}
}
void GameObject::releaseLockUser()
{
	setLockUser(false);
}
void GameObject::createButtonGo(CCPoint location,  int tag)
{
	/*
	if(buttonGo != NULL)
	{
		CCLog("ERROR: already have a go button");
		return;
	}
	*/
	
	CCSprite* buttonGoSprite = CCSprite::create(Config::lightup_go_init_image);
	buttonGoSprite->runAction((CCAction*) buttonGoAction->copy());
	buttonGoItem = CCMenuItemSprite::create(buttonGoSprite,buttonGoSprite,buttonGoSprite,
		this,menu_selector(GameObject::buttonGoCallback));
	buttonGoItem->setPosition(location);
	buttonGoItem->setTag(tag);
	CCMenu* buttonGo = CCMenu::createWithItem(buttonGoItem);
	buttonGo->setPosition(CCPointZero);
	buttonGo->setTag(tag);
	buttonGoArray->addObject(buttonGo);
	buttonGo->retain();
	parent->addChild(buttonGo);
	CCLog("create button Go with tag = %d", buttonGo->getTag());
}
void GameObject::removeButtonGo()
{
	//if(buttonGo != NULL)
	for(unsigned int i = 0; i < buttonGoArray->count(); i++)
	{
		CCMenu* buttonGo = (CCMenu*) buttonGoArray->objectAtIndex(i);
		//CCLog("remove button Go");
		buttonGo->removeFromParentAndCleanup(true);
		//buttonGo->release();
		//buttonGo=NULL;
	}
	buttonGoArray->removeAllObjects();
}
void GameObject::changeTurn()
{
	parent->unscheduleUpdate();
	parent->scheduleUpdate();
	currentTurn->removeTeamSpriteFromParent();
	resetCurrentUnit();
	switch(currentTurn->getTeamNo())
	{
	case 0:
		currentTurn = this->animal1;
		break;
	case 1:
		currentTurn = this->animal2;
		break;
	case 2:
		currentTurn = this ->animal3;
		break;
	case 3:
		currentTurn = this->animal0;
		break;
	default:
		break;
	}
	
	CCLog("ChangeTurn to player %d",currentTurn->getTeamNo());
	currentTurn->setupTeamSpriteToParent();
}
void GameObject::lightUpWay(CCPoint point)
{
	//check for already light up
	for(unsigned i = 0; i < lightupArray->count(); i++)
	{
		CCSprite * sprite = (CCSprite*) lightupArray->objectAtIndex(i);
		if(sprite->getPosition().equals(point)) //already light up
		{
			return;
		}
	}
	CCSprite* sprite = CCSprite::create(Config::lightup_way_init_image);
	sprite->setPosition(point);
	sprite->runAction((CCAction*)lightupAction->copy());
	parent->addChild(sprite);
	sprite->retain();
	lightupArray->addObject(sprite);
	lightupArray->retain();
}
void GameObject::deleteAllLightUpWay()
{
	for(unsigned int i = 0; i < lightupArray->count(); i++)
	{
		CCSprite* sprite = (CCSprite*)lightupArray->objectAtIndex(i);
		sprite->removeFromParentAndCleanup(true);
	};
	lightupArray->removeAllObjects();
}
void  GameObject::select(CCPoint point)
{
	//unload prev selectPoint
	if(selectedSprite!= NULL)
	{
		unSelect();
	}
	CCLog("Selected at %f, %f",point.x,point.y);
	//amination select at point
	selectedSprite = CCSprite::create(Config::select_init_image);
	selectedSprite->setPosition(point);
	selectedSprite->runAction((CCAction*)selectAction->copy());
	parent->addChild(selectedSprite);
	selectedSprite->retain();
}
void  GameObject::unSelect()
{
	if (!selectedSprite) return;
	CCLog("Unselected");
	//unload amination select at point
	selectedSprite->removeFromParentAndCleanup(true);
	selectedSprite->release();
	selectedSprite = NULL;
}
AnimalUnit * GameObject::getUnitOnInitLocation(int teamNo)
{
	CCPoint initPoint = map->getStartLocation(teamNo);
	for(int i = 0; i < 16; i ++)
	{
		AnimalUnit* unit = getUnitByTag(i);
		if(unit->getLocation().equals(initPoint)) return unit;
	}	
	return NULL;//neu ko co thi return null
}

int GameObject::havingUnitOnWay(int step)
{
	CCPointArray* way = map->getNextWay();
	CCLog("NextWay size = %d",way->count());
	//test
	for( int i = 0; i < 12; i ++)
	{
		CCLog("Way: %d = %f %f",i, way->getControlPointAtIndex(i).x,way->getControlPointAtIndex(i).y);
	}
	for(int i = 0; i < step-1; i ++)// kiem tra step-1 buoc gan do
	{
		for(int j = 0; j < 16; j++)
		{	
			CCPoint unitLocation = getUnitByTag(j)->getLocation();
			if(unitLocation.equals(way->getControlPointAtIndex(i))){
				return 100; // neu co unit thi return la nhieu qua
			}
		}
	}
	//kiem tra vi tri cuoi
	for(int i = 0; i < 16; i++)
	{
		if (getUnitByTag(i)->getLocation().equals(way->getControlPointAtIndex(step-1)))
		{
			return i;// 0->15 
		}
	}
	return -1;// khong co
}

void GameObject::resetDice()
{
	diceResult1 = 0;
	diceResult2 = 0;
}

bool GameObject::canContinueRollFromRollResult()
{
	if (diceResult1==diceResult2 && diceResult1 > 0) return true;
	return false;
}
bool GameObject::canInitFromRollResult()
{
	//kiem tra thu ket qua xuc xac la k1 va k2 thi co ra quan dc ko?
	//if(diceResult1 == 1 || diceResult1 == 6) return true;
	//if(diceResult2 == 1 || diceResult2 == 6) return true;
	
	if(diceResult1==diceResult2 && diceResult1 != 0) return true;
	if(diceResult1==1 && diceResult2 == 6) return true;
	if(diceResult1==6 && diceResult2 == 1) return true;
	
	return false;
}
bool GameObject::canFinishFromRollResult()
{
	return canInitFromRollResult();
	/*
	if(diceResult1 == diceResult2 && diceResult1>0) return true;
	if(diceResult1==1 && diceResult2 == 6) return true;
	if(diceResult1==6 && diceResult2 == 1) return true;
	return false;
	*/
}
int GameObject::getStepFromRollResult(int TAG)
{
	if(TAG==1) return diceResult1;
	if(TAG==2) return diceResult2;
	else return diceResult1+diceResult2;
	/*
	//neu ra 1 con giong nhau thi dc di = gia tri 1 con + dc them luot
	if(diceResult1 == diceResult2) return diceResult1;
	return diceResult1+diceResult2;
	*/
}
bool GameObject::canSelectUnit()
{
	if(diceResult1<=0 || diceResult2<=0) return false;
	return true;
}

GameObject::~GameObject(void)
{
	selectAction->release();
	if(selectedSprite != NULL)
		selectedSprite->release();
	lightupAction->release();
	lightupArray->removeAllObjects();
	lightupArray->release();
	delete map;
	delete animal0;
	delete animal1;
	delete animal2;
	delete animal3;
}

void GameObject::resetCurrentUnit()
{
	this->currentSelectUnit = NULL;
}

AnimalUnit* GameObject::getUnitByTag(int tag)
{
	switch(tag)
	{
	case 0:
		return animal0->getUnit0();
	case 1:
		return animal0->getUnit1();
	case 2:
		return animal0->getUnit2();
	case 3:
		return animal0->getUnit3();
	case 4:
		return animal1->getUnit0();
	case 5:
		return animal1->getUnit1();
	case 6:
		return animal1->getUnit2();
	case 7:
		return animal1->getUnit3();
	case 8:
		return animal2->getUnit0();
	case 9:
		return animal2->getUnit1();
	case 10:
		return animal2->getUnit2();
	case 11:
		return animal2->getUnit3();
	case 12:
		return animal3->getUnit0();
	case 13:
		return animal3->getUnit1();
	case 14:
		return animal3->getUnit2();
	case 15:
		return animal3->getUnit3();
	default:
		return NULL;
	}
}
int GameObject::getTagByUnit(AnimalUnit* unit)
{
	Animals* team = unit->getTeam();
	int teamNo = team->getTeamNo();
	
	if(team->getUnit0() == unit) return teamNo*4+0;
	if(team->getUnit1() == unit) return teamNo*4+1;
	if(team->getUnit2() == unit) return teamNo*4+2;
	if(team->getUnit3() == unit) return teamNo*4+3;

	return NULL;
}

bool GameObject::havingUnitOnFinish(int teamNo, int step)
{
	if(step > 5) return false;
	CCPoint p = map->getFinishLocation(teamNo,step);
	for(int i = teamNo*4; i <teamNo*4+4; i ++)
	{
		AnimalUnit* unit = getUnitByTag(i);
		if(unit->getLocation().equals(p)) return true;
	}
	return false;
}

Animals *GameObject::getAnimal(int index){
	switch(index){
	case 0:
		return animal0;
		break;
	case 1:
		return animal1;
		break;
	case 2:
		return animal2;
		break;
	case 3:
		return animal3;
		break;
	default:
		return animal0;
		break;
	}
}