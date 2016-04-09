# Cocos2d-X ver.
File Explain  : http://blog.naver.com/kyechan99/220492857669

### Create Joystick
```
 Joystick* joystick = Joystick::create();
 joystick->setMainChar(spr);	                  // param : move Object
 this->addChild(joystick);
```

### Edition
```
 joystick->setSpeed(0.1f);	      	// moving speed (standard : 0.1f);
 joystick->setLimitScreen(true);  	// limit screen size (standard : false);
 joystick->setTouchShow(true);		// Show Joystick on Touch Position
```

### Write (HelloWorldScene.cpp)
```
::Update()
{
	joystick->update();
}

::onTouchBegan(Touch* touch, Event* unused_event)   // or onTouchesBegan
{
	joystick->onTouchBegan(touch,unused_event);
}
::onTouchMoved(Touch* touch, Event* unused_event)   // or onTouchesMoved
{
	joystick->ontouchMoved(touch,unused_event);
}
::onTouchEnded(Touch* touch, Event* unused_event)   // or onTouchesEnded
{
	joystick->onTouchEnded(touch,unused_event);
}
```



