#include <Physics.h>


DownfallBoard::DownfallBoard(B2BodyFactory *factory, B2JointFactory* jointFactory, bool isMirror)
{
	this->mirror = isMirror;
	if(this->mirror)
	{
		this->dial54AngleInRadians = (150.0 * (3.14/180.0));
		this->dial21AngleInRadians = (60.0 * (3.14/180.0));
		this->multiplier = -1.0;
		this->dial5Centre = new b2Vec2 (25, 4.25);
		this->dial5ExitAngle = 3.14 + (6.28 - 5.5);
		this->edgeAngleInRadians = 30 * (3.142f/180.0f);
	}
	else
	{
		this->dial54AngleInRadians = (30.0 * (3.14/180.0));
		this->dial21AngleInRadians = (120.0 * (3.14/180.0));
		this->multiplier = 1.0;
		this->dial5Centre = new b2Vec2 (6, 4.25);
		this->dial5ExitAngle = 5.5;
		this->edgeAngleInRadians = 150 * (3.142f/180.0f);
	}
	this->barrierSlotGapIncreaseFactor = 1.5;
	this->factory = factory;
	this->jointFactory = jointFactory;
	this->SetDialRadii();
	this->slotRadius = this->dial1Radius/3.75;
	this->spacingExtra = this->dial1Radius/8.0;						
	this->SetDials();
	this->SetChute();
	this->SetTokens();
	this->SetDialBarriers();
	this->SetDialJoints();
	
	
	
}

void DownfallBoard::SetDialJoints()
{
	this->dial1RevoluteJoint =  this->jointFactory->CreateRevoluteDialJoint(this->dial1->GetB2Body(), this->dial1Radius, new PointFloat(this->dial1Centre->x, this->dial1Centre->y ) );
	this->dial2RevoluteJoint =  this->jointFactory->CreateRevoluteDialJoint(this->dial2->GetB2Body(), this->dial2Radius, new PointFloat(this->dial2Centre->x, this->dial2Centre->y ) );
	this->dial3RevoluteJoint =  this->jointFactory->CreateRevoluteDialJoint(this->dial3->GetB2Body(), this->dial3Radius, new PointFloat(this->dial3Centre->x, this->dial3Centre->y ) );
	this->dial4RevoluteJoint =  this->jointFactory->CreateRevoluteDialJoint(this->dial4->GetB2Body(), this->dial4Radius, new PointFloat(this->dial4Centre->x, this->dial4Centre->y) );
	this->dial5RevoluteJoint =  this->jointFactory->CreateRevoluteDialJoint(this->dial5->GetB2Body(), this->dial5Radius, new PointFloat(this->dial5Centre->x, this->dial5Centre->y) );
}
void DownfallBoard::SetDialBarriers()
{
	this->SetDial1Barrier();
	this->SetDial2Barrier();
	this->SetDial3Barrier();
	this->SetDial4Barrier();
	this->SetDial5Barrier();
}
void DownfallBoard::SetDial1Barrier()
{
	int numberOfGaps = 2;
	PointFloat* dial1CentrePf = new PointFloat(this->dial1Centre->x, this->dial1Centre->y);
	PointFloat* dial2CentrePf = new PointFloat(this->dial2Centre->x, this->dial2Centre->y);
	float gapAngles[2];
	gapAngles[0] = dial1CentrePf->GetAngleBetween(dial2CentrePf);
	gapAngles[1] = edgeAngleInRadians;
	this->factory->CreateBarrier(
								barrierSlotGapIncreaseFactor * slotRadius, 
								dial1Radius, 
								gapAngles, 
								numberOfGaps, 
								(this->spacingExtra/2.0), 
								dial1CentrePf
								);
}
void DownfallBoard::SetDial2Barrier()
{
	int numberOfGaps = 3;
	PointFloat* dial2CentrePf = new PointFloat(this->dial2Centre->x, this->dial2Centre->y);
	PointFloat* dial3CentrePf = new PointFloat(this->dial3Centre->x, this->dial3Centre->y);
	PointFloat* dial1CentrePf = new PointFloat(this->dial1Centre->x, this->dial1Centre->y);
	PointFloat* dial4CentrePf = new PointFloat(this->dial4Centre->x, this->dial4Centre->y);
	float gapAngles[3];
	gapAngles[0] = dial2CentrePf->GetAngleBetween(dial4CentrePf);
	gapAngles[1] = dial2CentrePf->GetAngleBetween(dial3CentrePf);
	gapAngles[2] = dial2CentrePf->GetAngleBetween(dial1CentrePf);
	this->factory->CreateBarrier(
								barrierSlotGapIncreaseFactor * slotRadius, 
								dial2Radius, 
								gapAngles, 
								numberOfGaps, 
								(this->spacingExtra/2.0), 
								dial2CentrePf
								);
}
void DownfallBoard::SetDial3Barrier()
{
	int numberOfGaps = 3;
	PointFloat* dial3CentrePf = new PointFloat(this->dial3Centre->x, this->dial3Centre->y);
	PointFloat* dial4CentrePf = new PointFloat(this->dial4Centre->x, this->dial4Centre->y);
	PointFloat* dial2CentrePf = new PointFloat(this->dial2Centre->x, this->dial2Centre->y);	
	PointFloat* dial5CentrePf = new PointFloat(this->dial5Centre->x, this->dial5Centre->y);
	float gapAngles[3];
	gapAngles[0] = dial3CentrePf->GetAngleBetween(dial4CentrePf);
	gapAngles[1] = dial3CentrePf->GetAngleBetween(dial5CentrePf);
	gapAngles[2] = dial3CentrePf->GetAngleBetween(dial2CentrePf);
	this->factory->CreateBarrier(
								barrierSlotGapIncreaseFactor * slotRadius, 
								dial3Radius, 
								gapAngles, 
								numberOfGaps, 
								(this->spacingExtra/2.0), 
								dial3CentrePf
								);
}
void DownfallBoard::SetDial4Barrier()
{
	int numberOfGaps = 3;
	PointFloat* dial4CentrePf = new PointFloat(this->dial4Centre->x, this->dial4Centre->y);
	PointFloat* dial2CentrePf = new PointFloat(this->dial2Centre->x, this->dial2Centre->y);
	PointFloat* dial3CentrePf = new PointFloat(this->dial3Centre->x, this->dial3Centre->y);
	PointFloat* dial5CentrePf = new PointFloat(this->dial5Centre->x, this->dial5Centre->y);
	
	float gapAngles[3];
	gapAngles[0] = dial4CentrePf->GetAngleBetween(dial5CentrePf);
	gapAngles[1] = dial4CentrePf->GetAngleBetween(dial3CentrePf);
	gapAngles[2] = dial4CentrePf->GetAngleBetween(dial2CentrePf);
	this->factory->CreateBarrier(
								barrierSlotGapIncreaseFactor * slotRadius, 
								this->dial4Radius, 
								gapAngles, 
								numberOfGaps, 
								(this->spacingExtra/2.0), 
								dial4CentrePf
								);
}
void DownfallBoard::SetDial5Barrier()
{
	int numberOfGaps = 3;
	PointFloat* dial5CentrePf = new PointFloat(this->dial5Centre->x, this->dial5Centre->y);
	PointFloat* dial3CentrePf = new PointFloat(this->dial3Centre->x, this->dial3Centre->y);
	PointFloat* dial4CentrePf = new PointFloat(this->dial4Centre->x, this->dial4Centre->y);
	float gapAngles[3];
	gapAngles[0] = this->dial5ExitAngle; //this is where tokens exit the board;
	gapAngles[1] = dial5CentrePf->GetAngleBetween(dial3CentrePf);
	gapAngles[2] = dial5CentrePf->GetAngleBetween(dial4CentrePf);
	this->factory->CreateBarrier(
								barrierSlotGapIncreaseFactor * slotRadius, 
								this->dial5Radius, 
								gapAngles, 
								numberOfGaps, 
								(this->spacingExtra/2.0), 
								dial5CentrePf
								);
}
void DownfallBoard::SetTokens()
{
	b2Body* token1Bod;
	b2Body* token2Bod;
	b2Body* token3Bod;
	b2Body* token4Bod;
	b2Body* token5Bod;
	float dial1Spacer = (this->dial1Radius * 8)/7;
	for(int i=1; i<=5; i++)
	{
		float x = this->dial1Centre->x + ((dial1Spacer + (2*i*this->slotRadius)) * cosf(this->edgeAngleInRadians));
		float y = this->dial1Centre->y + ((dial1Spacer + (2*i*this->slotRadius)) * sinf(this->edgeAngleInRadians));
		b2Body* bod = this->factory->CreateTokenWorld(new PointFloat(x,y), this->slotRadius);
		switch(i)
		{
			case 1:
				token1Bod = bod;
				break;
			case 2:
				token2Bod = bod;
				break;
			case 3:
				token3Bod = bod;
				break;
			case 4:
				token4Bod = bod;
				break;
			case 5:
				token5Bod = bod;
				break;
		}
	}
	
	this->token1 = new B2BodyCircularScreenSection(token1Bod, this->slotRadius, this->factory->GetWorldScreenBridge());
	this->token2 = new B2BodyCircularScreenSection(token2Bod, this->slotRadius, this->factory->GetWorldScreenBridge());
	this->token3 = new B2BodyCircularScreenSection(token3Bod, this->slotRadius, this->factory->GetWorldScreenBridge());
	this->token4 = new B2BodyCircularScreenSection(token4Bod, this->slotRadius, this->factory->GetWorldScreenBridge());
	this->token5 = new B2BodyCircularScreenSection(token5Bod, this->slotRadius, this->factory->GetWorldScreenBridge());
}

void DownfallBoard::SetChute()
{
	
	float chuteWidth = this->slotRadius * 2.1;
	float chuteLength = 3 * this->dial1Radius;
	PointFloat* centreOfFirstDial = new PointFloat(this->dial1Centre->x, this->dial1Centre->y);
	this->factory->CreateChute(centreOfFirstDial, chuteLength, this->dial1Radius, chuteWidth, this->edgeAngleInRadians);
}

void DownfallBoard::SetDials()
{
	b2Body* dial5Body;
	b2Body* dial4Body;
	b2Body* dial3Body;
	b2Body* dial2Body;
	b2Body* dial1Body;
	
	this->SetDialCentres();
	dial5Body = this->factory->CreateDialBody(this->dial5Centre, this->dial5Radius, 5, this->slotRadius, 0);
	dial4Body = this->factory->CreateDialBody(this->dial4Centre, this->dial4Radius, 4, this->slotRadius, 0);
	dial3Body = this->factory->CreateDialBody(this->dial3Centre, this->dial3Radius, 2, this->slotRadius, 0);
	dial2Body = this->factory->CreateDialBody(this->dial2Centre, this->dial2Radius, 3, this->slotRadius, 0);
	dial1Body = this->factory->CreateDialBody(this->dial1Centre, this->dial1Radius, 1, this->slotRadius, 0);
	
	
	this->dial1 = new B2BodyCircularScreenSection(dial1Body, this->dial1Radius, this->factory->GetWorldScreenBridge());
	this->dial2 = new B2BodyCircularScreenSection(dial2Body, this->dial2Radius, this->factory->GetWorldScreenBridge());
	this->dial3 = new B2BodyCircularScreenSection(dial3Body, this->dial3Radius, this->factory->GetWorldScreenBridge());
	this->dial4 = new B2BodyCircularScreenSection(dial4Body, this->dial4Radius, this->factory->GetWorldScreenBridge());
	this->dial5 = new B2BodyCircularScreenSection(dial5Body, this->dial5Radius, this->factory->GetWorldScreenBridge());
	
}


void DownfallBoard::SetDialRadii()
{
	this->dial1Radius = 2.0;
	this->dial5Radius = 1.62 * dial1Radius;
	this->dial4Radius = 1.32 * dial1Radius;
	this->dial3Radius = dial1Radius * 1.1;
	this->dial2Radius = 1.22 * dial1Radius;
}
void DownfallBoard::SetDialCentres()
{
	this->SetDial4Centre();	
	this->SetDial3Centre();							
	this->SetDial2Centre();							
	this->SetDial1Centre();	
}
void DownfallBoard::SetDial1Centre()
{
	float dial21Spacer = this->GetDialMNSpacer(dial2Radius, dial1Radius);
	this->dial1Centre = new b2Vec2(this->dial2Centre->x + (dial21Spacer * cosf(dial21AngleInRadians)), this->dial2Centre->y + (dial21Spacer * sinf(this->dial21AngleInRadians)));
}

void DownfallBoard::SetDial2Centre()
{
	float dial42Spacer = this->GetDialMNSpacer(this->dial4Radius, this->dial2Radius);
	float dial32Spacer = this->GetDialMNSpacer(this->dial3Radius, this->dial2Radius); 
	float dial43Spacer = this->GetDialMNSpacer(this->dial4Radius, this->dial3Radius); 
	float dial53Spacer = this->GetDialMNSpacer(this->dial5Radius, this->dial3Radius);
	
	float numerator = powf(dial42Spacer, 2.0f) - powf(dial32Spacer, 2.0f) - powf(dial43Spacer, 2.0f);
	float denominator = -2 * (dial32Spacer) * (dial43Spacer);
	float theta = acosf(numerator/denominator);
	float alpha = asinf(dial53Spacer * sinf(this->gamma)/dial43Spacer);
	float dial32AngleInRadians = this->dial54AngleInRadians + ( this->multiplier * (theta - alpha));
	this->dial2Centre = new b2Vec2(this->dial3Centre->x + (dial32Spacer * cosf(dial32AngleInRadians)), this->dial3Centre->y + (dial32Spacer * sinf(dial32AngleInRadians)));
}


void DownfallBoard::SetDial3Centre()
{
	float dial53Spacer = this->GetDialMNSpacer(this->dial5Radius, this->dial3Radius);
	float dial43Spacer = this->GetDialMNSpacer(this->dial4Radius, this->dial3Radius); 
	float dial54Spacer = this->GetDialMNSpacer(this->dial5Radius, this->dial4Radius);
	float numerator = powf(dial43Spacer, 2.0f) - powf(dial53Spacer, 2.0f) - powf(dial54Spacer, 2.0f);
	float denominator = -2 * (dial53Spacer) * (dial54Spacer);
	this->gamma = acosf(numerator/denominator);
	

	float dial53AngleInRadians = this->dial54AngleInRadians + (this->multiplier * this->gamma);

	this->dial3Centre = new b2Vec2(this->dial5Centre->x + (dial53Spacer * cosf(dial53AngleInRadians)), this->dial5Centre->y + (dial53Spacer * sinf(dial53AngleInRadians)));
}



void DownfallBoard::SetDial4Centre()
{
	float dial54Spacer = this->GetDialMNSpacer(this->dial5Radius, this->dial4Radius);
	this->dial4Centre = new b2Vec2(this->dial5Centre->x + (dial54Spacer * cosf(this->dial54AngleInRadians)), this->dial5Centre->y + (dial54Spacer * sinf(this->dial54AngleInRadians)));
}

float DownfallBoard::GetDialMNSpacer(float dialMRadius, float dialNRadius)
{
	return (dialMRadius + dialNRadius) + this->spacingExtra;
}


B2BodyCircularScreenSection* DownfallBoard::GetToken1()
{
	return this->token1;
}
B2BodyCircularScreenSection* DownfallBoard::GetToken2()
{
	return this->token2;
}
B2BodyCircularScreenSection* DownfallBoard::GetToken3()
{
	return this->token3;
}
B2BodyCircularScreenSection* DownfallBoard::GetToken4()
{
	return this->token4;
}
B2BodyCircularScreenSection* DownfallBoard::GetToken5()
{
	return this->token5;
}

B2BodyCircularScreenSection* DownfallBoard::GetDial1()
{
	return this->dial1;
}
B2BodyCircularScreenSection* DownfallBoard::GetDial2()
{
	return this->dial2;
}
B2BodyCircularScreenSection* DownfallBoard::GetDial3()
{
	return this->dial3;
}
B2BodyCircularScreenSection* DownfallBoard::GetDial4()
{
	return this->dial4;
}
B2BodyCircularScreenSection* DownfallBoard::GetDial5()
{
	return this->dial5;
}







b2Joint* DownfallBoard::GetDial1RevoluteJoint()
{
	return this->dial1RevoluteJoint;
}
b2Joint* DownfallBoard::GetDial2RevoluteJoint()
{
	return this->dial2RevoluteJoint;
}
b2Joint* DownfallBoard::GetDial3RevoluteJoint()
{
	return this->dial3RevoluteJoint;
}
b2Joint* DownfallBoard::GetDial4RevoluteJoint()
{
	return this->dial4RevoluteJoint;
}
b2Joint* DownfallBoard::GetDial5RevoluteJoint()
{
	return this->dial5RevoluteJoint;
}