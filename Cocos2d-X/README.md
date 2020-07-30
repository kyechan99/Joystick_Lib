# Cocos2d-X ver.
[KR](https://kyechan99.github.io/tech/2017/03/18/Joystick-Lib-Cocos2dX.html)

### Create Joystick
```cpp
 Joystick* joystick = Joystick::create();
 joystick->setMainChar(spr);	                  // param : move Object
 this->addChild(joystick);
```

### Edition
```cpp
 joystick->setSpeed(0.1f);	      	// Moving speed (default : 0.1f);
 joystick->setLimitScreen(true);  	// Limit screen size (default : false);
 joystick->setTouchShow(true);		// Show Joystick on Touch Position
```

### Touch
```cpp
void HelloWorld::onTouchesBegan(const std::vector &touches, Event* unused_event)    
{    
   for (auto it : touches)        
   {        
      joystick->onTouchBegan(it, unused_event);            
   }        
}
   
void HelloWorld::onTouchesMoved(const std::vector &touches, Event* unused_event)
{
   for (auto it : touches)
   {
      joystick->onTouchMoved(it, unused_event);
   }
}

void HelloWorld::onTouchesEnded(const std::vector &touches, Event* unused_event)
{
   for (auto it : touches)
   {
      joystick->onTouchEnded(it, unused_event);
   } 
}
```

### Update
```cpp
void HelloWorld::Update(float dt)    
{    
   joystick->update();        
}
```

### Header
```cpp
class HelloWorld : public Layer    
{    
private:    
   Joystick* joystick;     
```