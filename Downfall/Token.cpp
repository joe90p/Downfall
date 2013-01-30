#include <Controls.h>

Token::Token(int topLeftX, int topLeftY)
{
	Sprite* s = new Sprite();
	SetTopLeft(new Point(topLeftX, topLeftY));
	s->SetTopLeft(new Point (0, 0));
	s->SetImageLocation("images/token.png");
	Add(s);
	this->height = 30;
	this->width = 30;
	this->SetCentreOfRotationRelativeToTopLeft(new Point(this->width/2, this->height/2));
}


b2Body* Token::GetB2Body()
{
	return this->b2dBody;
}
void Token::SetB2Body(b2Body* body)
{
	this->b2dBody = body;
}
void Token::SetPhysicalTopLeft(Point* topLeft)
{
	int x;
	int y;
	Point* newTopLeft;
	x = topLeft->GetX() - this->width/2;
	y = topLeft->GetY() - this->height/2;
	newTopLeft = new Point(x, y);
	SetTopLeft(newTopLeft);
}

IVisualItem* Token::GetGravityObjectVisuals()
{
	return this;
}

void Token::DrawGravityObject(int angleInDegrees)
{
	this->SetAngle(angleInDegrees);
	this->Draw();
}