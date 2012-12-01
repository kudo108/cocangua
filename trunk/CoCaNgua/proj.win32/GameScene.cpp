
#include "GameScene.h"
#include "Config.h"
#include "MenuScene.h"
#include "RuleScene.h"
#include "MusicHelper.h"
#include <windows.h>
#include "GameWinScene.h"
#include "GameOverScene.h"
#include "RacingGameLogic.h"
#include "HelpScene.h"

using namespace cocos2d;

bool GameScene::init()
{
	if(! CCScene::init() ) return false;

	isCalledDice = FALSE;
	//int gameType = this->getTag();
	//CCLOG("setup game Type = %d", gameType);
	/************GameType*****
	* 1 - classic
	* 2 - Modern
	* 3 - AI
	* 4 - Racing
	*************************/
	//gameObject = &game;
	CCLog("Game type = %d", Config::gameType);
	gameObject = new GameObject(this);
	int currentTurn = 0;
	if(Config::loadGame){
		CCLog("load game");
		currentTurn = loadGame();
	}
	
	//gameLogic = new GameLogic(gameObject);

	if(!MusicHelper::getHasTurnOffMusic()){
		MusicHelper::stopBackgroundMusic();
		MusicHelper::playBackgroundMusic(MusicHelper::gameplayMusic, GP_MUSIC);
	}

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	
	//background
	CCSprite* background = CCSprite::create(Config::newGameBackground);
    if(background)
	{
		//background->setScaleX(0.5859375);
		//background->setScaleY(0.5859375);
		background->setPosition(ccp(size.width/2-100, size.height/2));
		this->addChild(background,-1);//uu tien (nam duoi cung)
	}
	//draw way helper
	gameObject->getMap()->drawWay();

	//menu border
	CCSprite* menuBorder = CCSprite::create(Config::menuBorder);
    if(menuBorder)
	{
		menuBorder->setPosition(ccp(size.width-100, size.height/2));
		this->addChild(menuBorder,-1);//uu tien (nam duoi cung)
	}
	
	//menu
	CCArray *menuArray = CCArray::create();
	int fontSize=Config::objectFontSize;
	int jump =40;
	//demo game win

	//save
	CCMenuItemFont* pSaveGameButton = CCMenuItemFont::create(
										"Save",
										this,
										menu_selector(GameScene::saveGameCallback));
	pSaveGameButton->setFontSizeObj(fontSize);
	menuArray->addObject(pSaveGameButton);
	pSaveGameButton->setPosition(ccp(size.width-100, 4*jump));
	//Rule game
	CCMenuItemFont* pRuleGameButton = CCMenuItemFont::create(
										"Rule",
										this,
										menu_selector(GameScene::ruleCallback));
	pRuleGameButton->setColor(ccColor3B());
	pRuleGameButton->setFontSizeObj(fontSize);
	menuArray->addObject(pRuleGameButton);
	pRuleGameButton->setPosition(ccp(size.width-100, 3*jump));
	//help
	CCMenuItemFont* pHelpGameButton = CCMenuItemFont::create(
										"Help",
										this,
										menu_selector(GameScene::helpGameCallback));
	pHelpGameButton->setFontSizeObj(fontSize);
	menuArray->addObject(pHelpGameButton);
	pHelpGameButton->setPosition(ccp(size.width-100, 2*jump));
	//Quit game
	CCMenuItemFont* pQuitGameButton = CCMenuItemFont::create(
										"Quit",
										this,
										menu_selector(GameScene::quitGameCallback));
	pQuitGameButton->setFontSizeObj(fontSize);
	menuArray->addObject(pQuitGameButton);
	pQuitGameButton->setPosition(ccp(size.width-100, jump));
			
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
	CCMenuItemSprite *diceButton1 = CCMenuItemSprite::create(diceA,diceA,diceA,this,menu_selector(GameScene::diceCallback));
	diceButton1->setPosition(ccp(size.width-100-40, size.height-60));
	menuArray->addObject(diceButton1);
	//xuc xac button 2
	CCMenuItemSprite *diceButton2 = CCMenuItemSprite::create(diceB,diceB,diceB,this,menu_selector(GameScene::diceCallback));
	diceButton2->setPosition(ccp(size.width-100+40, size.height-60));
	menuArray->addObject(diceButton2);

	//create button bo luot
	CCMenuItemFont* pButtonSkip = CCMenuItemFont::create(
										"Skip",
										this,
										menu_selector(GameScene::buttonSkipCallback));
	pButtonSkip->setFontSizeObj(Config::objectFontSize);
	pButtonSkip->setPosition(ccp(size.width-100, size.height*2/3+70));
	pButtonSkip->setColor(ccORANGE);
	menuArray->addObject(pButtonSkip);
	
	//Team point Lable
	CCSprite* teamHeo =  CCSprite::create(Config::team0);
	if(teamHeo){
		teamHeo->setPosition(ccp(size.width-140,size.height/3+0*45+30));
		this->addChild(teamHeo,-10);
	}

	CCSprite* teamVit =  CCSprite::create(Config::team1);
	if(teamVit){
		teamVit->setPosition(ccp(size.width-140,size.height/3+1*45+30));
		this->addChild(teamVit,-10);
	}

	CCSprite* teamNgua =  CCSprite::create(Config::team2);
	if(teamNgua){
		teamNgua->setPosition(ccp(size.width-140,size.height/3+2*45+30));
		this->addChild(teamNgua,-10);
	}

	CCSprite* teamCho =  CCSprite::create(Config::team3);
	if(teamCho){
		teamCho->setPosition(ccp(size.width-140,size.height/3+3*45+30));
		this->addChild(teamCho,-10);
	}
	/*CCMenuItemFont* pTeam0Point = CCMenuItemFont::create("Heo:");
	pTeam0Point->setFontSizeObj(Config::objectFontSize/2);
	pTeam0Point->setPosition(ccp(size.width-140,size.height/3+0*45+30));
	menuArray->addObject(pTeam0Point);

	CCMenuItemFont* pTeam1Point = CCMenuItemFont::create("Vit:");
	pTeam1Point->setFontSizeObj(Config::objectFontSize/2);
	pTeam1Point->setPosition(ccp(size.width-140,size.height/3+1*45+30));
	menuArray->addObject(pTeam1Point);

	CCMenuItemFont* pTeam2Point = CCMenuItemFont::create("Ngua:");
	pTeam2Point->setFontSizeObj(Config::objectFontSize/2);
	pTeam2Point->setPosition(ccp(size.width-140,size.height/3+2*45+30));
	menuArray->addObject(pTeam2Point);

	CCMenuItemFont* pTeam3Point = CCMenuItemFont::create("Cun:");
	pTeam3Point->setFontSizeObj(Config::objectFontSize/2);
	pTeam3Point->setPosition(ccp(size.width-140,size.height/3+3*45+30));
	menuArray->addObject(pTeam3Point);*/
	
	//point
	team0PointLable = CCMenuItemFont::create("0");
	team0PointLable->setFontSizeObj(Config::objectFontSize/2);
	team0PointLable->setPosition(ccp(size.width-60, size.height/3+30));
	team0PointLable->setColor(ccGREEN);
	menuArray->addObject(team0PointLable);
	team0PointLable->retain();

	team1PointLable = CCMenuItemFont::create("0");
	team1PointLable->setFontSizeObj(Config::objectFontSize/2);
	team1PointLable->setPosition(ccp(size.width-60, size.height/3+75));
	team1PointLable->setColor(ccGREEN);
	menuArray->addObject(team1PointLable);
	team1PointLable->retain();

	team2PointLable = CCMenuItemFont::create("0");
	team2PointLable->setFontSizeObj(Config::objectFontSize/2);
	team2PointLable->setPosition(ccp(size.width-60, size.height/3+120));
	team2PointLable->setColor(ccGREEN);
	menuArray->addObject(team2PointLable);
	team2PointLable->retain();

	team3PointLable = CCMenuItemFont::create("0");
	team3PointLable->setFontSizeObj(Config::objectFontSize/2);
	team3PointLable->setPosition(ccp(size.width-60, size.height/3+165));
	team3PointLable->setColor(ccGREEN);
	menuArray->addObject(team3PointLable);
	team3PointLable->retain();

	//team turn image
	gameObject->getAnimal(currentTurn)->setupTeamSpriteToParent();
	
	// Create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::createWithArray(menuArray);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu,1);//ngoai cung,tuong tac

	/*CCLabelTTF *label = CCLabelTTF::labelWithString("TURN", "Helvetica", 40);
	label->setPosition(ccp(100,100));
	label->setColor(ccRED);
	CCFadeTo *fadeIn = CCFadeTo::create(0.5f, 0.3f);
	CCFadeTo *fadeOut = CCFadeTo::create(0.5f, 1.0f);
	CCFiniteTimeAction *action = CCSequence::create(fadeIn, fadeOut,NULL);
	CCRepeat *repeat = CCRepeat::create(action, 100);
	label->runAction(repeat);*/

	//this->addChild(label, 1000);
	
	//update after called
	this->schedule(schedule_selector(GameScene::update));
	
	
	//random
	srand ( time(NULL));

	return true;
}



//test
/*
void GameScene::gameOverCallback(CCObject *sender){
	//save game
	
	MusicHelper::playEffect(MusicHelper::sfxButton, false);
	MusicHelper::stopAllEffect();
	GameOverScene *menuScene = GameOverScene::create();
	CCDirector::sharedDirector()->replaceScene(menuScene);
	
}

void GameScene::gameWinCallback(CCObject* sender){
	//save game
	MusicHelper::playEffect(MusicHelper::sfxButton, false);
	MusicHelper::stopAllEffect();
	GameWinScene *menuScene = GameWinScene::create();
	CCDirector::sharedDirector()->replaceScene(menuScene);
}
*/
void GameScene::saveGameCallback(CCObject *sender)
{
	//save game
	MusicHelper::playEffect(MusicHelper::sfxButton, false);
	MusicHelper::stopAllEffect();

	Data data ;
	data.gameType = Config::gameType;
	data.diceResult1 = gameObject->getDiceResult1();
	data.diceResult2 = gameObject->getDiceResult2();
	data.lockDice = gameObject->getLockDice();
	data.lockUser = gameObject->getLockUser();
	data.isCalledDice = isCalledDice;
	for(int i = 0; i < 4; i++){
		if(gameObject->getCurrentTurn() == gameObject->getAnimal(i)){
			data.currentTurn = i;
		}
		data.point[i] = gameObject->getAnimal(i)->getPoint();
		data.teamNo[i] = gameObject->getAnimal(i)->getTeamNo();
		data.unitFinished[i] = gameObject->getAnimal(i)->getUnitFinished();
		for(int j = 0; j < 4; j++){
			data.onWay[i][j] = gameObject->getAnimal(i)->getUnit(j)->getOnWay();
			data.finishedStep[i][j] = gameObject->getAnimal(i)->getUnit(j)->getFinishStep();
			data.pathWent[i][j] = gameObject->getAnimal(i)->getUnit(j)->getPathWent();
			data.location[i][j] = gameObject->getAnimal(i)->getUnit(j)->getLocation();
		}
	}
	SaveLoad::saveToFile(data, Config::gameType);

	MessageBox( NULL, L"Game was saved successfully",L"Save game",  MB_OK | MB_ICONINFORMATION);
	//test
	/*GameOverScene *menuScene = GameOverScene::create();
	CCDirector::sharedDirector()->replaceScene(menuScene);*/
}
void GameScene::quitGameCallback(CCObject *sender)
{
	//reset load game flag
	Config::loadGame = false;
	//back to menu
	MusicHelper::playEffect(MusicHelper::sfxButton, false);
	if(MessageBox( NULL, L"Unsaved game will be lost. Are you sure ? ",L"Quit", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES){
		CCDirector::sharedDirector()->replaceScene(MenuScene::create());
		MusicHelper::stopAllEffect();
		Config::loadGame = false;
	}
}
void GameScene::helpGameCallback(CCObject *sender)
{
	//reset load game flag
	Config::loadGame = false;
	//back to menu
	MusicHelper::playEffect(MusicHelper::sfxButton, false);
	if(MessageBox( NULL, L"Unsaved game will be lost. Are you sure ? ",L"Quit", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES){
		CCDirector::sharedDirector()->replaceScene(HelpScene::create());
		MusicHelper::stopAllEffect();
		Config::loadGame = false;
	}
}
void GameScene::ruleCallback(CCObject *sender)
{
	//show rule
	MusicHelper::playEffect(MusicHelper::sfxButton, false);
	if(MessageBox( NULL, L"Unsaved game will be lost. Are you sure ? ",L"Quit", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES){
		RuleScene *gW = RuleScene::create();
		CCDirector::sharedDirector()->replaceScene(gW);
		MusicHelper::stopAllEffect();
	}
}

void GameScene::diceCallback(CCObject *sender)
{	
	if(gameObject->getLockUser())
	{
		MusicHelper::playEffect(MusicHelper::btWrong,false);
		return;
	}
	if(gameObject->getLockDice())
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
		int kq=rand()%6+1;

		diceA->pauseSchedulerAndActions();
		sprintf(fn, "%d.png", kq);
		gameObject->setDiceResult1(kq);
		diceA->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fn));

		kq=rand()%6+1;
		diceB->pauseSchedulerAndActions();
		sprintf(fn, "%d.png", kq);
		gameObject->setDiceResult2(kq);
		diceB->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fn));
		
		isCalledDice =FALSE;
		gameObject->setLockDice(true);
		CCLog("kq xuc xac %d %d",gameObject->getDiceResult1(),gameObject->getDiceResult2());

		if(gameObject->canContinueRollFromRollResult())
		{
			MusicHelper::playEffect(MusicHelper::moreTurn,false);
		}
	}
}

void GameScene::updatePoint(int teamNo)
{
	char lable[128];
	switch (teamNo)
	{
	case 0:		
		sprintf(lable, "%d", gameObject->getAnimal0()->getPoint());
		team0PointLable->setString(lable);
		break;
	case 1:
		sprintf(lable, "%d", gameObject->getAnimal1()->getPoint());
		team1PointLable->setString(lable);
		break;
	case 2:
		sprintf(lable, "%d", gameObject->getAnimal2()->getPoint());
		team2PointLable->setString(lable);
		break;
	case 3:
		sprintf(lable, "%d", gameObject->getAnimal3()->getPoint());
		team3PointLable->setString(lable);
		break;
	default:
		break;
	}
}

void GameScene::buttonSkipCallback(CCObject* sender)
{
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
			CCLog("change Turn");
			gameObject->changeTurn();
		}
		gameObject->resetDice();
	}
}

void GameScene::update(CCTime dt)
{
	//update point
	updatePoint(0);
	updatePoint(1);
	updatePoint(2);
	updatePoint(3);

	//check for the winer team
	if(gameObject->getAnimal0()->isFinished()) 
	{
		MusicHelper::stopAllEffect();
		GameWinScene *gameWin = GameWinScene::create();
		CCDirector::sharedDirector()->replaceScene(gameWin);
	}
	if(gameObject->getAnimal1()->isFinished()) 
	{
		MusicHelper::stopAllEffect();
		GameWinScene *gameWin = GameWinScene::create();
		CCDirector::sharedDirector()->replaceScene(gameWin);
	}
	if(gameObject->getAnimal2()->isFinished()) 
	{
		MusicHelper::stopAllEffect();
		GameWinScene *gameWin = GameWinScene::create();
		CCDirector::sharedDirector()->replaceScene(gameWin);
	}
	if(gameObject->getAnimal3()->isFinished()) 
	{
		MusicHelper::stopAllEffect();
		GameWinScene *gameWin = GameWinScene::create();
		CCDirector::sharedDirector()->replaceScene(gameWin);
	}
}


GameScene::~GameScene()
{
	CCLog("delete Object");
	diceA->release();
	diceB->release();
	team0PointLable->release();
	team1PointLable->release();
	team2PointLable->release();
	team3PointLable->release();
	gameObject->release();
}


void GameScene::buttonSelectCallback(CCObject *sender)
{
	AnimalUnit* unit = (AnimalUnit*) ((CCMenuItemSprite*)sender)->getUserData();
	unit->printOutDebugInfo();
	gameObject->setCurrentSelectUnit(unit);
	//if gameType == 1 select 1, if gameType ==2 select 2
	
	switch(Config::gameType)
	{
	case CLASSIC:
		GameLogic::selectCallback(gameObject);
		break;
	case MODERN:
		break;
	case AI:
		if(gameObject->getCurrentSelectUnit()->getTeam()->getTeamNo() == 0)// PLAYER
			GameLogic::selectCallback(gameObject);
		break;
	case RACING:
		RacingGameLogic::selectCallback(gameObject);
		break;
	default:
		break;
	}
}

int GameScene::loadGame(){
	CCLog("load game function");
	Data data = SaveLoad::loadFromFile(Config::gameType);
	CCLOG("GameType : %d", data.gameType);
	CCLOG("DiceResult1 : %d", data.diceResult1);
	CCLOG("DiceResult2 : %d", data.diceResult2);
	CCLOG("Location : %f %f", data.location[0][0].x, data.location[0][0].y);

	Config::gameType = data.gameType;
	gameObject->setDiceResult1(data.diceResult1);
	gameObject->setDiceResult2(data.diceResult2);
	gameObject->setLockDice(data.lockDice);
	gameObject->setLockUser(data.lockUser);
	gameObject->setCurrentTurn(gameObject->getAnimal(data.currentTurn));
	this->setIsCalledDice(data.isCalledDice);
		
	for(int i = 0; i < 4; i++){
		gameObject->getAnimal(i)->setPoint(data.point[i]);
		gameObject->getAnimal(i)->setTeamNo(data.teamNo[i]);
		gameObject->getAnimal(i)->setUnitFinished(data.unitFinished[i]);
		for(int j = 0; j < 4; j++){
			gameObject->getAnimal(i)->getUnit(j)->setOnWay(data.onWay[i][j]);
			gameObject->getAnimal(i)->getUnit(j)->setFinishStep(data.finishedStep[i][j]);
			gameObject->getAnimal(i)->getUnit(j)->setPathWent(data.pathWent[i][j]);
			CCPoint loc = data.location[i][j];
			gameObject->getAnimal(i)->getUnit(j)->setLocation(loc);
			if(!loc.equals(gameObject->getAnimal(i)->getUnit(j)->getInitLocation())){
				CCFiniteTimeAction *moveAction = CCMoveTo::create(0,loc);
				gameObject->getAnimal(i)->getUnit(j)->getButton()->runAction(moveAction);
			}
				
		}
	}
	return data.currentTurn;
}
