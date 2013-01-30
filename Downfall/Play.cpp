#include <Display.h>

Play::Play(Game* myGame) : GameScreen(myGame)
{
	btTest = new Button(200, 400, 150, 75, "images/buttons/Start_normal.bmp");
}

void Play::Initialise()
{
	//btTest
	btTest->SetImage("images/buttons/Start_normal.bmp");
	btTest->SetHoverImage("images/buttons/Start_hover.bmp");
	
	//hook up event Handlers
	btTest->Clicked = boost::bind( &Play::btTest_Clicked, this);
	
	//add controls to control array
	Add(btTest);
}

void Play::btTest_Clicked()
{
	this->GetMyGame()->SetState(GameOver);
}