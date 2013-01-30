#ifndef DarkDraw
#define DarkDraw

#include "DarkGDK.h"
#include <list>
#include <unordered_map>
#include <Mathematics.h>
using namespace std;

struct eqstr
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) == 0;
  }
};

// the interface for objects in a VisualItem composition
class IVisualItem
{
public:
	virtual void Draw() = 0;
	virtual void Add(IVisualItem*) = 0;
	virtual void Delete() = 0;
	virtual void SetTopLeft(Point* topLeft) = 0;
	virtual Point* GetTopLeft() = 0;
	virtual IVisualItem* GetParent() = 0;
	virtual void SetParent(IVisualItem*) = 0;
	virtual Point* GetAbsoluteScreenPosition() = 0;
	virtual void SetAngle(int angleInDegrees) = 0;
	virtual void SetCentreOfRotationRelativeToTopLeft(Point*) = 0;
	virtual Point* GetCentreOfRotationRelativeToTopLeft() = 0;
};

class VisualItem : public IVisualItem
{
private:
	list<IVisualItem*> children;	
	Point* topLeft;
	IVisualItem* parent;
	Point* centreOfRotationRelativeToTopLeft;	
public:
	VisualItem();
	void Draw();
	void Add(IVisualItem*);
	void Delete();
	void SetTopLeft(Point* topLeft);
	Point* GetTopLeft();
	IVisualItem* GetParent();
	void SetParent(IVisualItem*);
	Point* GetAbsoluteScreenPosition();
	void SetAngle(int angleInDegrees);
	void SetCentreOfRotationRelativeToTopLeft(Point*);
	Point* GetCentreOfRotationRelativeToTopLeft();
};

class Sprite : public IVisualItem
{
private:
	int id;
	char* imageLocation;
	Point* topLeft;
	IVisualItem* parent;
	int angleInDegrees;
	Point* centreOfRotationRelativeToTopLeft;
	void DrawAtAbosoluteScreenCoOrd(Point*);
public:
	Sprite();
	void SetID(int value);
	int GetID();
	char* GetImageLocation();
	void  SetImageLocation(char*);
	void SetTopLeft(Point* topLeft);
	Point* GetTopLeft();
	void Draw();
	void Add(IVisualItem*); //TODO: Do nothing here. Seems a bit rubish to be forced to implement it.
	void Delete();
	IVisualItem* GetParent();
	void SetParent(IVisualItem*);
	Point* GetAbsoluteScreenPosition();
	Point* GetAbsoluteScreenPosition(Point* point);
	void SetAngle(int angleInDegrees);
	void SetCentreOfRotationRelativeToTopLeft(Point*);
	Point* GetCentreOfRotationRelativeToTopLeft();
};
//Contains methods and properties to draw to the screen
class GraphicsDB 
{
private:
	static GraphicsDB* _instance;
	int screenWidth;
	int screenHeight;
	std::tr1::unordered_map<char*, int> loadedImages;
	GraphicsDB();
	void DeleteSprite(int spriteID);
	void PlayWobbleVisualItem(IVisualItem* vItem,Point* change);
	int GetImageID(char* image);
public:	
	static GraphicsDB* GetInstance();
	void DeleteSprite(Sprite* sprite);
	void PlayMoveVisualItemAlongX(IVisualItem* vItem, int xChange);	
	void DrawSprite(Sprite* sprite, int topLeftX, int topLeftY, char* image);
	void DrawSprite(Sprite* sprite, int topLeftX, int topLeftY);
	void DrawSprite(Sprite* sprite, Point centreRotation, float angleDegrees, Point origTopLeft);
	void Initilaise(int screenWidth, int screenHeight);	
	int GetScreenWidth();
	int GetScreenHeight();
};

#endif /* DarkDraw */