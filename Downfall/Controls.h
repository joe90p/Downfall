#ifndef Controls
#define Controls

#include <Shapes.h>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <DarkDraw.h>
#include <box2D.h>
#include <Physics.h>
#include <Model.h>

//Represents an area of the screen controllable by the user
class Control
{
private:
	bool mouseIn;
	bool mouseUp;
	bool pressed;
	bool clicked;
	bool inPress;
	IVisualItem* visuals;
	IShape* clientArea;
	Point* topLeft;
	Control* parent;
	void SetMouseIn();
	void SetMouseUp();
	void SetPressed(bool oldMouseUp);
	void SetClicked(bool oldPressed);	
protected:
	list<Control*> controls;
	void SetVisuals(IVisualItem* visualItem);
	void SetClientArea(IShape*);
	IShape* GetClientArea();
public:
	Control(int topLeftX, int topLeftY);
	virtual void Update();
	boost::function<void()> Clicked;
	boost::function<void()> Pressed;
	boost::function<void()> MouseEnter;
	boost::function<void()> MouseLeave;	
	boost::function<void()> MouseUp;
	boost::function<void()> MouseDown;	
	boost::function<void()> OutOfPress;
	Point* GetTopLeft();
	IVisualItem* GetVisuals();
	void Add(Control* c);
	Control* GetParent();
	void SetParent(Control*);
	Point* GetAbsoluteScreenPosition(); 
};

//Represents a button control
class Button : public Control
{
private:
	char* imageLocation; // the file location of the standard image
	char* hoverImageLocation; // the file location of the hover image
	void OnMouseEnter();
	void OnMouseLeave();
	Sprite* mainSprite; //TODO: replace with something a bit nicer. A separate ButtonGraphics class maybe?
public:
	Button(int topLeftX, int topLeftY, int width, int height, char* imageLocation);
	void SetHoverImage(char* hoverImageLocation);
	void SetImage(char* imageLocation);		
};

class IGravityObject
{
public:
	virtual b2Body* GetB2Body() = 0;
	virtual void SetPhysicalTopLeft(Point*) = 0;
	virtual IVisualItem* GetGravityObjectVisuals() = 0; //TODO: nasty rename to get round Control having method of same name
	virtual void DrawGravityObject(int angleInDegrees) = 0;
};

//Represents a dial control
class Dial : public Control, public IGravityObject
{
private:
	b2Body* b2dBody;
	int radius;
	char* imageLocation; // the file location of the standard image
	Sprite* mainSprite; //TODO: replace with something a bit nicer. A separate DialGraphics class maybe?
	int initialAngleInDegrees;
	void Setup(int centreX, int centreY, int radius, char* imageLocation, int initialAngleInDegrees);
public:
	//Dial(int centreX, int centreY, int radius, char* imageLocation, int initialAngleInDegrees);
	Dial(B2BodyCircularScreenSection* bodyCircularSection, char* imageLocation, int initialAngleInDegrees);
	int GetRadius();
	void SetImage(char* imageLocation);
	b2Body* GetB2Body();
	void SetB2Body(b2Body* body);
	void SetPhysicalTopLeft(Point*);
	IVisualItem* GetGravityObjectVisuals(); //TODO: nasty rename to get round Control having method of same name
	void DrawGravityObject(int angleInDegrees);
};

//An object that acts under the influence of gravity
class Token : public VisualItem, public IGravityObject
{
private:
	b2Body* b2dBody;
	int width;
	int height;
public:
	Token(int topLeftX, int topLeftY);
	b2Body* GetB2Body();
	void SetB2Body(b2Body* body);
	void SetPhysicalTopLeft(Point*);
	IVisualItem* GetGravityObjectVisuals(); //TODO: nasty rename to get round Control having method of same name
	void DrawGravityObject(int angleInDegrees);
};

//A box that conatins gravity
class GravityBox : public Control
{
private:
	float gravityAcceleration;
	list<IGravityObject*> objects;		
	int width;
	int height;
	WorldScreenBridge* worldScreenBridge;
	MouseJointManager* mouseJointManager;
	b2World* GetB2World(TwoDCoordinateSystemConverter* converter);
	TwoDCoordinateSystemConverter* GetCoordConverter();
	void SetWorldScreenBridge();
public:
	GravityBox(Point* topLeft, float acceleration, int width, int height);
	void Update();
	void AddObject(IGravityObject* object);
	void Draw();
	void SetMouseJoint(IGravityObject* object, int x, int y);
	void DestroyMouseJoint();
	WorldScreenBridge* GetWorldScreenBridge();
};

class DownfallBoardControl 
{
private:
	GravityBox* gbTest;
	DownfallBoard* board;
	Dial* dial1;
	Dial* dial2;
	Dial* dial3;
	Dial* dial4;
	Dial* dial5;
	Token* token1;
	Token* token2;
	Token* token3;
	Token* token4;
	Token* token5;
	bool inPlay;
public:
	DownfallBoardControl(DownfallBoard* board, GravityBox* gbTest);
	void SetInPlay(bool inPlay);
	Dial* GetDial1();
	Dial* GetDial2();
	Dial* GetDial3();
	Dial* GetDial4();
	Dial* GetDial5();
	void SetMouseJoint(IGravityObject* gravObj);
	void DestroyMouseJoint();
	boost::function<void()> TurnOver;
};

class IPlayer
{
public:
	virtual void Play() = 0;
	virtual void SetOtherPlayer(IPlayer*) = 0;
};

class DownfallBoardPlayer : virtual public IPlayer
{
private:
	DownfallBoardControl* board;
	void dial1_Pressed();
	void dial1_MouseUp();
	void dial2_Pressed();
	void dial2_MouseUp();
	void dial3_Pressed();
	void dial3_MouseUp();
	void dial4_Pressed();
	void dial4_MouseUp();
	void dial5_Pressed();
	void dial5_MouseUp();
	IPlayer* otherPlayer;
	void BoardTurnOver();
public:
	DownfallBoardPlayer(DownfallBoardControl* board);
	void Play();
	void SetOtherPlayer(IPlayer*);
};



#endif /* Controls */