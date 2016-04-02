# Joystick_Lib
Import Joystick Function
+ [Email Address](kyechan99@naver.com) : kyechan99@naver.com
+ [WebSite](blog.naver.com/kyechan99) : http://blog.naver.com/kyechan99



-

## Cocos2d-X ver.
File Explain  : http://blog.naver.com/kyechan99/220492857669

조이스틱 생성 (필수로 적어야 할것들)
```
 Joystick* joystick = Joystick::create();
 joystick->setMainChar();	// 조이스틱으로 이동할 스프라이트를 적습니다.
 this->addChild(joystick);
```

추가 함수 (안쓰셔도 될것들)
```
 joystick->setSpeed(0.1f);	// 이동될 스프라이트의 속도 (기본 : 0.1f)
 joystick->setLimitScreen(true);// 이동을 화면사이즈에 제한을 걸지 유무
```

씬에 적어주셔야 할것들(HelloWorldScene.cpp)
```
Update()
{
	joystick->update();
}

onTouchBegan(Touch* touch, Event* unused_event)
{
	joystick->onTouchBegan(touch,unused_event);
}
onTouchmoved(Touch* touch, Event* unused_event)
{
	joystick->ontouchMoved(touch,unused_event);
}
onTouchEnded(Touch* touch, Event* unused_event)
{
	joystick->onTouchEnded(touch,unused_event);
}
```


-

## Unity ver.
File Explain  : preparing...

스크립트 추가 후
Inspector에서 해당 오브젝트들을 옮겨 주면 실행






-




