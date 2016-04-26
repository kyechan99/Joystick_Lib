/*********************************************************************
* Date : 2016.04.03
* Name : Joystick (Cocos2d-X ver 3.X)
* Email : kyechan99@naver.com
* GitHub : https://github.com/kyechan99/Joystick_Lib
* Description : http://blog.naver.com/kyechan99/220492857669
* This is Open Source, plz sharing if u know better way
***********************************************************************/
#include "Joystick.h"

// 원형값 계산
bool Joystick::isTouchCircle(Point pos, Point center, float radius)
{
	float dx = (pos.x - center.x);
	float dy = (pos.y - center.y);
	return (radius >= sqrt((dx*dx) + (dy*dy)));
}

Joystick::~Joystick()
{
	cocos2d::Director::getInstance()->getScheduler()->unschedule("JoyStickUpdate", this);
}

bool Joystick::init()
{
	if (!Layer::init())
		return false;


	_winSize = Director::getInstance()->getWinSize();

	_isTouch = false;

	// speed
	_speed = 0.1;

	// touch show
	_isTouchShow = false;

	// limit win size
	_isLimmitWinSize = false;

	// Joystick - Standard Position
	centerPos = Vec2(125, 125);

	// Joystick - Back Sprite (Limit)
	joystick_limit = Sprite::create("joystick_limit_circle.png");
	joystick_limit->setPosition(centerPos);
	this->addChild(joystick_limit);


	// Joystick - Front Sprite (Controler)
	joystick_control = Sprite::create("joystick_control_circle.png");
	joystick_control->setPosition(centerPos);
	this->addChild(joystick_control);

	// Joystick - Controler Position
	controlerPos = centerPos;

	// Touch Enabled
	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ALL_AT_ONCE);

	// setSchedule Update
	cocos2d::Director::getInstance()->getScheduler()->schedule(
		std::bind(&Joystick::update, this, std::placeholders::_1),
		this, 1 / 60.f, false, "JoyStickUpdate");

	return true;
}

void Joystick::update(float dt)
{
	// 조이스틱 - 포지션 값을 계속 업데이트 해줌
	joystick_control->setPosition(controlerPos);

	// 터치 도중일때만 움직임
	if (_isTouch)
	{
		// 움직일 거리 구하기
		float moveX = controlerPos.x - centerPos.x;
		float moveY = controlerPos.y - centerPos.y;

		Vec2 charPos = mainChar->getPosition();

		if (checkLimit())
		{
			if (0 < charPos.x + moveX * _speed && charPos.x + moveX * _speed < _winSize.width)
			{
				charPos.x += moveX * _speed;
			}
			if (0 < charPos.y + moveY * _speed && charPos.y + moveY * _speed < _winSize.height)
			{
				charPos.y += moveY * _speed;
			}
			mainChar->setPosition(charPos);
		}
		else
		{
			charPos.x += moveX * _speed;
			charPos.y += moveY * _speed;
			mainChar->setPosition(charPos);
		}
	}
}

void Joystick::setSpeed(float speed)
{
	_speed = speed;
}

void Joystick::setMainChar(Sprite* mainChar)
{
	this->mainChar = mainChar;
}

void Joystick::setTouchShow(bool check)
{
	_isTouchShow = check;

	if (_isTouchShow)
		this->setVisible(false);
}

void Joystick::setLimitScreen(bool check)
{
	_isLimmitWinSize = check;
}

bool Joystick::checkLimit()
{
	return _isLimmitWinSize;
}

void Joystick::onTouchesBegan(const std::vector<Touch*> &touches, Event* unused_event)
{
	for (auto it : touches)
	{
		Touch* touch = it;
		if (_isTouchShow)
		{
			centerPos = touch->getLocation();
			joystick_limit->setPosition(centerPos);
			joystick_control->setPosition(centerPos);
			this->setVisible(true);
		}

		// 조이스틱 - 리미트 공간안에서 시작을 하였다면
		if (isTouchCircle(touch->getLocation(), centerPos, joystick_limit->getContentSize().width / 4))
		{
			_isTouch = true;

			controlerPos = touch->getLocation();
		}
	}
}

void Joystick::onTouchesMoved(const std::vector<Touch*> &touches, Event* unused_event)
{
	for (auto it : touches)
	{
		Touch* touch = it;
		if (_isTouch)
		{
			float limitSize = joystick_limit->getContentSize().width / 4;	// 제한 범위의 반지름

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
}

void Joystick::onTouchesEnded(const std::vector<Touch*> &touches, Event* unused_event)
{
	for (auto it : touches)
	{
		if (_isTouch)
		{
			// 터치가 끝나면 조이스틱은 원래 위치로 돌아감
			controlerPos = centerPos;
		}
		_isTouch = false;

		if (_isTouchShow)
			this->setVisible(false);
	}
}