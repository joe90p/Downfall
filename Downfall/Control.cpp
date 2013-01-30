#include <Controls.h>
#include <DarkGDK.h>
Control::Control(int topLeftX, int topLeftY) : Clicked(0), mouseIn(false), mouseUp(true), pressed(false), clicked(false), parent(0), inPress(false)
{
	this->topLeft = new Point(topLeftX, topLeftY);
}
void Control::SetMouseIn()
{
	Point* position = this->GetAbsoluteScreenPosition();
	this->mouseIn = this->clientArea->IsInside(dbMouseX(), dbMouseY(), position->GetX(), position->GetY());
}

void Control::SetMouseUp()
{
	this->mouseUp = dbMouseClick()!=1;
}

void Control::SetPressed(bool oldMouseUp)
{
	if(this->pressed)
	{
		this->pressed = !this->mouseUp;
	}
	else
	{
		this->pressed = this->mouseIn && oldMouseUp && !this->mouseUp;
	}
	
}

void Control::SetClicked(bool oldPressed)
{
	this->clicked = this->mouseIn && !this->pressed && oldPressed;
}

//When an event (e.g Click) occurs this method calls functions, via function pointers, that are assigned
//as event handlers
void Control::Update() 
{
	bool oldMouseIn = this->mouseIn;
	bool oldMouseUp = this->mouseUp;
	bool oldPressed = this->pressed;
	SetMouseIn();
	SetMouseUp();
	SetPressed(oldMouseUp);
	SetClicked(oldPressed);
	
	//check for mouse enetering/leaving
	if(oldMouseIn !=this->mouseIn && !this->clicked)
	{
		if(this->mouseIn && MouseEnter)
		{
			MouseEnter();
		}
		else
		{
			if(MouseLeave)
			{
				MouseLeave();
			}
		}
	}
	//check for pressed
	if(this->pressed && Pressed)
	{
		inPress = true;
		Pressed();
	}
	//check for click
	if(this->clicked && Clicked)
	{
		Clicked();
	}
	if(this->mouseUp)
	{
		if(oldMouseUp != this->mouseUp)
		{
			if(MouseUp)
			{
				MouseUp();
			}
			if(inPress && OutOfPress)
			{
				OutOfPress();
				inPress=false;
			}
		}
	}
	
	//loop through all child controls and update
	list<Control*>::iterator i;
	for(i = this->controls.begin(); i != this->controls.end(); i++) 
	{
		(*i)->Update();
	}
}
Point* Control::GetTopLeft() 
{
	return topLeft;
}
IVisualItem* Control::GetVisuals()
{
	return this->visuals;
}

void Control::Add(Control* c)
{
	this->controls.push_back(c);
	c->SetParent(this);
	this->visuals->Add(c->GetVisuals());
}
Control* Control::GetParent()
{
	return this->parent;
}

Point* Control::GetAbsoluteScreenPosition()
{
	int x = 0;
	int y = 0;
	Control* child = this;
	Control* parent = this->GetParent();
	x = this->topLeft->GetX();
	y = this->topLeft->GetY();
	Point* result = new Point(x,y);
	while(parent!=0)
	{
		x = result->GetX() + parent->GetTopLeft()->GetX();
		y = result->GetY() + parent->GetTopLeft()->GetY();
		result = new Point(x,y);
		child = parent;
		parent = child->GetParent();
	}
	return result;
}
void Control::SetParent(Control* parent)
{
	this->parent = parent;
}

void Control::SetVisuals(IVisualItem* visualItem)
{
	this->visuals = visualItem;
}

void Control::SetClientArea(IShape* clientArea)
{
	this->clientArea = clientArea;
}

IShape* Control::GetClientArea()
{
	return this->clientArea;
}