#include <Shapes.h>


Circle::Circle(int radius)
{
	this->radius = radius;
}

//Determines if the (x,y) point is within the boundary of the circle
bool Circle::IsInside(int x, int y, int topLeftX, int topLeftY)
{
	double newX = (double)x - (double)(topLeftX + this->radius);
	double newY = (double)y - (double)(topLeftY + this->radius);
	
	bool test =  sqrt((newX * newX) + (newY * newY)) < (double)this->radius;
	
	if(test)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

int Circle::GetRadius()
{
	return this->radius;
}