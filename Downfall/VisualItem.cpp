#include <DarkDraw.h>

VisualItem::VisualItem() : parent(0)
{

}
void VisualItem::Draw()
{
	list<IVisualItem*>::iterator i;
	for(i=this->children.begin(); i != this->children.end(); i++) 
	{
		(*i)->Draw();
	}
}

void VisualItem::SetParent(IVisualItem* parent)
{
	this->parent = parent;
}

IVisualItem* VisualItem::GetParent()
{
	return this->parent;
}

void VisualItem::Add(IVisualItem* item)
{
	item->SetParent(this);
	this->children.push_back(item);
}

void VisualItem::Delete()
{
	list<IVisualItem*>::iterator i;
	for(i=this->children.begin(); i != this->children.end(); i++) 
	{
		(*i)->Delete();
	}
}

void VisualItem::SetAngle(int angleInDegrees)
{
	list<IVisualItem*>::iterator i;
	for(i=this->children.begin(); i != this->children.end(); i++) 
	{
		(*i)->SetAngle(angleInDegrees);
	}
}

void VisualItem::SetTopLeft(Point* topLeft)
{
	this->topLeft = topLeft;
}

Point* VisualItem::GetTopLeft()
{
	return this->topLeft;
}

Point* VisualItem::GetAbsoluteScreenPosition()
{
	//TODO: Not  implemented. Does it need to be?
	return new Point(0,0);
}

void VisualItem::SetCentreOfRotationRelativeToTopLeft(Point* centreOfRotation)
{
	this->centreOfRotationRelativeToTopLeft = centreOfRotation;
	list<IVisualItem*>::iterator i;
	for(i=this->children.begin(); i != this->children.end(); i++) 
	{
		Point* centreOfRotationRelativeToChild = this->centreOfRotationRelativeToTopLeft->Minus((*i)->GetTopLeft());
		(*i)->SetCentreOfRotationRelativeToTopLeft(centreOfRotationRelativeToChild);
	}
}
Point* VisualItem::GetCentreOfRotationRelativeToTopLeft()
{
	return this->centreOfRotationRelativeToTopLeft;
}