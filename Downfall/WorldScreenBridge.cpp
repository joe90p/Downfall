#include <Physics.h>

WorldScreenBridge::WorldScreenBridge(b2World* world, TwoDCoordinateSystemConverter* coOrdConverter, int screenWidth)
{
	this->world = world;
	this->coOrdConverter = coOrdConverter;
	this->width = this->GetWorldDimensions(new Point(screenWidth, 0))->GetX();
}


b2World* WorldScreenBridge::GetWorld()
{
	return this->world;
}
Point* WorldScreenBridge::GetScreenCoOrd(PointFloat* worldCoOrd)
{
	PointFloat* screenCoOrdFloat = this->coOrdConverter->ConvertSecondaryToPrimary(worldCoOrd);
	int x = Maths::RoundToNearestInt(screenCoOrdFloat->GetX());
	int y = Maths::RoundToNearestInt(screenCoOrdFloat->GetY());
	return new Point(x,y);
}
Point* WorldScreenBridge::GetScreenDimensions(PointFloat* worldDimensions)
{
	PointFloat* intermediate =  this->coOrdConverter->AbsConvertSecondaryToPrimary(worldDimensions);
	
	int x = intermediate->GetX();
	int y = intermediate->GetY();
	
	return new Point(x,y);
}


PointFloat* WorldScreenBridge::GetWorldCoOrd(Point* screenCoOrd)
{
	PointFloat* screenCoOrdFloat = new PointFloat(screenCoOrd->GetX(), screenCoOrd->GetY());
	return this->coOrdConverter->ConvertPrimaryToSecondary(screenCoOrdFloat);
}

PointFloat* WorldScreenBridge::GetWorldDimensions(Point* screenDimensions)
{
	return this->coOrdConverter->AbsConvertPrimaryToSecondary(new PointFloat((float)screenDimensions->GetX(), (float)screenDimensions->GetY()));
}


void WorldScreenBridge::SetGroundBody()
{
	b2BodyDef bodyDef;
	b2PolygonShape dynamicBox;
	b2FixtureDef fixtureDef;
	b2Body* body;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(this->width/2, - this->width/20);
	body = this->world->CreateBody(&bodyDef);
	
	
	dynamicBox.SetAsBox(this->width/2, this->width/20);	
	
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;	
	fixtureDef.restitution = 0.4f;
	
	body->CreateFixture(&fixtureDef);
	
	this->groundBody = body;
}

b2Body* WorldScreenBridge::GetGroundBody()
{
	if(this->groundBody)
	{
		this->SetGroundBody();
	}
	return this->groundBody;
}


