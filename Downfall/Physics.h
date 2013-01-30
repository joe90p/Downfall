#ifndef Physics
#define Physics

#include <list>
#include <box2D.h>
#include <DarkDraw.h>

using namespace std;

class WorldScreenBridge
{
private:
	b2World* world;
	TwoDCoordinateSystemConverter* coOrdConverter;
	WorldScreenBridge* worldScreenBridge;
	void SetGroundBody();
	float width;
	b2Body* groundBody;
public:
	WorldScreenBridge(b2World* world, TwoDCoordinateSystemConverter* coOrdConverter, int width);
	b2World* GetWorld();
	Point* GetScreenCoOrd(PointFloat* worldCoOrd);
	Point* GetScreenDimensions(PointFloat* worldDimensions);
	PointFloat* GetWorldCoOrd(Point* screenCoOrd);
	PointFloat* GetWorldDimensions(Point* screenDimensions);
	b2Body* GetGroundBody();

};

class B2BodyFactory 
{
private:
	WorldScreenBridge* worldScreenBridge;
	float width;
	b2Body* groundBody;
public:
	B2BodyFactory(WorldScreenBridge* worldScreenBridge);
	b2Body* CreateDialBody(b2Vec2* centre, float dialRadius, int numberOfSlots, float slotRadius, int initialAngleInDegrees);
	b2Body* GetGroundBody();
	b2Body* CreateChute(PointFloat* centreOfFirstDial, float chuteLength, float firstDialRadius, float chuteWidth, float angleInRadians);
	void CreateEdge(b2Body* body, PointFloat* left, PointFloat* right);
	void CreateArc(Point* centre, int radius, int initAngleIndegrees, int sweepAngleInDegrees);
	void CreateBarrier(float slotRadius, float dialRadius, float* gapAngles, int numberOfGapAngles, float spacer, PointFloat* centre);
	void CreateArc(b2Vec2* centre, float radius, float initAngleInRadians, float sweepAngleInRadians);
	b2Body* CreateTokenWorld(PointFloat* centre, float radius);
	WorldScreenBridge* GetWorldScreenBridge();
};

class B2JointFactory
{
private:
	WorldScreenBridge* worldScreenBridge;
public:
	B2JointFactory(WorldScreenBridge* worldScreenBridge);
	b2Joint* CreateRevoluteDialJoint(b2Body* dial, float dialRadius, PointFloat* centreOfJoint);
	b2Joint* CreateGearJoint(b2Body* body1, b2Body* body2, b2Joint* joint1, b2Joint* joint2, float ratio);
};

class IB2BodyWrapper
{
	public:
		virtual b2Body* GetB2Body() = 0;
};

class B2BodyCircularScreenSection : IB2BodyWrapper
{
	private:
		float worldRadius;	
		b2Body* body;	
		WorldScreenBridge* worldScreenBridge;
	public:
		B2BodyCircularScreenSection(b2Body* body, float worldRadius, WorldScreenBridge* worldScreenBridge);
		b2Body* GetB2Body();
		Point* GetCentre();
		int GetRadius();
};

class DialBody
{
private:
	list<b2FixtureDef*> fixtures;
	list<b2PolygonShape> shapes;
	b2Body* body;
	float dialRadius;
	float slotRadius;
	int numberOfSlots;
	int initialAngleInDegrees;
public:
	DialBody(float dialRadius, float slotRadius, int numberOfSlots, int );
	void SetDialSlotFixtures(b2Body* body);
	void SetDialSlotShapes(int slotNumber);
	void Initialise(b2Body* body);
};

class DownfallBoard
{
private:
	B2BodyFactory* factory;
	B2JointFactory* jointFactory;
	B2BodyCircularScreenSection* token1;
	B2BodyCircularScreenSection* token2;
	B2BodyCircularScreenSection* token3;
	B2BodyCircularScreenSection* token4;
	B2BodyCircularScreenSection* token5;
	B2BodyCircularScreenSection* dial1;
	B2BodyCircularScreenSection* dial2;
	B2BodyCircularScreenSection* dial3;
	B2BodyCircularScreenSection* dial4;
	B2BodyCircularScreenSection* dial5;
	b2Vec2* dial5Centre;
	b2Vec2* dial4Centre;
	b2Vec2* dial3Centre;
	b2Vec2* dial2Centre;
	b2Vec2* dial1Centre;
	b2Joint* dial1RevoluteJoint;
	b2Joint* dial2RevoluteJoint;
	b2Joint* dial3RevoluteJoint;
	b2Joint* dial4RevoluteJoint;
	b2Joint* dial5RevoluteJoint;
	b2Joint* testGearJoint;
	float dial5Radius;
	float dial4Radius;
	float dial3Radius;
	float dial2Radius;
	float dial1Radius;
	float slotRadius;
	float gamma;
	float spacingExtra;
	float dial54AngleInRadians;
	float dial21AngleInRadians;
	float GetDialMNSpacer(float dialMRadius, float dialNRadius);
	float edgeAngleInRadians;
	void SetDial4Centre();
	void SetDial3Centre();
	void SetDial2Centre();
	void SetDial1Centre();
	void SetDials();
	void SetDialRadii();
	void SetDialCentres();
	void SetChute();
	void SetTokens();
	void SetDialBarriers();
	void SetDial1Barrier();
	void SetDial2Barrier();
	void SetDial3Barrier();
	void SetDial4Barrier();
	void SetDial5Barrier();
	void SetDialJoints();
	float barrierSlotGapIncreaseFactor;
	bool mirror;
	float multiplier;
	float dial5ExitAngle;
public:
	DownfallBoard(B2BodyFactory* factory, B2JointFactory* jointFactory, bool isMirror);
	B2BodyCircularScreenSection* GetToken1();
	B2BodyCircularScreenSection* GetToken2();
	B2BodyCircularScreenSection* GetToken3();
	B2BodyCircularScreenSection* GetToken4();
	B2BodyCircularScreenSection* GetToken5();
	B2BodyCircularScreenSection* GetDial1();
	B2BodyCircularScreenSection* GetDial2();
	B2BodyCircularScreenSection* GetDial3();
	B2BodyCircularScreenSection* GetDial4();
	B2BodyCircularScreenSection* GetDial5();
	b2Joint* GetDial1RevoluteJoint();
	b2Joint* GetDial2RevoluteJoint();
	b2Joint* GetDial3RevoluteJoint();
	b2Joint* GetDial4RevoluteJoint();
	b2Joint* GetDial5RevoluteJoint();	
};

class MouseJointManager
{
private:
	b2MouseJoint* mouseJoint;
	b2MouseJoint* mouseJointB;
	WorldScreenBridge* worldScreenBridge;
public:
	MouseJointManager(WorldScreenBridge* worldScreenBridge);
	void SetMouseJoint(b2Body* body, PointFloat* target);
	void SetMouseJointB(b2Body* body, PointFloat* target);
	void DestroyMouseJoint();
};




#endif /* Shapes */