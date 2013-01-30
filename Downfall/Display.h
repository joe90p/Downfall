#ifndef Display
#define Display

#include <Model.h>
#include <Controls.h>
#include <list>
using namespace std;

//A screen which can be used to refelct and change the state of a Game
class GameScreen : public Control
{
private:
	Game* myGame;
	bool freeze;
protected:
	Game* GetMyGame();
public:
	GameScreen(Game*);
	void Update();
	void SetFreeze(bool);
	virtual void Initialise() = 0;
	
};

//The start/welcome screen for our game
class Start : public GameScreen
{
private:
	Button* btTest;
	Button* btTest2;
	GravityBox* gbTest;
	DownfallBoardControl* boardControl;
	DownfallBoardControl* mirroredBoardControl;
	DownfallBoardPlayer* player1;
	DownfallBoardPlayer* player2;
	void btTest_Clicked();
	void btTest2_Clicked();
	
public:
	void Initialise();
	Start(Game*);
	
};

//The "In Play" screen for our game
class Play : public GameScreen
{
private:
	Button* btTest;
	GravityBox* gbTest;
	void btTest_Clicked();
	void UpdateWithWheelInfo();
public:
	void Initialise();
	Play(Game*);
};
//The game over screen
class Over : public GameScreen
{
private:
	Button* btTest;
	void btTest_Clicked();
public:
	void Initialise();
	Over(Game*);
};

//Manages the screen to display by observing the state of a Game
class GameScreenManager : public IGameObserver 
{
private:
	Game* myGame;
	GameScreen* currentScreen;
	void PlaySlideTransition(GameScreen*);
public:
	GameScreenManager(Game*);
	void Update();
	GameScreen* GetCurrentScreen();
};

#endif /* Display */