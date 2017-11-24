#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Nodes/Crane/Crane.h"
#include "Physics/PhysicsManager.h"
#include "Nodes/Brick/Brick.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();    
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void update(float deltaTime) override;	

private:
	Crane* m_pCrane;
	Brick* m_pBrick;	
	cocos2d::Sprite* m_pUIDriveLeft;
	cocos2d::Sprite* m_pUIDriveRight;
	cocos2d::Sprite* m_pUICraneMoveUp;
	cocos2d::Sprite* m_pUICraneMoveDown;
	cocos2d::EventListenerMouse* m_pMouseListener;

	void onMouseUp(cocos2d::Event* plainEvent);
	void onMouseDown(cocos2d::Event* plainEvent);
};

#endif // __HELLOWORLD_SCENE_H__
