#include "cocos2d.h"

class GameWinScene : public cocos2d::CCScene
{
public:
	bool init();
	CREATE_FUNC(GameWinScene);
private:
	void menuCallback(CCObject* sender);
};

