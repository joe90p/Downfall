#include <Physics.h>

DialBody::DialBody(float dialRadius, float slotRadius, int numberOfSlots, int initialAngleInDegrees)
{
	this->dialRadius = dialRadius;
	this->slotRadius = slotRadius;
	this->numberOfSlots = numberOfSlots;
	this->initialAngleInDegrees = initialAngleInDegrees;
}

void DialBody::Initialise(b2Body* body)
{
	for(int i=0; i < numberOfSlots; i++)
	{
		this->SetDialSlotShapes(i);
	}
	this->SetDialSlotFixtures(body);
}


void DialBody::SetDialSlotFixtures(b2Body* body)
{
	list<b2PolygonShape>::iterator iter;
	for(iter = this->shapes.begin(); iter != this->shapes.end(); iter++) 
	{
		b2FixtureDef fixture;
		fixture.shape = &(*iter);
		fixture.density = 1.0f;
		fixture.friction = 0.3f;	
		fixture.restitution = 0.4f;
		body->CreateFixture(&fixture);
	}
}



void DialBody::SetDialSlotShapes(int slotNumber)
{
	float angleMain = (2 * 3.141/numberOfSlots * slotNumber) + (0.0175 * this->initialAngleInDegrees);
	float outerTriangleAngle = (3.14/6) - asinf( (dialRadius - (3 * slotRadius)) * (1/(2*dialRadius)) );
	float radiusToInnerTriangleCentre = sqrtf(powf(dialRadius - slotRadius, 2.0f) + powf(2 * slotRadius * tanf(3.142f/6), 2.0f));
	float innerTriangleCentreAngle = atanf((2 * slotRadius * tanf(3.142f/6))/(dialRadius - slotRadius));
	float innerTriangleRightAngle = asinf((2 * slotRadius * tanf(3.142f/6))/dialRadius);
	float centreTriangleAngle = atanf((slotRadius * tanf(3.142f/6))/(dialRadius - (2 * slotRadius)));
	float centreTriangleRadius = sqrtf(powf(dialRadius - (2 * slotRadius), 2.0f) + powf(slotRadius * tanf(3.142f/6), 2.0f));
		
	b2Vec2 outerTriangleLeft[3];
	b2Vec2 outerTriangleRight[3];
	b2Vec2 innerTriangleLeft[3];
	b2Vec2 innerTriangleRight[3];
	b2Vec2 centreTriangle[3];
	b2PolygonShape outerTriangleLeftShape;
	b2PolygonShape outerTriangleRightShape;
	b2PolygonShape innerTriangleLeftShape;
	b2PolygonShape innerTriangleRightShape;
	b2PolygonShape centreTriangleShape;
		
	outerTriangleLeft[0].Set(0, 0);
	outerTriangleLeft[1].Set((dialRadius - (3 * slotRadius)) * sinf(angleMain), (dialRadius - (3 * slotRadius)) * cosf(angleMain));
	outerTriangleLeft[2].Set(dialRadius * sinf(angleMain - outerTriangleAngle) , dialRadius * cosf(angleMain - outerTriangleAngle) );	
		
	outerTriangleRight[0].Set(0, 0);
	outerTriangleRight[2].Set((dialRadius - (3 * slotRadius)) * sinf(angleMain), (dialRadius - (3 * slotRadius)) * cosf(angleMain));
	outerTriangleRight[1].Set(dialRadius * sinf(angleMain + outerTriangleAngle) , dialRadius * cosf(angleMain + outerTriangleAngle) );
		
	innerTriangleLeft[0].Set(radiusToInnerTriangleCentre * sinf(angleMain - innerTriangleCentreAngle), radiusToInnerTriangleCentre * cosf(angleMain - innerTriangleCentreAngle));
	innerTriangleLeft[1].Set(dialRadius * sinf(angleMain - innerTriangleRightAngle), dialRadius * cosf(angleMain - innerTriangleRightAngle));
	innerTriangleLeft[2].Set(dialRadius * sinf(angleMain - outerTriangleAngle) , dialRadius * cosf(angleMain - outerTriangleAngle) );
		
	innerTriangleRight[0].Set(radiusToInnerTriangleCentre * sinf(angleMain + innerTriangleCentreAngle), radiusToInnerTriangleCentre * cosf(angleMain + innerTriangleCentreAngle));
	innerTriangleRight[2].Set(dialRadius * sinf(angleMain + innerTriangleRightAngle), dialRadius * cosf(angleMain + innerTriangleRightAngle));
	innerTriangleRight[1].Set(dialRadius * sinf(angleMain + outerTriangleAngle) , dialRadius * cosf(angleMain + outerTriangleAngle) );
		
	centreTriangle[0].Set((dialRadius - (3 * slotRadius)) * sinf(angleMain), (dialRadius - (3 * slotRadius)) * cosf(angleMain));
	centreTriangle[1].Set(centreTriangleRadius * sinf(angleMain + centreTriangleAngle), centreTriangleRadius * cosf(angleMain + centreTriangleAngle));
	centreTriangle[2].Set(centreTriangleRadius * sinf(angleMain - centreTriangleAngle) , centreTriangleRadius * cosf(angleMain - centreTriangleAngle) );
		
	outerTriangleLeftShape.Set(outerTriangleLeft, 3);
	outerTriangleRightShape.Set(outerTriangleRight, 3);
	innerTriangleLeftShape.Set(innerTriangleLeft, 3);
	innerTriangleRightShape.Set(innerTriangleRight, 3);
	centreTriangleShape.Set(centreTriangle, 3);
	
	this->shapes.push_back(outerTriangleLeftShape);
	this->shapes.push_back(outerTriangleRightShape);
	this->shapes.push_back(innerTriangleLeftShape);
	this->shapes.push_back(innerTriangleRightShape);
	this->shapes.push_back(centreTriangleShape);
	
	float factor = 6.0;
	float phi = outerTriangleAngle + (3.142f/factor);
		
	while(phi < (2 * 3.141/numberOfSlots) - outerTriangleAngle)
	{
		b2Vec2 triangle[3];
		b2PolygonShape triangleShape;
			
		triangle[0].Set(0, 0);		
		triangle[1].Set(dialRadius * sinf(angleMain + phi), dialRadius * cosf(angleMain + phi));
		triangle[2].Set(dialRadius * sinf(angleMain + phi - (3.142f/factor)), dialRadius * cosf(angleMain + phi - (3.142f/factor)) );
		triangleShape.Set(triangle, 3);
		this->shapes.push_back(triangleShape);
			
		phi = phi + (3.142f/factor);
	}
		
	b2Vec2 triangle[3];
	b2PolygonShape triangleShape;
			
	triangle[0].Set(0, 0);		
	triangle[1].Set(dialRadius * sinf(angleMain + (2 * 3.141/numberOfSlots) - outerTriangleAngle), dialRadius * cosf(angleMain + (2 * 3.141/numberOfSlots) - outerTriangleAngle));
	triangle[2].Set(dialRadius * sinf(angleMain + phi - (3.142f/factor)), dialRadius * cosf(angleMain + phi - (3.142f/factor)) );
	triangleShape.Set(triangle, 3);
	this->shapes.push_back(triangleShape);
}