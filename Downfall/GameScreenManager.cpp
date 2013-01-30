#include <Display.h>

GameScreenManager::GameScreenManager(Game* myGame)
{
	this->myGame = myGame;
	this->currentScreen = new Start(this->myGame); //should not need to initialise the currentscreen
}

//Sets the current screen dependent on the state of the game
void GameScreenManager::Update()
{
	GameScreen* oldScreen = this->currentScreen;
	oldScreen->SetFreeze(true);
	switch(this->myGame->GetState())
	{
		case Welcome:
			this->currentScreen = new Start(this->myGame);
		break;
			
		case InPlay:
			this->currentScreen = new Play(this->myGame);
		break;
		
		case GameOver:
			this->currentScreen = new Over(this->myGame);
		break;
	}
	//We must load then unload the screen (rather than other way round)
	// because Dark GDK cannot handle deleting a sprite with the same number 
	// straight after you have created it.
	this->currentScreen->Initialise();	
	PlaySlideTransition(oldScreen);
	oldScreen->GetVisuals()->Delete();	
}
//Play an animation to slide the new(current) screen into place. 
void GameScreenManager::PlaySlideTransition(GameScreen* oldScreen)
{
	//TODO: This slide transition only works if the GameScreen top left is (0,0) it may not always be.
	GraphicsDB* g = GraphicsDB::GetInstance();
	int screenWidth = g->GetScreenWidth();
	//create a new visual item to hold both the current screen and old screen
	VisualItem* vItem = new VisualItem();
	vItem->SetTopLeft(new Point(-screenWidth, 0)); 
	//set top lefts relative to new parent container
	this->currentScreen->GetVisuals()->SetTopLeft(new Point(0,0));
	oldScreen->GetVisuals()->SetTopLeft(new Point(screenWidth,0));
	
	vItem->Add(this->currentScreen->GetVisuals());
	vItem->Add(oldScreen->GetVisuals());
	
	g->PlayMoveVisualItemAlongX(vItem, screenWidth);
}


GameScreen* GameScreenManager::GetCurrentScreen()
{
	if(this->currentScreen==0)
	{
		this->currentScreen = new Start(this->myGame);
	}
	return this->currentScreen;
}