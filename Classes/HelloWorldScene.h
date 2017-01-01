#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Crane\Crane.h"
#include "Physics\PhysicsManager.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void update(float deltaTime) override;
	void addListenerWithSceneGraphPriority(cocos2d::EventListener* listener, cocos2d::Node* listeningNode);

private:
	Crane* m_Crane;
	PhysicsManager* m_PhysicsManager;
	cocos2d::Sprite* m_UIDriveLeft;
	cocos2d::Sprite* m_UIDriveRight;
	cocos2d::Sprite* m_UICraneLiftUp;
	cocos2d::Sprite* m_UICraneLiftDown;
	cocos2d::EventListenerMouse* m_MouseListener;


	void onMouseUp(cocos2d::Event* plainEvent);
	void onMouseDown(cocos2d::Event* plainEvent);
};

#endif // __HELLOWORLD_SCENE_H__
