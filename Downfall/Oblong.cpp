#include <Shapes.h>

Oblong::Oblong(int width, int height)
{
	//set values
	this->width = width;
	this->height = height;
}

//Determines if the (x,y) point is within the boundary of the oblong
bool Oblong::IsInside(int x, int y, int topLeftX, int topLeftY)
{
	return
	(x > topLeftX) && 
	(x < topLeftX + this->width) &&
	(y > topLeftY) && 
	(y < topLeftY + this->height);
}