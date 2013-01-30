#include <Mathematics.h>


TwoDCoordinateSystemConverter::TwoDCoordinateSystemConverter( TwoDCoordinateSystem* primaryCoordinateSystem, TwoDCoordinateSystem* secondaryCoordinateSystem)
{
	this->primaryCoordinateSystem = primaryCoordinateSystem;
	this->secondaryCoordinateSystem = secondaryCoordinateSystem;
}

PointFloat* TwoDCoordinateSystemConverter::ConvertPrimaryToSecondary(PointFloat* pointOnPrimary)
{
	return TwoDCoordinateSystemConverter::ConvertAToB(pointOnPrimary, this->primaryCoordinateSystem, this->secondaryCoordinateSystem);
}
PointFloat* TwoDCoordinateSystemConverter::ConvertSecondaryToPrimary(PointFloat* pointOnSecondary)
{
	return TwoDCoordinateSystemConverter::ConvertAToB(pointOnSecondary, this->secondaryCoordinateSystem, this->primaryCoordinateSystem);
}

PointFloat* TwoDCoordinateSystemConverter::ConvertAToB(PointFloat* pointOnA, TwoDCoordinateSystem* aSystem, TwoDCoordinateSystem* bSystem)
{
	float x;
	float y;
	if(aSystem->GetIsXDirectionLeftToRight() == bSystem->GetIsXDirectionLeftToRight() )
	{
		x = TwoDCoordinateSystemConverter::SameDirectionConversion(pointOnA->GetX() ,aSystem->GetMaximumX(), bSystem->GetMaximumX());
	}
	else
	{
		x = TwoDCoordinateSystemConverter::OppositeDirectionConversion(pointOnA->GetX() ,aSystem->GetMaximumX(), bSystem->GetMaximumX());
	}
	
	if(aSystem->GetIsYDirectionBottomToTop() == bSystem->GetIsYDirectionBottomToTop() )
	{
		y = TwoDCoordinateSystemConverter::SameDirectionConversion(pointOnA->GetY() ,aSystem->GetMaximumY(), bSystem->GetMaximumY());
	}
	else
	{
		y = TwoDCoordinateSystemConverter::OppositeDirectionConversion(pointOnA->GetY() ,aSystem->GetMaximumY(), bSystem->GetMaximumY());
	}
	
	return new PointFloat(x,y);
}

float TwoDCoordinateSystemConverter::SameDirectionConversion(float convertFrom, float convertFromMax, float convertToMax)
{
	return (convertFrom/convertFromMax) * convertToMax;
}

float TwoDCoordinateSystemConverter::OppositeDirectionConversion(float convertFrom, float convertFromMax, float convertToMax)
{
	return ((-convertFrom/convertFromMax) * convertToMax) + convertToMax;
}

PointFloat* TwoDCoordinateSystemConverter::AbsConvertPrimaryToSecondary(PointFloat* pointOnPrimary)
{
	float x;
	float y;
	x = TwoDCoordinateSystemConverter::SameDirectionConversion(pointOnPrimary->GetX() ,this->primaryCoordinateSystem->GetMaximumX(), this->secondaryCoordinateSystem->GetMaximumX());
	y = TwoDCoordinateSystemConverter::SameDirectionConversion(pointOnPrimary->GetY() ,this->primaryCoordinateSystem->GetMaximumY(), this->secondaryCoordinateSystem->GetMaximumY());
	
	return new PointFloat(x,y);
}

PointFloat* TwoDCoordinateSystemConverter::AbsConvertSecondaryToPrimary(PointFloat* pointOnSecondary)
{
	float x;
	float y;
	x = TwoDCoordinateSystemConverter::SameDirectionConversion(pointOnSecondary->GetX() ,this->secondaryCoordinateSystem->GetMaximumX(), this->primaryCoordinateSystem->GetMaximumX());
	y = TwoDCoordinateSystemConverter::SameDirectionConversion(pointOnSecondary->GetY() ,this->secondaryCoordinateSystem->GetMaximumY(), this->primaryCoordinateSystem->GetMaximumY());
	
	return new PointFloat(x,y);
}
	
	