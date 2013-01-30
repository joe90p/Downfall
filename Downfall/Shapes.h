#ifndef Shapes
#define Shapes

#include <DarkDraw.h>
#include <math.h>


//The interfce for a drawable 2D shape
class IShape
{
public:
	virtual bool IsInside(int x, int y, int topLeftX, int topLeftY) = 0;
};


class Oblong : public IShape
{
private:
	int width;
	int height;
public:
	Oblong(int width, int height);
	virtual bool IsInside(int x, int y, int topLeftX, int topLeftY);
};

class Circle : public IShape
{
private:
	int radius;
public:
	Circle(int radius);
	virtual bool IsInside(int x, int y, int topLeftX, int topLeftY);
	int GetRadius();
};


#endif /* Shapes */