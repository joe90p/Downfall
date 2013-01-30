#include <DarkGDK.h>
#include <Controls.h>
#include <Model.h>
#include <DarkDraw.h>
#include <Display.h>


const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;

void InitialiseDarkGDK();

void DarkGDK ( void )
{
	InitialiseDarkGDK();
	//Initisalise the GraphicsDB singleton
	GraphicsDB::GetInstance()->Initilaise(SCREEN_WIDTH, SCREEN_HEIGHT);
	//get a new Game and use it to instantiate a ScreenManager
	Game* myGame = new Game();	
	GameScreenManager* sManager = new GameScreenManager(myGame);	
	//attach ScreenManager as an observer of game
	// and set the initial game state
	myGame->Attach(sManager);
	myGame->SetState(Welcome);
	
	
	while ( LoopGDK ( ) )
	{
		sManager->GetCurrentScreen()->Update();
		dbSync();		
	}	
	// return back to windows
	return;
}


void InitialiseDarkGDK()
{
	dbSetDisplayMode(SCREEN_WIDTH,SCREEN_HEIGHT,32);
	dbSetImageColorKey(255,0,255);	
	// Turn on fullscreen mode
	dbSetWindowLayout(0, 0, 1);
	dbMaximizeWindow();
	// turn on sync rate and set maximum rate to 60 fps
	dbSyncOn  ( );
	dbSyncRate ( 60 );
}