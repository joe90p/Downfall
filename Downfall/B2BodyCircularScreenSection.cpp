#include <Physics.h>
#include <DarkDraw.h>

B2BodyCircularScreenSection::B2BodyCircularScreenSection(b2Body* body, float radius, WorldScreenBridge* worldScreenBridge)
{
	this->worldScreenBridge = worldScreenBridge;
	this->body = body;
	this->worldRadius = radius;
}


b2Body* B2BodyCircularScreenSection::GetB2Body()
{
	return this->body;
}
Point* B2BodyCircularScreenSection::GetCentre()
{
	return this->worldScreenBridge->GetScreenCoOrd(new PointFloat(body->GetWorldCenter().x, body->GetWorldCenter().y));
}
int B2BodyCircularScreenSection::GetRadius()
{
	Point* temp1 = this->worldScreenBridge->GetScreenDimensions(
													new PointFloat(
																	this->worldRadius, 
																	0.0
																	)
													);
													
	return temp1->GetX();
}