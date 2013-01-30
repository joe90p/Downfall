#include <Controls.h>

Dial::Dial(B2BodyCircularScreenSection* bodyCircularSection, char* imageLocation, int initialAngleInDegrees) : Control(bodyCircularSection->GetCentre()->GetX() - bodyCircularSection->GetRadius(), bodyCircularSection->GetCentre()->GetY() - bodyCircularSection->GetRadius())
{
	this->Setup(bodyCircularSection->GetCentre()->GetX(), bodyCircularSection->GetCentre()->GetY(), bodyCircularSection->GetRadius(), imageLocation, initialAngleInDegrees);
	this->SetB2Body(bodyCircularSection->GetB2Body());
}

void Dial::Setup(int centreX, int centreY, int radius, char* imageLocation, int initialAngleInDegrees)
{
	this->initialAngleInDegrees = initialAngleInDegrees;
	this->SetClientArea(new Circle(radius));
	this->SetVisuals(new VisualItem());
	this->GetVisuals()->SetTopLeft(new Point(centreX - radius, centreY - radius));
	this->mainSprite = new Sprite(); //TODO: get rid of the mainSprite thing
	this->mainSprite->SetTopLeft(new Point(0,0));
	this->mainSprite->SetImageLocation(imageLocation);
	this->GetVisuals()->Add(this->mainSprite);	
	this->radius = radius;
	this->GetVisuals()->SetCentreOfRotationRelativeToTopLeft(new Point(radius, radius));
}


int Dial::GetRadius()
{
	Circle* area = static_cast<Circle*>(this->GetClientArea());
	return area->GetRadius();
}

void Dial::SetImage(char* imageLocation)
{
	this->imageLocation = imageLocation;
}

b2Body* Dial::GetB2Body()
{
	return this->b2dBody;
}
void Dial::SetB2Body(b2Body* body)
{
	this->b2dBody = body;
}
void Dial::SetPhysicalTopLeft(Point* topLeft)
{
	int x;
	int y;
	Point* newTopLeft;
	x = topLeft->GetX() - this->radius;
	y = topLeft->GetY() - this->radius;
	newTopLeft = new Point(x, y);
	this->GetVisuals()->SetTopLeft(newTopLeft);
}

IVisualItem* Dial::GetGravityObjectVisuals()
{
	return GetVisuals();
}

void Dial::DrawGravityObject(int angleInDegrees)
{
	this->GetVisuals()->SetAngle(angleInDegrees + this->initialAngleInDegrees);
	this->GetVisuals()->Draw();
}