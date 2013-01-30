#include <DarkDraw.h>


GraphicsDB* GraphicsDB::_instance = 0;

GraphicsDB::GraphicsDB()
{
		
}

void GraphicsDB::Initilaise(int screenWidth, int screenHeight)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
}

void GraphicsDB::DrawSprite(Sprite* sprite, int topLeftX, int topLeftY, char* image)
{
	static int dummySpriteID = 1; //TODO: replace this
	int imageID = GetImageID(image);
	if(sprite->GetID()==-1)
	{
		int newSpriteID = dummySpriteID;
		sprite->SetID(newSpriteID);
		dummySpriteID++;
	}
	dbSprite(sprite->GetID(), topLeftX, topLeftY, imageID);
}

void GraphicsDB::DrawSprite(Sprite* sprite, int topLeftX, int topLeftY)
{
	DrawSprite(sprite, topLeftX, topLeftY, sprite->GetImageLocation());
}

void GraphicsDB::DrawSprite(Sprite* sprite, Point centreRotation, float angleDegrees, Point origTopLeft)
{
	float angleRadians;
	float r;
	//firstly express the centre of rotation as a polar co-ord (r, theta) with origTopLeft as origin
	float deltaX;
	float deltaY;
	float theta;
	deltaX = ((float)(centreRotation.GetX() - origTopLeft.GetX()));
	deltaY = ((float)(centreRotation.GetY() - origTopLeft.GetY()));
	
	r = sqrt(
					(float)((float)pow(deltaX, (float)2.0) + (float)pow(deltaY, (float)2.0))
					);
	theta = atan((float)(centreRotation.GetY() - origTopLeft.GetY())/(float)(centreRotation.GetX() - origTopLeft.GetX()));
	//------------------------------------------
	//Work out the angle of rotation (thi) in terms of our polar co-ord system
	angleRadians = angleDegrees*(3.14159f/180);
	float thi = angleRadians + theta;	
	//rotate sprite
	dbRotateSprite(sprite->GetID(), angleDegrees);
	//shift the sprite so centreof rotation is unchanged
	dbSprite(sprite->GetID(), 
				origTopLeft.GetX() + Maths::RoundToNearestInt(r*(cos(theta) - cos(thi))),
				origTopLeft.GetY() + Maths::RoundToNearestInt(r*(sin(theta) - sin(thi))),
				GetImageID(sprite->GetImageLocation()));
	
}
int GraphicsDB::GetImageID(char* image)
{
	static int nextImageId = 1;
	if(this->loadedImages.count(image)==0)
	{
		dbLoadImage(image, nextImageId, 1); //setting the texture flag to 1 preserves the full quality of the image
		this->loadedImages[image] = nextImageId;
		nextImageId++;
	}
	return this->loadedImages[image];
}

//draws a new sprite on the screen and returns the sprite id
void GraphicsDB::DeleteSprite(int spriteID)
{
	if(dbSpriteExist(spriteID)==1)
	{
		dbDeleteSprite(spriteID);
	}
}

void GraphicsDB::DeleteSprite(Sprite* sprite)
{
	DeleteSprite(sprite->GetID());
}

GraphicsDB* GraphicsDB::GetInstance()
{
	if(_instance==0)
	{
		_instance = new GraphicsDB();
	}
	return _instance;
}


void GraphicsDB::PlayMoveVisualItemAlongX(IVisualItem* vItem, int xChange)
{
	int time = 600;
	int timerStart = dbTimer();
	int elapsedTime = 0;
	float speed = (float)xChange/(float)time;
	Point* initialPosition = vItem->GetTopLeft();
	int initX = initialPosition->GetX();
	int initY = initialPosition->GetY();
	
	//move sprites at speed and refresh (sync) the screen
	while(elapsedTime < time)
	{
		elapsedTime = dbTimer() - timerStart;
		vItem->SetTopLeft(new Point(initX + Maths::RoundToNearestInt(speed * elapsedTime), initY));
		vItem->Draw();
		dbSync();
	}
	
	//wobble the item
	PlayWobbleVisualItem(vItem, new Point(initX + xChange, initY));
	
	//move into correct position
	vItem->SetTopLeft(new Point(initX + xChange, initY));
	vItem->Draw();
	
}
//wobbles the item with damped simple harmonic motion
void GraphicsDB::PlayWobbleVisualItem(IVisualItem* vItem, Point* change)
{
	int timerStart = dbTimer();
	int elapsedTime = 0;
	int maxTime = 600;
	double alpha = 15;
	double beta = (double)(-1.75/1000);
	double gamma = (double)((3*3.14159)/maxTime);
	list<Sprite*>::iterator i;
	int xChange = change->GetX();
	int yChange = change->GetY();
	
	while(elapsedTime < maxTime)
	{
		vItem->SetTopLeft(new Point(xChange +  Maths::RoundToNearestInt(alpha*exp(beta*elapsedTime)*sin(gamma*elapsedTime)), yChange));
		vItem->Draw();
		elapsedTime = dbTimer() - timerStart;
		dbSync();
	}
}
int GraphicsDB::GetScreenWidth()
{
	return this->screenWidth;
}
int GraphicsDB::GetScreenHeight()
{
	return this->screenHeight;
}