#pragma once

#include "cocos2d.h"
#include "Box2D/Common/b2Math.h"
#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Dynamics/b2Body.h"
#include "extensions/physics-nodes/CCPhysicsSprite.h"

struct PhysicsContactInformation;
typedef std::function<bool(PhysicsContactInformation& contact)> ContactCallback;
struct PhysicsContactListener
{
	const char* name;
	ContactCallback onContactCallback;

	PhysicsContactListener(const char* name, ContactCallback onContactCallback)
	{
		this->name = name;
		this->onContactCallback = onContactCallback;
	}
};
struct PhysicsContactInformation
{
	b2Fixture* pListenerFixture;
	b2Fixture* pTheOtherFixture;
	
	PhysicsContactInformation(b2Fixture* pListenerFixt,
		b2Fixture* pTheOtherFixt)
	{
		this->pListenerFixture = pListenerFixt;
		this->pTheOtherFixture = pTheOtherFixt;		
	}
};
enum PhysicsBodyType
{
	DYNAMIC,
	KINEMATIC,
	STATIC
};

class PhysicsManager: private b2ContactListener
{
public:
	static PhysicsManager* getInstance();		
	~PhysicsManager();

	bool init();	
	void addBoxColider(cocos2d::extension::PhysicsSprite* pSprite, PhysicsBodyType bodyType, float mass);
	void addCustomBoxCollider(cocos2d::extension::PhysicsSprite* pSprite, cocos2d::Size size,
		PhysicsBodyType bodyType, float mass);
	void addContactListener(const char* bodyName, ContactCallback onContactBegin);	
	void castRay(b2RayCastCallback* callback,
		const cocos2d::Vec2& first, const cocos2d::Vec2& second);
	void update();
	void enableDebugDraw(cocos2d::Node* rootNode);

private:	
	PhysicsManager();	
	b2BodyType convertToBox2dBodyType(PhysicsBodyType type);
	b2Fixture* createBodyFixture(b2Body& rigidBody,
		const cocos2d::Size& size, const float& density) const;

	virtual void BeginContact(b2Contact* contact) override;
	virtual void EndContact(b2Contact* contact) override;

private:	
	const b2Vec2 GRAVITY = b2Vec2(0, -9.8f);
	const float DEFAULT_FRICTION = 0.4f;
	const float DEFAULT_RESTITUTION = 0.1f;
	const float PHYSICS_TIME_STEP = 1.0f / 60.0f;
	const float VELOCITY_ITERATION = 5;
	const float POSITION_ITERATION = 1;
	const float PTM_RATIO = 32;
	
	unsigned int m_UniqueId;
	std::vector<PhysicsContactListener> m_ContactListeners;		
	b2World* m_pPhysicsWorld;
};