#include <Physics.h>
#include <DarkDraw.h>

B2BodyFactory::B2BodyFactory(WorldScreenBridge* worldScreenBridge) : groundBody(0)
{
	this->worldScreenBridge = worldScreenBridge;
}

b2Body* B2BodyFactory::CreateTokenWorld(PointFloat* centre, float radius)
{
	b2BodyDef tokenBodyDef;
	b2FixtureDef tokenFixtureDef;
	b2CircleShape circle;
	b2Body* bod;
	
	tokenBodyDef.type = b2_dynamicBody;
	tokenBodyDef.position.Set(centre->GetX(), centre->GetY());
	bod =  this->GetWorldScreenBridge()->GetWorld()->CreateBody(&tokenBodyDef);
	
	circle.m_p.Set(0, 0);
	circle.m_radius = radius;
	
	tokenFixtureDef.shape = &circle;
	tokenFixtureDef.density = 1.0f;
	tokenFixtureDef.friction = 0.1f;	
	tokenFixtureDef.restitution = 0.6f;
	
	
	bod->CreateFixture(&tokenFixtureDef);
	
	return bod;
}



b2Body* B2BodyFactory::CreateDialBody(b2Vec2* centre, float dialRadius, int numberOfSlots, float slotRadius, int initialAngleInDegrees)
{
	b2RevoluteJointDef* jointDef;
	b2Body* body;
	b2BodyDef bodyDef;
	
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(centre->x, centre->y);
	body = this->GetWorldScreenBridge()->GetWorld()->CreateBody(&bodyDef);
	DialBody* dialBody = new DialBody(dialRadius, slotRadius, numberOfSlots, initialAngleInDegrees);
	dialBody->Initialise(body);
	
	/*jointDef = new b2RevoluteJointDef();
	jointDef->Initialize(body, this->GetGroundBody(), *centre);
	jointDef->maxMotorTorque = 1000 * dialRadius;
	jointDef->enableMotor = true;
	this->GetWorldScreenBridge()->GetWorld()->CreateJoint(jointDef);*/
	
	return body;
}

b2Body* B2BodyFactory::CreateChute(PointFloat* centreOfFirstDial, float chuteLength, float firstDialRadius, float chuteWidth, float angleInRadians)
{
	b2BodyDef bodyDef;
	b2Body* body;
	bodyDef.type = b2_staticBody;
	body = this->GetWorldScreenBridge()->GetWorld()->CreateBody(&bodyDef);
	
	//work out lower vertices and add fixture to the body
	float extraAngleInRadians = asinf(chuteWidth/(2 * firstDialRadius));
	float firstDialRadiusSpacer = (firstDialRadius * 8)/7;
	float bottomRightLowerX = centreOfFirstDial->GetX() + (firstDialRadiusSpacer * cosf(angleInRadians + extraAngleInRadians));
	float bottomRightLowerY = centreOfFirstDial->GetY() + (firstDialRadiusSpacer * sinf(angleInRadians + extraAngleInRadians));
	
	float bottomRightUpperX = centreOfFirstDial->GetX() + (firstDialRadiusSpacer * cosf(angleInRadians - extraAngleInRadians));
	float bottomRightUpperY = centreOfFirstDial->GetY() + (firstDialRadiusSpacer * sinf(angleInRadians - extraAngleInRadians));
	
	float  lowerWidthDivisor = 1.0f;
	float  upperWidthDivisor = 1.0f;
	
	
	PointFloat* bottomRightLower = new PointFloat(bottomRightLowerX, bottomRightLowerY); 
	PointFloat* topLeftLower = new PointFloat(	
												bottomRightLower->GetX() + ((chuteLength/lowerWidthDivisor) * cosf(angleInRadians)), 
												bottomRightLower->GetY() + ((chuteLength/lowerWidthDivisor) * sinf(angleInRadians))
										);
	
	PointFloat* bottomRightUpper = new PointFloat(bottomRightUpperX, bottomRightUpperY); 

	
	PointFloat* topLeftUpper = new PointFloat(	
												bottomRightUpper->GetX()+ ((chuteLength/upperWidthDivisor) * cosf(angleInRadians)), 
												bottomRightUpper->GetY()+ ((chuteLength/upperWidthDivisor) * sinf(angleInRadians))
										);
	
	this->CreateEdge(body, topLeftLower, bottomRightLower);
	this->CreateEdge(body, topLeftUpper, bottomRightUpper);
	return body;	
}

void B2BodyFactory::CreateEdge(b2Body* body, PointFloat* left, PointFloat* right)
{
	b2Vec2 p1 = b2Vec2(left->GetX(), left->GetY());
	b2Vec2 p2 = b2Vec2(right->GetX(), right->GetY());
	b2EdgeShape chuteShape;
	chuteShape.Set(p2, p1);
	
	b2FixtureDef fixtureDef;
	
	fixtureDef.shape = &chuteShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.8f;	
	fixtureDef.restitution = 0.6f;
	
	body->CreateFixture(&fixtureDef);
}

void B2BodyFactory::CreateBarrier(float slotRadius, float dialRadius, float* gapAngles, int numberOfGapAngles, float spacer, PointFloat* centre)
{
	//put angles in reverse order
	list<float> angles;
	list<float>::iterator it;
	for(int p = 0; p < numberOfGapAngles; p++)
	{
		angles.push_back(gapAngles[p]);
	}
	angles.sort();
	angles.reverse();
	int t = 0;
	for (it=angles.begin(); it!=angles.end(); it++)
	{
		gapAngles[t] = *it;
		t++;
	}
	//END put angles in reverse order
	float arc1GapAngle = asinf(slotRadius/(dialRadius));
	float dialSpacer = dialRadius + spacer;


	for(int p = numberOfGapAngles - 1; p >=0; p--)
	{
		float sweepAngle;
		float nextAngle;
		float initAngle = gapAngles[p] + arc1GapAngle;
	
		if(p == 0)
		{
			nextAngle = (gapAngles[numberOfGapAngles - 1] - arc1GapAngle);
		}
		else
		{
			nextAngle = (gapAngles[p-1] - arc1GapAngle);
		}
		if(nextAngle < initAngle)
		{
			sweepAngle = 6.28 - (initAngle - nextAngle);
		}
		else
		{
			sweepAngle = nextAngle - initAngle;
		}
		b2Vec2* b2Centre = new b2Vec2(centre->GetX(), centre->GetY());
		this->CreateArc(b2Centre, dialSpacer, initAngle, sweepAngle);
	}
	
}	
void B2BodyFactory::CreateArc(b2Vec2* centre, float radius, float initAngleInRadians, float sweepAngleInRadians)
{
	b2BodyDef bodyDef;
	b2Body* body;
	bodyDef.type = b2_staticBody;
	body = this->worldScreenBridge->GetWorld()->CreateBody(&bodyDef);
	
	int numberOfEdgesInArc = 16;
	
	b2Vec2 arc[16];
	
	for(int i=0; i<numberOfEdgesInArc; i++)
	{
		float angleInRadians = initAngleInRadians + (i *sweepAngleInRadians/(float)(numberOfEdgesInArc-1));
		
		float x = centre->x + (radius * cosf(angleInRadians));
		float y = centre->y +  (radius * sinf(angleInRadians));
		arc[i].Set(x,y);
	}
		b2ChainShape edgeShape;
		edgeShape.CreateChain(arc, numberOfEdgesInArc);
		b2FixtureDef fixtureDef;
	
		fixtureDef.shape = &edgeShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.8f;	
		fixtureDef.restitution = 0.6f;
		
		body->CreateFixture(&fixtureDef);
	
}
b2Body* B2BodyFactory::GetGroundBody()
{
	return this->worldScreenBridge->GetGroundBody();
}



WorldScreenBridge* B2BodyFactory::GetWorldScreenBridge()
{
	return this->worldScreenBridge;
}