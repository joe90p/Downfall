#include <Display.h>

Over::Over(Game* myGame) : GameScreen(myGame)
{
	btTest = new Button(200, 500, 150, 75, "images/buttons/Start_normal.bmp");
	
}

void Over::Initialise()
{
	btTest->SetImage("images/buttons/Start_normal.bmp");
	btTest->SetHoverImage("images/buttons/Start_hover.bmp");
	//hook up event Handlers
	btTest->Clicked = boost::bind( &Over::btTest_Clicked, this);
	//add control to control array
	Add(btTest);
}

void Over::btTest_Clicked()
{
	this->GetMyGame()->SetState(Welcome);
}