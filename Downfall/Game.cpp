#include <Model.h>

Game::Game()
{
	this->state = Welcome;
}

GameState Game::GetState()
{
	return this->state;
}


//attach observers to be updated by this Game
void Game::Attach(IGameObserver* observer)
{
	this->observers.push_back(observer);
}

//Update the observers of this Game
void Game::Notify()
{
	list<IGameObserver*>::iterator i;
	for(i=this->observers.begin(); i != this->observers.end(); i++) 
	{
		(*i)->Update();
	}
}

void Game::SetState(GameState value)
{
	this->state = value;
	this->Notify();
}