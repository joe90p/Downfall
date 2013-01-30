#include <Display.h>


Start::Start(Game* myGame) : GameScreen(myGame)
{
	this->btTest = new Button(200, 650, 150, 75,"images/buttons/Start_normal.bmp");	
	this->btTest2 = new Button(700, 650, 150, 75,"images/buttons/Start_normal.bmp");
	this->btTest->SetImage("images/buttons/Start_normal.bmp");
	this->btTest2->SetImage("images/buttons/Start_normal.bmp");
	this->btTest->SetHoverImage("images/buttons/Start_hover.bmp");
	this->btTest2->SetHoverImage("images/buttons/Start_hover.bmp");
	btTest->Clicked = boost::bind( &Start::btTest_Clicked, this);
	this->gbTest = new GravityBox(new Point(50, 50), -20.0, 1000, 600);
	B2BodyFactory* bodFac = new B2BodyFactory(gbTest->GetWorldScreenBridge());
	B2JointFactory* jointFac = new B2JointFactory(gbTest->GetWorldScreenBridge());
	DownfallBoard* board = new DownfallBoard(bodFac, jointFac, false);
	DownfallBoard* boardMirrored = new DownfallBoard(bodFac, jointFac, true);
	
	this->boardControl = new DownfallBoardControl(board, gbTest);
	this->mirroredBoardControl = new DownfallBoardControl(boardMirrored, gbTest);
	this->player1 = new DownfallBoardPlayer(boardControl);
	this->player2 = new DownfallBoardPlayer(mirroredBoardControl);
	this->player1->SetOtherPlayer(player2);
	this->player2->SetOtherPlayer(player1);
	this->player1->Play();

	jointFac->CreateGearJoint(
										board->GetDial1()->GetB2Body(), 
										boardMirrored->GetDial1()->GetB2Body(),
										board->GetDial1RevoluteJoint(),
										boardMirrored->GetDial1RevoluteJoint(),
										1.0);
	jointFac->CreateGearJoint(
										board->GetDial2()->GetB2Body(), 
										boardMirrored->GetDial2()->GetB2Body(),
										board->GetDial2RevoluteJoint(),
										boardMirrored->GetDial2RevoluteJoint(),
										1.0);
	jointFac->CreateGearJoint(
										board->GetDial3()->GetB2Body(), 
										boardMirrored->GetDial3()->GetB2Body(),
										board->GetDial3RevoluteJoint(),
										boardMirrored->GetDial3RevoluteJoint(),
										1.0);
	jointFac->CreateGearJoint(
										board->GetDial4()->GetB2Body(), 
										boardMirrored->GetDial4()->GetB2Body(),
										board->GetDial4RevoluteJoint(),
										boardMirrored->GetDial4RevoluteJoint(),
										1.0);
	jointFac->CreateGearJoint(
										board->GetDial5()->GetB2Body(), 
										boardMirrored->GetDial5()->GetB2Body(),
										board->GetDial5RevoluteJoint(),
										boardMirrored->GetDial5RevoluteJoint(),
										1.0);
	

}

void Start::Initialise()
{
	//add controls to control array
	Add(btTest);
	Add(btTest2);
	Add(gbTest);
}


void Start::btTest_Clicked()
{
this->GetMyGame()->SetState(GameState::InPlay);
}
