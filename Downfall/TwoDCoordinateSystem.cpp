#include <Mathematics.h>


TwoDCoordinateSystem::TwoDCoordinateSystem(CoordinateSystemOriginPosition originPosition, float xMaximum, float yMaximum)
{
	this->SetXandYDirections(originPosition);
	this->maximumX = xMaximum;
	this->maximumY = yMaximum;
}

bool TwoDCoordinateSystem::GetIsXDirectionLeftToRight()
{
	return this->isXDirectionLeftToRight;
}

bool TwoDCoordinateSystem::GetIsYDirectionBottomToTop()
{
	return this->isYDirectionBottomToTop;
}

float TwoDCoordinateSystem::GetMaximumX()
{
	return this->maximumX;
}

float TwoDCoordinateSystem::GetMaximumY()
{
	return this->maximumY;
}

void TwoDCoordinateSystem::SetXandYDirections(CoordinateSystemOriginPosition originPosition)
{
	switch(originPosition)
	{
		case TopLeft:
			this->isYDirectionBottomToTop = false;
			this->isXDirectionLeftToRight = true;
			break; 
		case TopRight:
			this->isYDirectionBottomToTop = false;
			this->isXDirectionLeftToRight = false;
			break; 
		case BottomLeft:
			this->isYDirectionBottomToTop = true;
			this->isXDirectionLeftToRight = true;
			break; 
		case BottomRight:
			this->isYDirectionBottomToTop = true;
			this->isXDirectionLeftToRight = false;
			break; 
	}
}