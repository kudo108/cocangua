#include "AnimalUnit.h"
/*
Chua nhung thong tin ve 1 con co
*/

AnimalUnit::AnimalUnit(CCPoint _initLocation, const char* imageLink, CCNode* parent)
{
	this->initLocation = _initLocation;//vi tri trong chuong
	this->location = _initLocation;
	this->sprite = CCSprite::create(imageLink);
	this->sprite->setPosition(location);
	this->path_went = -1;
	parent->addChild(this->sprite,100);
	this->sprite->retain();
}
CCPoint AnimalUnit::getLocation(){
	return this->location;
}

AnimalUnit::~AnimalUnit(void)
{
	this->sprite->autorelease();
}
void AnimalUnit::born(){//tu chuong ra duong
	this->location = this->initLocation;
}
void AnimalUnit::go(int path){//di them dc path buoc
	
}
void AnimalUnit::finish(int x){//den dich buoc thu x

}
void AnimalUnit::die(){//chet, ve lai chuong

}
void AnimalUnit::dance()
{

}
