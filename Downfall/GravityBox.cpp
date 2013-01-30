#include <Controls.h>
GravityBox::GravityBox(Point* topLeft, float acceleration, int width, int height) : Control(topLeft->GetX(), topLeft->GetY())
{
	this->width = width;
	this->height = height;	
	this->SetClientArea(new Oblong(this->width, this->height));
	this->gravityAcceleration = acceleration;
	this->SetVisuals(new VisualItem());
	this->GetVisuals()->SetTopLeft(new Point(topLeft->GetX(), topLeft->GetY()));
	this->SetWorldScreenBridge();
	this->mouseJointManager = new MouseJointManager(this->worldScreenBridge);
}

	

void GravityBox::Update()
{
		list<IGravityObject*>::iterator i;
		this->worldScreenBridge->GetWorld()->Step(1.0f/60.0f, 3, 3);
		this->worldScreenBridge->GetWorld()->ClearForces();
		for(i=this->objects.begin(); i != this->objects.end(); i++) 
		{
			if((*i)->GetB2Body()->IsAwake())
			{
				b2Vec2 position = (*i)->GetB2Body()->GetPosition();
				float angle = (*i)->GetB2Body()->GetAngle();
				Point* p = this->worldScreenBridge->GetScreenCoOrd(new PointFloat(position.x, position.y));
				(*i)->SetPhysicalTopLeft(new Point(p->GetX(), p->GetY()));
				(*i)->DrawGravityObject(angle * (-180.0f/3.141f));
			}
		}
		
		Control::Update();
}
void GravityBox::SetMouseJoint(IGravityObject* object, int x, int y)
{
	Point* targetInScreenCoOrds = new Point(x,y);
	b2Body* body = object->GetB2Body();
	PointFloat* target = this->worldScreenBridge->GetWorldCoOrd(targetInScreenCoOrds->Minus(this->GetAbsoluteScreenPosition()));
	this->mouseJointManager->SetMouseJoint(body, target);
	
}

//void GravityBox::SetMouseJointB(IGravityObject* object, int x, int y)
//{
//	Point* targetInScreenCoOrds = new Point(x,y);
//	b2Body* body = object->GetB2Body();
//	PointFloat* target = this->worldScreenBridge->GetWorldCoOrd(targetInScreenCoOrds->Minus(this->GetAbsoluteScreenPosition()));
//	mouseJointManager->SetMouseJointB(body, target);
//	
//}
void GravityBox::AddObject(IGravityObject* object)
{
	this->objects.push_back(object);
	this->GetVisuals()->Add(object->GetGravityObjectVisuals());
}

void GravityBox::DestroyMouseJoint()
{
	this->mouseJointManager->DestroyMouseJoint();
}

void GravityBox::Draw()
{
	//TODO: do something here
}

b2World* GravityBox::GetB2World(TwoDCoordinateSystemConverter* converter)
{
	b2AABB worldAABB;
	PointFloat* dimensions = new PointFloat((float)width, (float)height);
	PointFloat* boxDimensions = converter->AbsConvertPrimaryToSecondary(dimensions);
	
	worldAABB.lowerBound.Set(0.0f, 0.0f);
	worldAABB.upperBound.Set(boxDimensions->GetX(), boxDimensions->GetY());

	// Define the gravity vector.
	b2Vec2 gravity(0.0f, this->gravityAcceleration);

	// Construct a world object, which will hold and simulate the rigid bodies.
	return new b2World(gravity, true);//
}


TwoDCoordinateSystemConverter* GravityBox::GetCoordConverter()
{
	float boxHeightInMeteres = 20.0;
	float conversionFactor = (float)this->height/this->width;
	TwoDCoordinateSystem* primaryCoordinateSystem = new TwoDCoordinateSystem(TopLeft, this->width, this->height);
	TwoDCoordinateSystem* secondaryCoordinateSystem = new TwoDCoordinateSystem(BottomLeft, boxHeightInMeteres / conversionFactor, boxHeightInMeteres);
	return new TwoDCoordinateSystemConverter(primaryCoordinateSystem, secondaryCoordinateSystem);
}
WorldScreenBridge* GravityBox::GetWorldScreenBridge()
{
	return this->worldScreenBridge;
}

void GravityBox::SetWorldScreenBridge()
{
	TwoDCoordinateSystemConverter* coordConverter = this->GetCoordConverter();
	b2World* world = this->GetB2World(coordConverter);
	this->worldScreenBridge = new WorldScreenBridge(world, coordConverter, this->width);
		
}