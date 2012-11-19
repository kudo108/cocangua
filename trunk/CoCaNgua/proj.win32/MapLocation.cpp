#include "MapLocation.h"
#include "Config.h"

#define CLASSICMAP 1
#define NEWMAP 2
#define CURRENTMAP NEWMAP

MapLocation::MapLocation(int _winSize, CCNode* _parent)
{
	winSize = _winSize;
	scale = winSize/1024;
	parent = _parent;
	parent->retain();
	//scale = 1;
	margin = 45*scale;
	center = 512*scale;
	stepEnd = 117*scale;
	stepLength = (350/6)*scale;
	if(CURRENTMAP == CLASSICMAP) 
	{
	for(int i=0; i<=6; i++){
		wayLocation[i]= ccp(margin+i*stepLength,center-stepEnd);
		wayLocation[6+i]=ccp(center-stepEnd,(center-stepEnd)-i*stepLength);
		wayLocation[14+i]=ccp(center+stepEnd-3,margin+i*stepLength);
		wayLocation[20+i]=ccp(center+stepEnd+i*stepLength-2,center-stepEnd);
		wayLocation[28+i]=ccp(2*center-margin-i*stepLength-3,center+stepEnd);
		wayLocation[34+i]=ccp(center+stepEnd-3,center+stepEnd+i*stepLength);
		wayLocation[42+i]=ccp(center-stepEnd,2*center-margin-i*stepLength);
		wayLocation[48+i]=ccp(center-stepEnd-i*stepLength,center+stepEnd);
	}
	wayLocation[13]=ccp(center,margin);
	wayLocation[27]=ccp(2*center-margin,center);
	wayLocation[41]=ccp(center,2*center-margin);
	wayLocation[55]=ccp(margin,center);

	//vitri trong chuong
	wayLocation[56]=ccp(margin+stepLength*2,margin+stepLength*2);
	wayLocation[57]=ccp(margin+stepLength*3,margin+stepLength*2);
	wayLocation[58]=ccp(margin+stepLength*3,margin+stepLength*3);
	wayLocation[59]=ccp(margin+stepLength*2,margin+stepLength*3);
	//Finish location yellow,red,green,blue
	for(int i=0;i<6;i++)
	{
		finishLocation0[i]=ccp(margin+(i+1)*stepLength,center);
		finishLocation1[i]=ccp(center,margin+(i+1)*stepLength);
		finishLocation2[i]=ccp(2*center-margin-(i+1)*stepLength,center);
		finishLocation3[i]=ccp(center,2*center-margin-(i+1)*stepLength);
	}
	
	//init location
	initLocation[0]=	ccp((175-25)*scale,(175-25)*scale);
	initLocation[1]=	 ccp((175+25)*scale,(175-25)*scale);
	initLocation[2]=	 ccp((175+25)*scale,(175+25)*scale);
	initLocation[3]=	 ccp((175-25)*scale,(175+25)*scale);
	
	initLocation[4]=	 ccp((850-25)*scale,(175-25)*scale);
	initLocation[5]=	 ccp((850+25)*scale,(175-25)*scale);
	initLocation[6]=	 ccp((850+25)*scale,(175+25)*scale);
	initLocation[7]=	 ccp((850-25)*scale,(175+25)*scale);

	initLocation[8]=	 ccp((850-25)*scale,(850-25)*scale);
	initLocation[9]=	 ccp((850+25)*scale,(850-25)*scale);
	initLocation[10]=	 ccp((850+25)*scale,(850+25)*scale);
	initLocation[11]=	 ccp((850-25)*scale,(850+25)*scale);
	
	initLocation[12]=	 ccp((175-25)*scale,(850-25)*scale);
	initLocation[13]=	 ccp((175+25)*scale,(850-25)*scale);
	initLocation[14]=	 ccp((175+25)*scale,(850+25)*scale);
	initLocation[15]=	 ccp((175-25)*scale,(850+25)*scale);
	} else if (CURRENTMAP == NEWMAP) 
	{
		//1
	wayLocation[0]=ccp(37,278);
	wayLocation[1]=ccp(55,253);
	wayLocation[2]=ccp(85,245);
	wayLocation[3]=ccp(119,246);
	wayLocation[4]=ccp(155,246);
	wayLocation[5]=ccp(190,244);
	wayLocation[6]=ccp(225,230);
	wayLocation[7]=ccp(236,201);
	wayLocation[8]=ccp(235,166);
	wayLocation[9]=ccp(241,136);
	wayLocation[10]=ccp(241,101);
	wayLocation[11]=ccp(238,67);
	wayLocation[12]=ccp(267,48);
	wayLocation[13]=ccp(307,44);

	//2
	wayLocation[14]=ccp(344,45);
	wayLocation[15]=ccp(379,60);
	wayLocation[16]=ccp(389,89);
	wayLocation[17]=ccp(386,122);
	wayLocation[18]=ccp(374,158);
	wayLocation[19]=ccp(369,192);
	wayLocation[20]=ccp(388,224);
	wayLocation[21]=ccp(420,233);
	wayLocation[22]=ccp(449,219);
	wayLocation[23]=ccp(476,230);
	wayLocation[24]=ccp(511,235);
	wayLocation[25]=ccp(544,247);
	wayLocation[26]=ccp(559,272);
	wayLocation[27]=ccp(566,300);

	//3
	wayLocation[28]=ccp(557,333);
	wayLocation[29]=ccp(540,361);
	wayLocation[30]=ccp(510,369);
	wayLocation[31]=ccp(477,373);
	wayLocation[32]=ccp(444,381);
	wayLocation[33]=ccp(410,369);
	wayLocation[34]=ccp(375,372);
	wayLocation[35]=ccp(365,405);
	wayLocation[36]=ccp(370,447);
	wayLocation[37]=ccp(377,482);
	wayLocation[38]=ccp(377,518);
	wayLocation[39]=ccp(364,547);
	wayLocation[40]=ccp(336,567);
	wayLocation[41]=ccp(302,568);

	
	//3
	wayLocation[42]=ccp(264,564);
	wayLocation[43]=ccp(238,537);
	wayLocation[44]=ccp(228,508);
	wayLocation[45]=ccp(231,477);
	wayLocation[46]=ccp(241,442);
	wayLocation[47]=ccp(234,411);
	wayLocation[48]=ccp(221,385);
	wayLocation[49]=ccp(184,382);
	wayLocation[50]=ccp(149,386);
	wayLocation[51]=ccp(114,390);
	wayLocation[52]=ccp(78,386);
	wayLocation[53]=ccp(53,366);
	wayLocation[54]=ccp(38,342);
	wayLocation[55]=ccp(37,309);

	//vitri trong chuong
	wayLocation[56]=ccp(margin+stepLength*2,margin+stepLength*2);
	wayLocation[57]=ccp(margin+stepLength*3,margin+stepLength*2);
	wayLocation[58]=ccp(margin+stepLength*3,margin+stepLength*3);
	wayLocation[59]=ccp(margin+stepLength*2,margin+stepLength*3);
	//Finish location yellow,red,green,blue
	//0
	finishLocation0[0]=ccp(79,309);
	finishLocation0[1]=ccp(116,309);
	finishLocation0[2]=ccp(149,309);
	finishLocation0[3]=ccp(182,309);
	finishLocation0[4]=ccp(214,309);
	finishLocation0[5]=ccp(248,309);
	//1
	finishLocation1[0]=ccp(307,82);
	finishLocation1[1]=ccp(307,118);
	finishLocation1[2]=ccp(307,153);
	finishLocation1[3]=ccp(307,184);
	finishLocation1[4]=ccp(307,218);
	finishLocation1[5]=ccp(307,253);
	//2
	finishLocation2[0]=ccp(526,300);
	finishLocation2[1]=ccp(489,300);
	finishLocation2[2]=ccp(456,300);
	finishLocation2[3]=ccp(421,300);
	finishLocation2[4]=ccp(390,300);
	finishLocation2[5]=ccp(356,300);
	//3
	finishLocation3[0]=ccp(302,530);
	finishLocation3[1]=ccp(302,492);
	finishLocation3[2]=ccp(302,460);
	finishLocation3[3]=ccp(302,425);
	finishLocation3[4]=ccp(302,394);
	finishLocation3[5]=ccp(302,359);
	
	//init location
	initLocation[0]=	ccp((175-25)*scale,(175-25)*scale);
	initLocation[1]=	 ccp((175+25)*scale,(175-25)*scale);
	initLocation[2]=	 ccp((175+25)*scale,(175+25)*scale);
	initLocation[3]=	 ccp((175-25)*scale,(175+25)*scale);
	
	initLocation[4]=	 ccp((850-25)*scale,(175-25)*scale);
	initLocation[5]=	 ccp((850+25)*scale,(175-25)*scale);
	initLocation[6]=	 ccp((850+25)*scale,(175+25)*scale);
	initLocation[7]=	 ccp((850-25)*scale,(175+25)*scale);

	initLocation[8]=	 ccp((850-25)*scale,(850-25)*scale);
	initLocation[9]=	 ccp((850+25)*scale,(850-25)*scale);
	initLocation[10]=	 ccp((850+25)*scale,(850+25)*scale);
	initLocation[11]=	 ccp((850-25)*scale,(850+25)*scale);
	
	initLocation[12]=	 ccp((175-25)*scale,(850-25)*scale);
	initLocation[13]=	 ccp((175+25)*scale,(850-25)*scale);
	initLocation[14]=	 ccp((175+25)*scale,(850+25)*scale);
	initLocation[15]=	 ccp((175-25)*scale,(850+25)*scale);
	}
	//wayNext
	nextWay = CCPointArray::create(12);
	for(int i = 0; i <12; i++)
	{
		nextWay->addControlPoint(ccp(-1,-1));
	}
	nextWay->retain();
}

void MapLocation::resetNextWay()
{
	for(int i = 0; i <12; i++)
	{
		nextWay->replaceControlPoint(ccp(-1,-1),i);
	}
}
MapLocation::~MapLocation(void)
{
	for(int i = 0; i<56; i++)
	{
		wayLocation[i].autorelease();
	}
	for(int i = 0; i<6; i++)
	{
		finishLocation0[i].autorelease();
		finishLocation1[i].autorelease();
		finishLocation2[i].autorelease();
		finishLocation3[i].autorelease();
	}
	for(int i = 0; i < 16; i++)
	{
		initLocation[i].autorelease();
	}
	nextWay->autorelease();
}

CCPoint MapLocation::getFinishLocation(int teamNo,int index)
{
	//map = 0,1,2,3: finish
	switch(teamNo)
	{
	case 0:
		return finishLocation0[index];	
		break;
	case 1:
		if(index>=0&&index<=5)
			return finishLocation1[index];
		break;
	case 2:
		if(index>=0&&index<=5)
			return finishLocation2[index];
		break;
	case 3:
		if(index>=0&&index<=5)
			return finishLocation3[index];
		break;
	default:
		return ccp(-1,-1);
		break;
	}
	return ccp(-1,-1);
}

int MapLocation::getIndexLocation(CCPoint point)
{
	for(int i = 0; i < 56; i++)
	{
		if (wayLocation[i].equals(point)) return i;
	}
	return -1;
}

CCPoint MapLocation::getNextLocationInWay(int current,int step)
{
	if(current >=56) return ccp(-1,-1);
	if(step <=0 || step>12) return ccp(-1,-1);
	if((current+step)>55) return wayLocation[current+step+-56];
	else return wayLocation[current+step];
}
// getnextpoint return array
void MapLocation::getNextLocationsInWay(CCPoint current,int step)
{
	resetNextWay();
	int currentIndex = getIndexLocation(current);
	
	for(int i=0;i<step;i++)
	{
		CCPoint p = getNextLocationInWay(currentIndex,i+1);
		nextWay->replaceControlPoint(p, i);
	}
}
//get startPoint: Diem ra quan cau moi ben
CCPoint MapLocation::getStartLocation(int teamNo)
{
	if(teamNo <0 || teamNo >=4) return ccp(-1,-1);
	return wayLocation[teamNo*14];
}
//get Init Location
CCPoint MapLocation::getInitLocation(int teamNo,int teamUnit)
{	
	if(teamNo>=4||teamNo<0) return ccp(-1,-1);
	return initLocation[teamNo*4+teamUnit];
	
}

void MapLocation::drawWay() {
	CCSprite *sprite = CCSprite::create(Config::draw_way_image);
	for( int i = 0; i < 56; i ++) {
		CCSprite *new_sprite = CCSprite::createWithTexture(sprite->getTexture());
		new_sprite->setPosition(wayLocation[i]);
		new_sprite->setScale(0.2f);
		parent->addChild(new_sprite,1);
	}
}