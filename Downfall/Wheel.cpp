#include <Model.h>

Wheel::Wheel() : angle(0)
{

}

int Wheel::GetAngle()
{
	return this->angle;
}


//attach observers to be updated 
void Wheel::Attach(IWheelObserver* observer)
{
	this->observers.push_back(observer);
}

//Update the observers 
void Wheel::Notify()
{
	list<IWheelObserver*>::iterator i;
	for(i=this->observers.begin(); i != this->observers.end(); i++) 
	{
		(*i)->UpdateWithWheelInfo();
	}
}

void Wheel::SetAngle()
{
	static int angle = 10;
	//TODO: test stuff messy.
	if(this->state==Ready)
	{	
		this->angle = angle;
		angle = angle + 10;
		
	}
	Notify();
}

void Wheel::SetAngle(int value)
{
	if(this->state==Turning)
	{	
		this->angle = value;
	}	
	Notify();
}

WheelState Wheel::GetState()
{
	return this->state;
}

void Wheel::SetState()
{
	//TODO: test cycle through states
	static int testCounter = 0;
	switch(testCounter%3)
	{
		case 0:
			this->state = Free;
		break;
		
		case 1:
			this->state = Ready;
		break;
		
		case 2:
			this->state = Turning;
		break;
	}
	testCounter++;
}