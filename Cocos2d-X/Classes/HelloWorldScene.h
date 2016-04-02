/*********************************************************************
* Date : 2015.09.30
* Name : 조이스틱 (멀티터치)
* Email : kyechan99@naver.com
* Description : http://blog.naver.com/kyechan99/220492857669
* 오픈 소스 입니다. 더 나은 소스 개발하면 공유해주세요.
***********************************************************************/
#pragma once

#include "Joystick.h"
#include "cocos2d.h"
using namespace cocos2d;

class HelloWorld : public Layer
{
private:
	Sprite* spr;
	Joystick* joystick;

public:
	static Scene* createScene();

	virtual bool init();

	void Update(float dt);

	void onTouchesBegan(const std::vector<Touch*> &touches, Event* unused_event);
	void onTouchesMoved(const std::vector<Touch*> &touches, Event* unused_event);
	void onTouchesEnded(const std::vector<Touch*> &touches, Event* unused_event);

	CREATE_FUNC(HelloWorld);
};