/*********************************************************************
* Date : 2015.09.30
* Name : 조이스틱 (멀티터치)
* Email : kyechan99@naver.com
* Description : http://blog.naver.com/kyechan99/220492857669
* 오픈 소스 입니다. 더 나은 소스 개발하면 공유해주세요.
***********************************************************************/
#include "HelloWorldScene.h"

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}

bool HelloWorld::init()
{
	if (!Layer::init())
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();



	spr = Sprite::create("cid_icon4.png");
	spr->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(spr);


	// 조이스틱
	joystick = Joystick::create();	// 조이스틱 생성
	joystick->setMainChar(spr);		// 조이스틱으로 조종할 스프라이트 설정
	joystick->setSpeed(0.1f);		// 조이스틱으로 움직일 스피드 설정
	joystick->setLimitScreen(true);	// 스프라이트 움직임을 화면에 제한걸으려면 true, 아니라면 false 또는 안써도 됨
	this->addChild(joystick);



	// 터치
	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ALL_AT_ONCE);


	schedule(schedule_selector(HelloWorld::Update), 0.0f);

	return true;
}

void HelloWorld::Update(float dt)
{
	joystick->update();
}

void HelloWorld::onTouchesBegan(const std::vector<Touch*> &touches, Event* unused_event)
{
	for (auto it : touches)
	{
		joystick->onTouchBegan(it, unused_event);
	}

}

void HelloWorld::onTouchesMoved(const std::vector<Touch*> &touches, Event* unused_event)
{
	for (auto it : touches)
	{
		joystick->onTouchMoved(it, unused_event);
	}

}

void HelloWorld::onTouchesEnded(const std::vector<Touch*> &touches, Event* unused_event)
{
	for (auto it : touches)
	{
		joystick->onTouchEnded(it, unused_event);
	}

}
