#include <Physics.h>

MouseJointManager::MouseJointManager(WorldScreenBridge* worldScreenBridge) : mouseJoint(0), mouseJointB(0)
{
	this->worldScreenBridge = worldScreenBridge;
}
void MouseJointManager::SetMouseJoint(b2Body* body, PointFloat* target)
{
	if(!this->mouseJoint)
	{
		b2MouseJointDef* mousejointDefinition = new b2MouseJointDef();
		mousejointDefinition->bodyA = this->worldScreenBridge->GetGroundBody();
		mousejointDefinition->bodyB = body;
		
		mousejointDefinition->target.Set(target->GetX(), target->GetY());
		mousejointDefinition->collideConnected = true;
		mousejointDefinition->maxForce = 300.0f * body->GetMass();
		this->mouseJoint = static_cast<b2MouseJoint*>(this->worldScreenBridge->GetWorld()->CreateJoint(mousejointDefinition));
		body->SetAwake(true);
	}
	else
	{
		this->mouseJoint->SetTarget(b2Vec2(target->GetX(), target->GetY()));
	}
}
void MouseJointManager::SetMouseJointB(b2Body* body, PointFloat* target)
{
	if(!this->mouseJointB)
	{
		b2MouseJointDef* mousejointDefinition = new b2MouseJointDef();
		mousejointDefinition->bodyA = this->worldScreenBridge->GetGroundBody();
		mousejointDefinition->bodyB = body;
		
		mousejointDefinition->target.Set(target->GetX(), target->GetY());
		mousejointDefinition->collideConnected = true;
		mousejointDefinition->maxForce = 300.0f * body->GetMass();
		this->mouseJointB = static_cast<b2MouseJoint*>(this->worldScreenBridge->GetWorld()->CreateJoint(mousejointDefinition));
		body->SetAwake(true);
	}
	else
	{
		this->mouseJointB->SetTarget(b2Vec2(target->GetX(), target->GetY()));
	}

}
void MouseJointManager::DestroyMouseJoint()
{
	if(this->mouseJoint)
	{
		this->worldScreenBridge->GetWorld()->DestroyJoint(this->mouseJoint);
		this->mouseJoint = NULL;
	}
	if(this->mouseJointB)
	{
		this->worldScreenBridge->GetWorld()->DestroyJoint(this->mouseJointB);
		this->mouseJointB = NULL;
	}
}
