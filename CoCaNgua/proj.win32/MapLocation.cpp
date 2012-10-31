#include "MapLocation.h"

MapLocation::MapLocation(int _winSize)
{
	winSize = _winSize;
	scale = winSize/1024;
	//scale = 1;
	margin = 45*scale;
	center = 512*scale;
	stepEnd = 117*scale;
	stepLength = (350/6)*scale;

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


