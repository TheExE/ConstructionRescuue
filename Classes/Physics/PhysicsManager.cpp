#include "PhysicsManager.h"
#include "HelloWorldScene.h"
#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Dynamics/b2Body.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "3rdParty/Box2dDebugDraw/B2DebugDrawLayer.h"

using namespace cocos2d;

PhysicsManager::PhysicsManager()
{
	m_UniqueId = 0;
}

PhysicsManager::~PhysicsManager()
{
	// Release memory for the world
	delete m_pPhysicsWorld;
	m_pPhysicsWorld = nullptr;
}

PhysicsManager* PhysicsManager::getInstance()
{
	static PhysicsManager instance;
	return &instance;
}

bool PhysicsManager::init()
{
	m_pPhysicsWorld = new b2World(GRAVITY);
	m_pPhysicsWorld->SetContactListener(this); // Listen for contact events

	return m_pPhysicsWorld != nullptr;
}

void PhysicsManager::update()
{
	// Instruct the world to perform a single step of simulation. It is
	// generally best to keep the time step and iterations fixed.
	m_pPhysicsWorld->Step(PHYSICS_TIME_STEP, VELOCITY_ITERATION, POSITION_ITERATION);

	// Iterate over the bodies in the physics world
	for (b2Body* body = m_pPhysicsWorld->GetBodyList(); body; body = body->GetNext())
	{
		if (body->GetUserData() != nullptr)
		{
			/*
			 * Synchronize the sprite position
			 * and rotation with the corresponding physics body
			*/
			Sprite* bodySprite = (Sprite*)body->GetUserData();
			bodySprite->setPosition(Vec2(body->GetPosition().x * PTM_RATIO,
				body->GetPosition().y * PTM_RATIO));
			bodySprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(body->GetAngle()));
		}
	}
}

/*
* Add box colider using sprite size.
*/
void PhysicsManager::addBoxColider(extension::PhysicsSprite* pSprite, PhysicsBodyType bodyType,
	float density)
{
	addCustomBoxCollider(pSprite, pSprite->getContentSize(), bodyType, density);
}

/*
 * Add box colider with custom size.
*/
void PhysicsManager::addCustomBoxCollider(extension::PhysicsSprite* pSprite, Size size,
	PhysicsBodyType bodyType, float mass)
{
	// Create body def
	b2BodyDef bodyDef;
	bodyDef.type = convertToBox2dBodyType(bodyType);
	bodyDef.userData = pSprite;	// Link sprite to rigidBody
	b2Body* rigidBody = m_pPhysicsWorld->CreateBody(&bodyDef);
	pSprite->setB2Body(rigidBody);
	pSprite->setPTMRatio(PTM_RATIO);

	// Create fixture defination
	float boxVolume = size.width*size.height*size.width; /* Assume that length of
															the box is same as width*/
	float density = mass / boxVolume;
	b2Fixture* bodyFixture = createBodyFixture(*rigidBody, size,
		density);

}

b2Fixture* PhysicsManager::createBodyFixture(b2Body& rigidBody,
	const Size& size, const float& density) const
{
	b2FixtureDef fixtureDef;
	b2PolygonShape shape;
	shape.SetAsBox((size.width / PTM_RATIO)*0.5f, (size.height / PTM_RATIO)*0.5f);
	fixtureDef.shape = &shape;
	fixtureDef.density = density;
	fixtureDef.friction = DEFAULT_FRICTION;
	fixtureDef.restitution = DEFAULT_RESTITUTION;

	return rigidBody.CreateFixture(&fixtureDef);
}

/*
 * Add body name for which to listen for
 * contact event.
 */
void PhysicsManager::addContactListener(const char* bodyName,
	ContactCallback onContactBegin)
{
	m_ContactListeners.push_back(PhysicsContactListener(bodyName, onContactBegin));
}

b2BodyType PhysicsManager::convertToBox2dBodyType(PhysicsBodyType type)
{
	b2BodyType realType;
	switch (type)
	{
	case DYNAMIC:
		realType = b2_dynamicBody;
		break;
	case KINEMATIC:
		realType = b2_kinematicBody;
		break;
	case STATIC:
		realType = b2_staticBody;
		break;
	}

	return realType;
}

void PhysicsManager::castRay(b2RayCastCallback* callback,
	const Vec2& first, const Vec2& second)
{
	if (m_pPhysicsWorld != nullptr)
	{
		b2Vec2 pointOne = b2Vec2(first.x/PTM_RATIO, first.y/PTM_RATIO);
		b2Vec2 pointTwo = b2Vec2(second.x/PTM_RATIO, second.y/PTM_RATIO);
		m_pPhysicsWorld->RayCast(callback, pointOne, pointTwo);
	}
	else
	{
		cocos2d::log("PhysicsManager: [castRay] PhysicsWorld is null !");
	}
}

/*
* Box2d callback for when
* contact between body fixtures starts.
*/
void PhysicsManager::BeginContact(b2Contact* contact)
{
	using namespace extension;

	b2Fixture* pFixtureA = contact->GetFixtureA();
	b2Fixture* pFixtureB = contact->GetFixtureB();

	PhysicsSprite* pSpriteA = (PhysicsSprite*)pFixtureA->GetUserData();
	PhysicsSprite* pSpriteB = (PhysicsSprite*)pFixtureB->GetUserData();

	if (pSpriteA != nullptr && pSpriteB != nullptr)
	{
		const char* bodyAName = pSpriteA->getName().c_str();
		const char* bodyBName = pSpriteB->getName().c_str();

		// If contact contains some of the listener names then inform the listeners
		for (int i = 0; i < (int)m_ContactListeners.size(); i++)
		{
			PhysicsContactListener& currentListener = m_ContactListeners[i];
			if (strcmp(bodyAName, currentListener.name) == 0)
			{
				currentListener.onContactCallback(PhysicsContactInformation(pFixtureA,
					pFixtureB));
			}
			else if (strcmp(bodyBName, currentListener.name) == 0)
			{
				currentListener.onContactCallback(PhysicsContactInformation(pFixtureB,
					pFixtureA));
			}
		}
	}
}

/*
 * Box2d callback for when
 * contact between body fixtures ends.
 */
void PhysicsManager::EndContact(b2Contact* contact)
{

}

/*
 * For this to work sprite visibility needs to be set to false.
 */
void PhysicsManager::enableDebugDraw(Node* rootNode)
{
	rootNode->addChild(B2DebugDrawLayer::create(m_pPhysicsWorld, PTM_RATIO), 999);
}