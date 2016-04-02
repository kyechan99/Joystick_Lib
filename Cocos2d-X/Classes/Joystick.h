/*********************************************************************
* Date : 2015.09.30
* Name : 조이스틱 (멀티터치)
* Email : kyechan99@naver.com
* Description : http://blog.naver.com/kyechan99/220492857669
* 오픈 소스 입니다. 더 나은 소스 개발하면 공유해주세요.
***********************************************************************/
#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class Joystick : public Layer
{
private:
	Sprite* joystick_limit;		// 조이스틱 - 제한된 공간 저장 
	Sprite* joystick_control;	// 조이스틱 - 움직일 컨트롤러 저장
	Sprite* mainChar;			// 조이스틱 - 컨트롤할 스프라이트

private:
	Vec2 controlerPos;			// 조이스틱 - 컨트롤러의 위치 값 저장
	Vec2 centerPos;				// 조이스틱 - 가운데 기중점의 위치 값 저장

private:
	bool isTouch;				// 올바른 위치에서 터치하였는지 유무
	float m_speed;				// 움직일 속도
	bool isLimmitWinSize;		// 윈사이즈에 제한을 걸것인지 유무
	Size winSize;

public:
	Joystick(){};
	~Joystick(){};

	virtual bool init();

	// 조이스틱 위치, 주인공 위치, 리미트 설정
	void update();

	// 조이스틱 - 주인공 설정
	void setMainChar(Sprite* mainChar);

	// 조이스틱 - 스피드 설정
	void setSpeed(float speed);

	// 스프라이트 화면 이동 제한 받기
	void setLimitScreen(bool check);

	// 윈도우 사이즈에 이동을 제한 할것이지에 대한 유무
	bool checkLimit();

	// 터치
	bool onTouchBegan(Touch* touch, Event* unused_event);
	void onTouchMoved(Touch* touch, Event* unused_event);
	void onTouchEnded(Touch* touch, Event* unused_event);

	CREATE_FUNC(Joystick);
};
