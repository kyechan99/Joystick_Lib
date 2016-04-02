/*********************************************************************
* Date : 2016.04.03
* Name : Joystick (Cocos2d-X)
* Email : kyechan99@naver.com
* Description : http://blog.naver.com/kyechan99/220492857669
* This is Open Source, plz sharing if u know better way
***********************************************************************/
#include "Joystick.h"

// 원형값 계산
bool isTouchCircle(Point pos, Point center, float radius)
{
	float dx = (pos.x - center.x);
	float dy = (pos.y - center.y);
	return (radius >= sqrt((dx*dx) + (dy*dy)));
}

bool Joystick::init()
{
	if (!Layer::init())
		return false;

	winSize = Director::getInstance()->getWinSize();

	// 터치하고 있는 지 유무
	isTouch = false;

	// 움직일 스피드 (변경하려면 setSpeed()함수 사용)
	m_speed = 0.1f;

	// 윈도우 사이즈에 이동을 제한 할것이지에 대한 유무
	isLimmitWinSize = false;

	// 조이스틱 - 가운데 기준점
	centerPos = Vec2(125, 125);


	// 조이스틱 - 제한 되어 있는 공간
	joystick_limit = Sprite::create("joystick_limit_circle.png");
	joystick_limit->setPosition(centerPos);
	this->addChild(joystick_limit);


	// 조이스틱 - 움직일 공간
	joystick_control = Sprite::create("joystick_control_circle.png");
	joystick_control->setPosition(centerPos);
	this->addChild(joystick_control);


	// 조이스틱 - 컨트롤러의 포지션
	controlerPos = centerPos;

	return true;
}

// 조이스틱 위치, 주인공 위치, 리미트 설정
void Joystick::update()
{
	// 조이스틱 - 포지션 값을 계속 업데이트 해줌
	joystick_control->setPosition(controlerPos);

	// 터치 도중일때만 움직임
	if (isTouch)
	{
		// 움직일 거리 구하기
		float moveX = controlerPos.x - centerPos.x;
		float moveY = controlerPos.y - centerPos.y;

		Vec2 charPos = mainChar->getPosition();


		if (checkLimit())
		{
			if (0 < charPos.x + moveX * m_speed && charPos.x + moveX * m_speed < winSize.width)
			{
				charPos.x += moveX * m_speed;
			}
			if (0 < charPos.y + moveY * m_speed && charPos.y + moveY * m_speed < winSize.height)
			{
				charPos.y += moveY * m_speed;
			}
			mainChar->setPosition(charPos);
		}
		else
		{
			charPos.x += moveX * m_speed;
			charPos.y += moveY * m_speed;
			mainChar->setPosition(charPos);
		}
	}
}

// 조이스틱 - 스피드 설정
void Joystick::setSpeed(float speed)
{
	m_speed = speed;
}

// 조이스틱 - 주인공 설정
void Joystick::setMainChar(Sprite* mainChar)
{
	this->mainChar = mainChar;
}

// 스프라이트 화면 이동 제한 받기
void Joystick::setLimitScreen(bool check)
{
	isLimmitWinSize = check;
}

// 윈도우 사이즈에 이동을 제한 할것이지에 대한 유무
bool Joystick::checkLimit()
{
	return isLimmitWinSize;
}


bool Joystick::onTouchBegan(Touch* touch, Event* unused_event)
{
	// 조이스틱 - 리미트 공간안에서 시작을 하였다면
	if (isTouchCircle(touch->getLocation(), centerPos, joystick_limit->getContentSize().width / 2))
	{
		isTouch = true;

		controlerPos = touch->getLocation();

		return isTouch;
	}
	return isTouch;
}

void Joystick::onTouchMoved(Touch* touch, Event* unused_event)
{
	if (isTouch)
	{
		float limitSize = joystick_limit->getContentSize().width / 2;	// 제한 범위의 반지름
		
		// 터치가 리미트 범위를 넘었을 시에 컨트롤러가 끝부분에 남아있게 하기 위함
		if (!(isTouchCircle(touch->getLocation(), centerPos, limitSize)))
		{
			Point touchPos = touch->getLocation();	// 터치 위치값

			float dX = touchPos.x - centerPos.x;
			float dY = touchPos.y - centerPos.y;

			float distance = sqrt(dX*dX + dY*dY);	// 대각선 길이 구하기
			float angle = atan2(dY, dX);			// 각도 구하기

			if (distance > limitSize)
			{
				dX = cos(angle) * limitSize;
				dY = sin(angle) * limitSize;
				
				touchPos.x = centerPos.x + dX;
				touchPos.y = centerPos.y + dY;
			}

			controlerPos = Vec2(touchPos);

		}
		else
		{
			controlerPos = touch->getLocation();
		}

	}
}

void Joystick::onTouchEnded(Touch* touch, Event* unused_event)
{
	if (isTouch)
	{
		// 터치가 끝나면 조이스틱은 원래 위치로 돌아감
		controlerPos = centerPos;
	}
	isTouch = false;
}
