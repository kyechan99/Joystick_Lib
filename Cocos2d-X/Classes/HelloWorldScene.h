/*********************************************************************
* Date : 2016.04.03
* Name : Joystick (Cocos2d-X ver 3.X)
* Email : kyechan99@naver.com
* GitHub : https://github.com/kyechan99/Joystick_Lib
* Description : http://blog.naver.com/kyechan99/220492857669
* This is Open Source, plz sharing if u know better way

* Modified List
* Date : 2016.04.26
* Name : Joystick (Cocos2d-X ver 3.X)
* Email : mark4215@naver.com
* GitHub : https://github.com/haminjun/Joystick_Lib
* By registering listeners to replace the touch inner class
* Registration / release a scheduler inside
***********************************************************************/
#pragma once

#include "cocos2d.h"
using namespace cocos2d;
#include "Joystick.h"

class HelloWorld : public Layer
{
private:
	Sprite* spr;
	Joystick* joystick;

public:
	static Scene* createScene();

	virtual bool init();
	CREATE_FUNC(HelloWorld);
};
