#include "AIGameScene.h"
#include "Config.h"
#include "MenuScene.h"
#include "MusicHelper.h"
#include "GameObject.h"
#include "AnimalUnit.h"
#include "AIGameLogic.h"

#define  PLAYER 0
#define  NOT_HAVE_UNIT_ON_WAY 100
using namespace cocos2d;

bool AIGameScene::init()
{	
	GameScene::init();

	CCArray* menuArray = CCArray::create();
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	//set dice and diceAction

	//xuc xac
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(Config::dice_plist);
	CCSpriteBatchNode *diceSpriteBatchNode =  CCSpriteBatchNode::create(Config::dice_texture);
	char fn[128];
	CCAnimation* diceAnim =CCAnimation::create();

	for (int i = 1; i <= 6; i++) 
	{
		sprintf(fn, "%d.png", i);
		CCSpriteFrame* pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fn);
		diceAnim->addSpriteFrame(pFrame);
	}

	diceAnim->setDelayPerUnit(0.01f);
	//create sprite first frame from animation first frame

	char frame[64];
	if(gameObject->getDiceResult1() == 0){//new game
		sprintf(frame, "1.png");
	}else{//load game
		sprintf(frame, "%d.png",gameObject->getDiceResult1());
	}

	this->diceA = CCSprite::createWithSpriteFrameName(frame);
	this->diceA->retain();

	diceAminationAction = CCRepeatForever::create(CCAnimate::create(diceAnim));
	diceAminationAction->setOriginalTarget(diceA);
	diceAminationAction->retain();
	//create sprite first frame from animation first frame
	if(gameObject->getDiceResult2() == 0){//new game
		sprintf(frame, "1.png");
	}else{//load game
		sprintf(frame, "%d.png",gameObject->getDiceResult2());
	}
	this->diceB = CCSprite::createWithSpriteFrameName(frame);
	this->diceB->retain();

	//xuc xac button 1
	CCMenuItemSprite *diceButton1 = CCMenuItemSprite::create(diceA,diceA,diceA,this,menu_selector(AIGameScene::buttonDiceCallback));
	diceButton1->setPosition(ccp(size.width-100-40, size.height-60));
	menuArray->addObject(diceButton1);
	//xuc xac button 2
	CCMenuItemSprite *diceButton2 = CCMenuItemSprite::create(diceB,diceB,diceB,this,menu_selector(AIGameScene::buttonDiceCallback));
	diceButton2->setPosition(ccp(size.width-100+40, size.height-60));
	menuArray->addObject(diceButton2);


	//create button bo luot
	CCMenuItemFont* pButtonSkip = CCMenuItemFont::create(
							"Skip",
							 this,
							 menu_selector(AIGameScene::buttonSkipCallback));

	pButtonSkip->setFontSizeObj(Config::objectFontSize);
	pButtonSkip->setPosition(ccp(size.width-100, size.height*2/3+70));
	pButtonSkip->setColor(ccORANGE);
	menuArray->addObject(pButtonSkip);

	// Create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::createWithArray(menuArray);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu,1);

	//update after called
	this->schedule(schedule_selector(GameScene::update));
	//random
	srand ( time(NULL));
	return true;
}

void AIGameScene::autoPlay(){
	CCLog("tu dong do xi ngau");
	// tu dong do xi ngau cho AI
	CCCallFunc* firstCallDice		= CCCallFunc::create(this, callfunc_selector(AIGameScene::diceCallback));
	CCCallFunc* secondCallDice		= CCCallFunc::create(this, callfunc_selector(AIGameScene::diceCallback));
	CCDelayTime* timeDelay			= CCDelayTime::create(2.0f);
	this->runAction(CCSequence::create(timeDelay, firstCallDice, timeDelay, secondCallDice,NULL));
}

void AIGameScene::buttonSkipCallback(CCObject* sender)
{
	// chi PLAYER moi dc nhan SKIP, AI tu dong nhan SKIP
	if(gameObject->getCurrentTurn()->getTeamNo() == PLAYER)
		this->skipCallBack();
	else 
		MessageBox(NULL,L"only player can click SKIP button", L"", MB_OK | MB_ICONINFORMATION);
}

void AIGameScene::skipCallBack(){
	if(gameObject->getLockUser())
	{
		MusicHelper::playEffect(MusicHelper::btWrong, false);
	}else
	{
		gameObject->unSelect();
		gameObject->deleteAllLightUpWay();
		gameObject->removeButtonGo();
		gameObject->resetCurrentUnit();
		gameObject->setLockDice(false);
		MusicHelper::playEffect(MusicHelper::btSkip, false);
		if(gameObject->canContinueRollFromRollResult())
		{//skip luot thoi
			CCLog("skip dice roll");
		}else
		{
			gameObject->changeTurn();
			int teanNo =gameObject->getCurrentTurn()->getTeamNo();
			if( teanNo != PLAYER) {
				this->autoPlay();
			}
			else{
				// TO DO: player do xi ngau va choi
				// MessageBox(NULL,L"PLAYER", L"", MB_OK | MB_ICONINFORMATION);
				CCLog("PLAYER ");
			}
		}
		gameObject->resetDice();
	}
}
void AIGameScene::buttonDiceCallback(CCObject* sender){
	this->diceCallback();
}
void AIGameScene::diceCallback(){
	CCLog("tu dong do xi ngau");
	if(gameObject->getLockUser())
	{
		MusicHelper::playEffect(MusicHelper::btWrong,false);
		return;
	}

	if(!isCalledDice)
	{
		if(MusicHelper::getIdDice() == -1){
			MusicHelper::setIdDice(MusicHelper::playEffect(MusicHelper::sfxDice, true));
		}else{
			MusicHelper::resumeEffect(MusicHelper::getIdDice());
		}
		isCalledDice = TRUE;
		diceA->stopAllActions();
		diceA->runAction( diceAminationAction);
		diceB->stopAllActions();
		diceB->runAction((CCAction*)diceAminationAction->copy());
		gameObject->resetDice();
	}
	else{
		MusicHelper::pauseEffect(MusicHelper::getIdDice());

		char fn[128];
		int kq1=rand()%6+1;

		diceA->pauseSchedulerAndActions();
		sprintf(fn, "%d.png", kq1);
		gameObject->setDiceResult1(kq1);
		diceA->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fn));

		int random = rand()%4 + 1;
		int kq2;
		CCLog("random = %d", random);
		if( (AIGameLogic::isHaveUnitOnInitLocation(gameObject->getCurrentTurn()) && random == 1 && gameObject->getCurrentTurn()->getTeamNo()!= PLAYER) || random == 3)
			kq2 = kq1; 
		else
			kq2 = rand()%6+1;

		diceB->pauseSchedulerAndActions();
		sprintf(fn, "%d.png", kq2);
		gameObject->setDiceResult2(kq2);
		diceB->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fn));

		isCalledDice =FALSE;
		gameObject->setLockDice(true);
		CCLog("kq xuc xac %d %d",gameObject->getDiceResult1(),gameObject->getDiceResult2());

		// kiem tra ket qua xi ngau
		diceResultA = gameObject->getDiceResult1();
		diceResultB = gameObject->getDiceResult2();

		if(gameObject->canContinueRollFromRollResult())
		{
			MusicHelper::playEffect(MusicHelper::moreTurn,false);
		}

		this->checkResultDice(diceResultA, diceResultB);
	}
}

void AIGameScene::checkResultDice(int diceA, int diceB){
	CCLog("dice result: %d - %d", diceA, diceB);
	float time = -1.0;
	if(gameObject->getCurrentTurn()->getTeamNo() != PLAYER){
		AnimalUnit* unitSelected = this->unitSelected(diceA, diceB);
		if (unitSelected == NULL){// ko chon duoc unit de di -> SKIP den team ke tiep
			CCLog("khong chon duoc unit nao!");
			this->skipCallBack();
			if(diceA == diceB) // neu do duoc 2 xi ngau bang nhau ma ko di duoc phai skip 1 lan nua
				this->skipCallBack();
		}
		else{
			gameObject->setCurrentSelectUnit(unitSelected);
			time = AIGameLogic::goCallback(gameObject, unitSelected, diceB+diceA);
			if (time == -1.0){ // ko di duoc
				CCLog("GO nhung ko di duoc");
				this->skipCallBack();
				return;
			}
			if (diceA == diceB){ // truong hop do xi ngau giong nhau, sau khi GO duoc do xi ngau lan nua
				this->autoPlay();
			}
			else{// truong hop xi ngau khac nhau, sau khi GO tu dong SKIP
				CCLog("truong hop so xi ngau khac nhau -> khong duoc di nua");
				this->skipCallBack();
			}
		}
	}
	else { // PLAYER
		CCLog("player GO");
		time = GameLogic::goCallback(gameObject, diceA+diceB);
		if(time == -1)
			CCLog("PLAYER GO nhung ko di duoc");
		if(diceA != diceB){
			this->skipCallBack();
			//this->autoPlay();
		}
	}
}

AnimalUnit* AIGameScene::unitSelected(int diceA, int diceB){
	AnimalUnit* selectUnit = NULL;
	
	if (diceA == diceB){
		CCLog("2 xi ngau bang nhau");
		// uu tien ve dich truoc
		for (int i = 0 ; i<4 ; i++)	{
			AnimalUnit* unit = gameObject->getCurrentTurn()->getUnit(i);
			if(unit->getPathWent() == 56){
				CCLog("unit uu tien ve dich");
				return unit;
			}
		}
		
		// uu tien xuat quan
		for (int i = 0 ; i<4 ; i++)	{
			AnimalUnit* unit = gameObject->getCurrentTurn()->getUnit(i);
			if(unit->isOnInitLocation() && !AIGameLogic::haveAnyUnitAtStartPosition(gameObject->getCurrentTurn())){
				CCLog("unit uu tien ra quan");
				return unit;
			}
		}
		// chon 1 con dang tren duong de di
		for (int i = 0; i<4; i++){
			AnimalUnit* unit = gameObject->getCurrentTurn()->getUnit(i);
			if(unit->isOnWay()){
				bool havingUnitOnWay = AIGameLogic::haveUnitOnWay(gameObject, unit, diceB+diceA);
				CCLog("havingUnitOnWay = %f", havingUnitOnWay);
				if(!havingUnitOnWay){
					CCLog("chon 1 con tren duong va ko bi chan di");
					return unit;
				}
			}
		}

	} else{//diceA # diceB
		// uu tien ve dich truoc
		CCLog("2 xi ngau khac nhau");
		for (int i = 0 ; i<4 ; i++)	{
			AnimalUnit* unit = gameObject->getCurrentTurn()->getUnit(i);
			if(unit->getPathWent() == 56){
				CCLog("unit uu tien ve dich");
				return unit;
			}
		}
		for (int i = 0 ; i<4 ; i++)	{
			AnimalUnit* unit = gameObject->getCurrentTurn()->getUnit(i);
			bool havingUnitOnWay = AIGameLogic::haveUnitOnWay(gameObject, unit, diceB+diceA);
			CCLog("havingUnitOnWay = %f", havingUnitOnWay);
			if(unit->isOnWay() && havingUnitOnWay == FALSE){
					CCLog("unit dang di tren duong");
					return unit;
			}
		}
	}

	return selectUnit;
}

