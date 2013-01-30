#include <Display.h>

GameScreen::GameScreen(Game* myGame) : Control(0,0)
{
	IShape* clientArea;
	GraphicsDB* g = GraphicsDB::GetInstance();
	this->myGame = myGame;
	this->freeze = false;
	clientArea = new Oblong(g->GetScreenWidth(), g->GetScreenHeight());
	
	this->SetVisuals(new VisualItem());
	this->GetVisuals()->SetTopLeft(new Point(0,0));	
	this->SetClientArea(clientArea);
}

//TODO: Would be nice to use the parent Control.Update method instead of overriding
void GameScreen::Update()
{
	GameState initialState = this->myGame->GetState();
	if(!this->freeze)
	{
		list<Control*>::iterator i;
		for(i=this->controls.begin(); i != this->controls.end(); i++) 
		{
			(*i)->Update();
			//TODO: the game change check could be a bit nicer. ie do it a different way.
			if(initialState!=this->myGame->GetState())
			{
				break;
			}
		}
	}
}


void GameScreen::SetFreeze(bool freeze)
{
	this->freeze = freeze;
}

Game* GameScreen::GetMyGame()
{
	return this->myGame;
}

