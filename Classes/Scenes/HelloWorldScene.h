#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Crane\Crane.h"
#include "Physics\PhysicsManager.h"
#include "Brick\Brick.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();    
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void update(float deltaTime) override;
	void addListenerWithSceneGraphPriority(cocos2d::EventListener* listener, cocos2d::Node* listeningNode);

private:
	Crane* m_Crane;
	PhysicsManager* m_PhysicsManager;
	Brick* m_Brick;
	cocos2d::Sprite* m_UIDriveLeft;
	cocos2d::Sprite* m_UIDriveRight;
	cocos2d::Sprite* m_UICraneMoveUp;
	cocos2d::Sprite* m_UICraneMoveDown;
	cocos2d::EventListenerMouse* m_MouseListener;


	void onMouseUp(cocos2d::Event* plainEvent);
	void onMouseDown(cocos2d::Event* plainEvent);
};

#endif // __HELLOWORLD_SCENE_H__
