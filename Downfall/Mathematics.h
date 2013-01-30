#ifndef Mathematics
#define Mathematics

#include <math.h>


enum CoordinateSystemOriginPosition { TopLeft, BottomLeft, BottomRight, TopRight };

class Point 
{
private:
	int x;
	int y;
public:
	Point(int x, int y);
	int GetX();
	int GetY();
	Point* Add(Point*);
	Point* Minus(Point*);
};

class PointFloat
{
private:
	float x;
	float y;
public:
	PointFloat(float x, float y);
	float GetX();
	float GetY();
	PointFloat* Add(PointFloat*);
	PointFloat* Minus(PointFloat*);
	float GetAngleBetween(PointFloat*);
};


class Maths
{
public:
	static int RoundToNearestInt(double value);
	static int RoundToNearestInt(float value);
	static float GetAbsoluteValue(float value);
};


class TwoDCoordinateSystem
{
public:
	TwoDCoordinateSystem(CoordinateSystemOriginPosition originPosition, float xMaximum, float yMaximum);
	bool GetIsXDirectionLeftToRight();
	bool GetIsYDirectionBottomToTop();
	float GetMaximumX();
	float GetMaximumY();
private:
	bool isXDirectionLeftToRight;
	bool isYDirectionBottomToTop;
	float maximumX;
	float maximumY;
	void SetXandYDirections(CoordinateSystemOriginPosition originPosition);
};


class TwoDCoordinateSystemConverter
{
public:
	TwoDCoordinateSystemConverter(TwoDCoordinateSystem* primaryCoordinateSystem, TwoDCoordinateSystem* secondaryCoordinateSystem);
	PointFloat* ConvertPrimaryToSecondary(PointFloat* pointOnPrimary);
	PointFloat* ConvertSecondaryToPrimary(PointFloat* pointOnSecondary);
	PointFloat* AbsConvertSecondaryToPrimary(PointFloat* pointOnSecondary);
	PointFloat* AbsConvertPrimaryToSecondary(PointFloat* pointOnPrimary);
	static PointFloat* ConvertAToB(PointFloat* pointOnA, TwoDCoordinateSystem* aSystem, TwoDCoordinateSystem* bSystem);
private:
	TwoDCoordinateSystem* primaryCoordinateSystem;
	TwoDCoordinateSystem* secondaryCoordinateSystem;
	static float SameDirectionConversion(float convertFrom, float convertFromMax, float convertToMax);
	static float OppositeDirectionConversion(float convertFrom, float convertFromMax, float convertToMax);
};

#endif /* Mathematics */