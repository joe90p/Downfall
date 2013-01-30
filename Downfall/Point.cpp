#include <Mathematics.h>

Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}

int Point::GetX()
{
	return this->x;
}

int Point::GetY()
{
	return this->y;
}

Point* Point::Add( Point* other ) 
{
   return new Point( x + other->GetX(), y + other->GetY() );
}

Point* Point::Minus( Point* other ) 
{
   return new Point( x - other->GetX(), y - other->GetY() );
}