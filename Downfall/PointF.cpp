#include <Mathematics.h>

PointFloat::PointFloat(float x, float y)
{
	this->x = x;
	this->y = y;
}

float PointFloat::GetX()
{
	return this->x;
}

float PointFloat::GetY()
{
	return this->y;
}

PointFloat* PointFloat::Add(PointFloat* other ) 
{
   return new PointFloat( this->x + other->GetX(), this->y + other->GetY() );
}

PointFloat* PointFloat::Minus(PointFloat* other ) 
{
   return new PointFloat( this->x - other->GetX(), this->y - other->GetY() );
}

float PointFloat::GetAngleBetween(PointFloat * other)
{
   	float xDiff = other->GetX() - this->x;
	float yDiff = other->GetY() - this->y;
	float angle = atanf(Maths::GetAbsoluteValue(yDiff)/Maths::GetAbsoluteValue(xDiff));
	float halfPiFactor = 0.0;
	
	if(xDiff < 0 && yDiff > 0)
	{
		angle = 3.14 - angle;
	}
	if(xDiff < 0 && yDiff < 0)
	{
		angle = 3.14 + angle;
	}
	if(xDiff > 0 && yDiff < 0)
	{
		angle = 6.28 - angle;
	}
	
	return angle;
}