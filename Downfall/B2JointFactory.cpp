#include <physics.h>

B2JointFactory::B2JointFactory(WorldScreenBridge* worldScreenBridge)
{
	this->worldScreenBridge = worldScreenBridge;
}

b2Joint* B2JointFactory::CreateRevoluteDialJoint(b2Body* dial, float dialRadius, PointFloat* centreOfJoint)
{
	b2RevoluteJointDef* jointDef;
	b2Vec2* centre = new b2Vec2(centreOfJoint->GetX(), centreOfJoint->GetY());
	jointDef = new b2RevoluteJointDef();
	//Note, that in the initialization function the static body must be the first parameter
	jointDef->Initialize(this->worldScreenBridge->GetGroundBody(), dial, *centre); 
	jointDef->maxMotorTorque = 1000 * dialRadius;
	jointDef->enableMotor = true;
	return this->worldScreenBridge->GetWorld()->CreateJoint(jointDef);
}

b2Joint* B2JointFactory::CreateGearJoint(b2Body* body1, b2Body* body2, b2Joint* joint1, b2Joint* joint2, float ratio)
{
	b2GearJointDef* jointDefx = new b2GearJointDef();
	jointDefx->bodyA = body1;
	jointDefx->bodyB = body2;
	jointDefx->joint1 = joint1;
	jointDefx->joint2 = joint2;
	jointDefx->ratio = ratio;
	return this->worldScreenBridge->GetWorld()->CreateJoint(jointDefx);
}