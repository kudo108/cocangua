
#include "MapLocation.h"
#include "cocos2d.h"

using namespace cocos2d;

MapLocation::MapLocation(int _winSize)
{
	//waylocation[0] la vi tri xuat phat cua quan co mau vang 
	//
	way = 0;
	fnY = 1;
	fnG = 2;
	fnR = 3;
	fnB = 4;
	//
	winSize = _winSize;
	scale = winSize/1024;
	margin = 45*scale;
	center = 512*scale;
	stepEnd = 117*scale;
	stepLength = (350/6)*this->scale;
	for(int i=0;i<=6;i++){
		wayLocation[i]= ccp(margin+i*stepLength,center-stepEnd);
		wayLocation[6+i]=ccp(center-stepEnd,(center-stepEnd)-i*stepLength);
		wayLocation[14+i]=ccp(center+stepEnd,margin+i*stepLength);
		wayLocation[20+i]=ccp(center+stepEnd+i*stepLength,center-stepEnd);
		wayLocation[28+i]=ccp(2*center-margin-i*stepLength,center+stepEnd);
		wayLocation[34+i]=ccp(center+stepLength,center+stepEnd+i*stepLength);
		wayLocation[42+i]=ccp(center-stepEnd,2*center-margin-i*stepLength);
		wayLocation[48+i]=ccp(center-stepEnd-i*stepLength,center+stepEnd);
	}
	wayLocation[13]=ccp(center,margin);
	wayLocation[27]=ccp(2*center-margin,center);
	wayLocation[41]=ccp(center,2*center-margin);
	wayLocation[55]=ccp(margin,center);
	//Finish location yellow,red,green,blue
	for(int i=0;i<6;i++)
	{
		finishLocationYellow[i]=ccp(margin+(i+1)*stepLength,center);
		finishLocationGreen[i]=ccp(center,margin+(i+1)*stepLength);
		finishLocationRed[i]=ccp(2*center-margin-(i+1)*stepLength,center);
		finishLocationBlue[i]=ccp(center,2*center-margin-(i+1)*stepLength);
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
		finishLocationYellow[i].autorelease();
		finishLocationBlue[i].autorelease();
		finishLocationGreen[i].autorelease();
		finishLocationRed[i].autorelease();
	}

}

CCPoint MapLocation::getPoint(int map,int index)
{
	switch(map)
	{
	case 0:
		if(index>=0&&index<=55)
			return this->wayLocation[index]; else return ccp(-1,-1);
		break;
	case 1:
		if(index>=0&&index<=5)
			return this->finishLocationYellow[index]; else return ccp(-1,-1);
		break;
	case 2:
		if(index>=0&&index<=5)
			return this->finishLocationGreen[index]; else return ccp(-1,-1);
		break;
	case 3:
		if(index>=0&&index<=5)
			return this->finishLocationRed[index]; else return ccp(-1,-1);
		break;
	case 4:
		if(index>=0&&index<=5)
			return this->finishLocationBlue[index]; else return ccp(-1,-1);
		break;
	default:
		return ccp(-1,-1);
		break;
	}
}
int MapLocation::getIndexLocation(int map,CCPoint point)
{
	
	switch(map)
	{
	case 0:
		for(int i=0;i<56;i++) if(wayLocation[i].equals(point)) return i;
		return -1;
		break;
	case 1:
		for(int i=0;i<6;i++) if(finishLocationYellow[i].equals(point)) return i;
		return -1;
		break;
	case 2:
		for(int i=0;i<6;i++) if(finishLocationGreen[i].equals(point)) return i;
		return -1;
		break;
	case 3:
		for(int i=0;i<6;i++) if(finishLocationRed[i].equals(point)) return i;
		return -1;
		break;
	case 4:
		for(int i=0;i<6;i++) if(finishLocationBlue[i].equals(point)) return i;
		return -1;
		break;
	default: 
			
			return -1;
		break;
	}	
}

CCPoint MapLocation::getNextPoint(int type,CCPoint current,int step)
{
	int i=0,j=0;
	switch(type)
	{
	case 1:
		if(step<=0) return current;
		i = getIndexLocation(way,current);
		if(i==-1){
			j = getIndexLocation(fnY,current);
			if(j==-1) return ccp(-1,-1);
			if((step+j)>5) return ccp(-1,-1);
			return finishLocationYellow[step+j];
		}
		if((i+step)>55) return finishLocationYellow[i+step-56];
		return wayLocation[i+step];
		break;
	case 2:
		//13
		if(step<=0) return current;
		i = getIndexLocation(way,current);
		if(i==-1){
			j = getIndexLocation(fnG,current);
			if(j==-1) return ccp(-1,-1);
			if((step+j)>5) return ccp(-1,-1);
			return finishLocationGreen[step+j];
		}
		if((i+step)>13&&i>=0&&i<=13) return finishLocationGreen[i+step-14];
		if((i+step)>13&&i>=0&&i<=13&&(step+i-13)>5) return ccp(-1,-1);
		if((i+step)>55) return wayLocation[i+step-56];
		return wayLocation[i+step];
		break;
	case 3:
		//27
		if(step<=0) return current;
		i = getIndexLocation(way,current);
		if(i==-1){
			j = getIndexLocation(fnR,current);
			if(j==-1) return ccp(-1,-1);
			if((step+j)>5) return ccp(-1,-1);
			return finishLocationRed[step+j];
		}
		if((i+step)>27&&i>=0&&i<=27) return finishLocationRed[i+step-28];
		if((i+step)>27&&i>=0&&i<=27&&(i+step-27)>5) return ccp(-1,-1);
		if((i+step)>55) return wayLocation[i+step-56];
		return wayLocation[i+step];
		break;
	case 4:
		if(step<=0) return current;
		i = getIndexLocation(way,current);
		if(i==-1){
			j = getIndexLocation(fnB,current);
			if(j==-1) return ccp(-1,-1);
			if((step+j)>5) return ccp(-1,-1);
			return finishLocationBlue[step+j];
		}
		if((i+step)>41&&i>=0&&i<=41) return finishLocationRed[i+step-42];
		if((i+step)>41&&i>=0&&i<=41&&(i+step-41)>5) return ccp(-1,-1);
		if((i+step)>55) return wayLocation[i+step-56];
		return wayLocation[i+step];
		break;
	default:
		return ccp(-1,-1);break;
	}
}
