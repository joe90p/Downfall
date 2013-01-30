#include <Mathematics.h>


int Maths::RoundToNearestInt(double value)
{
	return floor(value + 0.5);
}

int Maths::RoundToNearestInt(float value)
{
	return floorf(value + 0.5f);
}

float Maths::GetAbsoluteValue(float value)
{
	if(value < 0)
	{
		value= value * -1;
	}
	return value;
}