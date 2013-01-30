#include <Controls.h>

DownfallBoardPlayer::DownfallBoardPlayer(DownfallBoardControl* board) 
{
	this->board = board;
	this->board->GetDial1()->Pressed = boost::bind( &DownfallBoardPlayer::dial1_Pressed, this);
	this->board->GetDial1()->OutOfPress = boost::bind( &DownfallBoardPlayer::dial1_MouseUp, this);
	//------dial2-----------------------------------
	this->board->GetDial2()->Pressed = boost::bind( &DownfallBoardPlayer::dial2_Pressed, this);
	this->board->GetDial2()->OutOfPress = boost::bind( &DownfallBoardPlayer::dial2_MouseUp, this);
	//------dial3-----------------------------------
	this->board->GetDial3()->Pressed = boost::bind( &DownfallBoardPlayer::dial3_Pressed, this);
	this->board->GetDial3()->OutOfPress = boost::bind( &DownfallBoardPlayer::dial3_MouseUp, this);
	//------dial4-----------------------------------
	this->board->GetDial4()->Pressed = boost::bind( &DownfallBoardPlayer::dial4_Pressed, this);
	this->board->GetDial4()->OutOfPress = boost::bind( &DownfallBoardPlayer::dial4_MouseUp, this);
	//------dial5-----------------------------------
	this->board->GetDial5()->Pressed = boost::bind( &DownfallBoardPlayer::dial5_Pressed, this);
	this->board->GetDial5()->OutOfPress = boost::bind( &DownfallBoardPlayer::dial5_MouseUp, this);
	//----------------------------------------------
	this->board->TurnOver = boost::bind( &DownfallBoardPlayer::BoardTurnOver, this);
}

void DownfallBoardPlayer::Play()
{
	this->board->SetInPlay(true);
}

void DownfallBoardPlayer::BoardTurnOver()
{
	this->board->SetInPlay(false);
	this->otherPlayer->Play();
}

void DownfallBoardPlayer::SetOtherPlayer(IPlayer* otherPlayer)
{
	this->otherPlayer = otherPlayer;
}

void DownfallBoardPlayer::dial1_Pressed()
{
	this->board->SetMouseJoint(this->board->GetDial1());
}

void DownfallBoardPlayer::dial1_MouseUp()
{
	this->board->DestroyMouseJoint();
}

void DownfallBoardPlayer::dial2_Pressed()
{
	this->board->SetMouseJoint(this->board->GetDial2());
}

void DownfallBoardPlayer::dial2_MouseUp()
{
	this->board->DestroyMouseJoint();
}

void DownfallBoardPlayer::dial3_Pressed()
{
	
	this->board->SetMouseJoint(this->board->GetDial3());
}

void DownfallBoardPlayer::dial3_MouseUp()
{
	this->board->DestroyMouseJoint();
}

void DownfallBoardPlayer::dial4_Pressed()
{
	this->board->SetMouseJoint(this->board->GetDial4());
}

void DownfallBoardPlayer::dial4_MouseUp()
{
	this->board->DestroyMouseJoint();
}

void DownfallBoardPlayer::dial5_Pressed()
{
	this->board->SetMouseJoint(this->board->GetDial5());
}

void DownfallBoardPlayer::dial5_MouseUp()
{
	this->board->DestroyMouseJoint();
}
