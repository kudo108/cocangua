
#include "cocos2d.h"
#include "MenuScene.h"

class RuleScene :  public cocos2d::CCScene
{
public:
	virtual bool init();
	CREATE_FUNC(RuleScene);
private:
	void menuCallBack(CCObject* sender);
};

