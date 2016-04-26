/*********************************************************************
* Date : 2016.04.03
* Name : Joystick (Cocos2d-X ver 3.X)
* Email : kyechan99@naver.com
* GitHub : https://github.com/kyechan99/Joystick_Lib
* Description : http://blog.naver.com/kyechan99/220492857669
* This is Open Source, plz sharing if u know better way
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


	joystick = Joystick::create();
	joystick->setMainChar(spr);
	joystick->setSpeed(0.1f);
	joystick->setLimitScreen(true);
	joystick->setTouchShow(true);
	this->addChild(joystick);

	return true;
}