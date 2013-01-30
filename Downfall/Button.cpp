#include <Controls.h>

//TODO: get rid of imagelocation parameter
Button::Button(int topLeftX, int topLeftY, int width, int height, char* imageLocation): Control(topLeftX, topLeftY),  imageLocation(0), hoverImageLocation(0)
{
	this->SetClientArea(new Oblong(width, height));
	//TODO: The code to set the visuals is repeated in GravityBox and Dial. Do something.
	this->SetVisuals(new VisualItem());
	this->GetVisuals()->SetTopLeft(new Point(topLeftX, topLeftY));
	this->mainSprite = new Sprite(); //TODO: get rid of the mainSprite thing
	this->mainSprite->SetTopLeft(new Point(0,0));
	this->mainSprite->SetImageLocation(imageLocation);
	this->GetVisuals()->Add(this->mainSprite);
	this->MouseEnter = boost::bind( &Button::OnMouseEnter, this);
	this->MouseLeave = boost::bind( &Button::OnMouseLeave, this);
}
void Button::OnMouseEnter()
{
	this->mainSprite->SetImageLocation(this->hoverImageLocation);
	this->GetVisuals()->Draw();
}

void Button::OnMouseLeave()
{
	this->mainSprite->SetImageLocation(this->imageLocation);
	this->GetVisuals()->Draw();
}

void Button::SetImage(char* imageLocation)
{
	this->imageLocation = imageLocation;
}

void Button::SetHoverImage(char* hoverImageLocation)
{
	this->hoverImageLocation = hoverImageLocation;
}

