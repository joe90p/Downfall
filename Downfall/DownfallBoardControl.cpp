#include <Controls.h>


DownfallBoardControl::DownfallBoardControl(DownfallBoard* board, GravityBox* gbTest) : TurnOver(0)
{
	this->inPlay = true;
	this->gbTest = gbTest;
	this->board = board;
	this->token1 = new Token(0,0);
	this->token2 = new Token(0,0);
	this->token3 = new Token(0,0);
	this->token4 = new Token(0,0);
	this->token5 = new Token(0,0);
	token1->SetB2Body(board->GetToken1()->GetB2Body());
	token2->SetB2Body(board->GetToken2()->GetB2Body());
	token3->SetB2Body(board->GetToken3()->GetB2Body());
	token4->SetB2Body(board->GetToken4()->GetB2Body());
	token5->SetB2Body(board->GetToken5()->GetB2Body());
	this->dial1 = new Dial(board->GetDial1(), "images/dials/dial1.png", 0);
	this->dial2 = new Dial(board->GetDial2(), "images/dials/dial2.png", 0);
	this->dial3 = new Dial(board->GetDial3(), "images/dials/dial3.png", 0);
	this->dial4 = new Dial(board->GetDial4(), "images/dials/dial4.png", 0);
	this->dial5 = new Dial(board->GetDial5(), "images/dials/dial5.png", 0);
	
	gbTest->Add(dial1);
	gbTest->Add(dial2);
	gbTest->Add(dial3);
	gbTest->Add(dial4);
	gbTest->Add(dial5);
	
	gbTest->AddObject(dial1);
	gbTest->AddObject(dial2);
	gbTest->AddObject(dial3);
	gbTest->AddObject(dial4);
	gbTest->AddObject(dial5);
	gbTest->AddObject(this->token1);
	gbTest->AddObject(this->token2);
	gbTest->AddObject(this->token3);
	gbTest->AddObject(this->token4);
	gbTest->AddObject(this->token5);
}

void DownfallBoardControl::SetInPlay(bool inPlay)
{
	
	this->inPlay = inPlay;
}

void DownfallBoardControl::SetMouseJoint(IGravityObject* gravObj)
{
	if(this->inPlay)
	{
		this->gbTest->SetMouseJoint(gravObj, dbMouseX(), dbMouseY());
	}
}

void DownfallBoardControl::DestroyMouseJoint()
{
	if(this->inPlay)
	{
		this->gbTest->DestroyMouseJoint();
	}
	if(TurnOver)
	{
		TurnOver();
	}
}

Dial* DownfallBoardControl::GetDial1()
{
	return this->dial1;
}
Dial* DownfallBoardControl::GetDial2()
{
	return this->dial2;
}
Dial* DownfallBoardControl::GetDial3()
{
	return this->dial3;
}
Dial* DownfallBoardControl::GetDial4()
{
	return this->dial4;
}
Dial* DownfallBoardControl::GetDial5()
{
	return this->dial5;
}
