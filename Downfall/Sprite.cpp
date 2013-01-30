#include <DarkDraw.h>

Sprite::Sprite() : imageLocation(0), id(-1), parent(0), angleInDegrees(0)
{
	this->centreOfRotationRelativeToTopLeft = new Point(0,0);
}

void Sprite::Delete()
{
	GraphicsDB::GetInstance()->DeleteSprite(this);
}

int Sprite::GetID()
{
	return this->id;
}

void Sprite::Draw()
{
	DrawAtAbosoluteScreenCoOrd(GetAbsoluteScreenPosition());
}

void Sprite::DrawAtAbosoluteScreenCoOrd(Point* p)
{
	if(this->angleInDegrees != 0)
	{
		Point* centre = new Point(this->centreOfRotationRelativeToTopLeft->GetX() + p->GetX(), this->centreOfRotationRelativeToTopLeft->GetY() + p->GetY());
		GraphicsDB::GetInstance()->DrawSprite(this, *centre, this->angleInDegrees, *p);
	}
	else
	{
		GraphicsDB::GetInstance()->DrawSprite(this, p->GetX() , p->GetY());
	}
}

Point* Sprite::GetAbsoluteScreenPosition()
{
	return GetAbsoluteScreenPosition(this->topLeft);
}

//TODO: put this general method in a more appropriate place
Point* Sprite::GetAbsoluteScreenPosition(Point* point)
{
	int x = 0;
	int y = 0;
	IVisualItem* child = this;
	IVisualItem* parent = this->GetParent();
	x = point->GetX();
	y = point->GetY();
	Point* result = new Point(x,y);
	while(parent!=0)
	{
		x = result->GetX() + parent->GetTopLeft()->GetX();
		y = result->GetY() + parent->GetTopLeft()->GetY();
		result = new Point(x,y);
		child = parent;
		parent = child->GetParent();
	}
	return result;
}

void Sprite::SetID(int value)
{
	this->id = value;
}

void Sprite::SetTopLeft(Point* topLeft)
{
	this->topLeft = topLeft;
}

void Sprite::Add(IVisualItem*)
{
	//TODO: Do nothing. seems a bit rubbish e have to implement the Add method.
}

char* Sprite::GetImageLocation()
{
	return this->imageLocation;
}

void Sprite::SetImageLocation(char* value)
{
	this->imageLocation = value;
}


Point* Sprite::GetTopLeft()
{
	return this->topLeft;
}

void Sprite::SetParent(IVisualItem* parent)
{
	this->parent = parent;
}

IVisualItem* Sprite::GetParent()
{
	return this->parent;
}


void Sprite::SetAngle(int angleInDegrees)
{
	this->angleInDegrees = angleInDegrees;
}

void Sprite::SetCentreOfRotationRelativeToTopLeft(Point* centreOfRotation)
{
	this->centreOfRotationRelativeToTopLeft = centreOfRotation;
}

Point* Sprite::GetCentreOfRotationRelativeToTopLeft()
{
	return this->centreOfRotationRelativeToTopLeft;
}