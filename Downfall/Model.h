#ifndef Model
#define Model

#include <list>
#include <Controls.h>

using namespace std;

enum GameState { Welcome, InPlay, GameOver };

enum WheelState { Free, Ready, Turning };

//The interface for a game observer
class IGameObserver
{
public:
	virtual void Update() = 0; 	
};

//TODO: TEST - The interface for a wheel observer
class IWheelObserver
{
public:
	virtual void UpdateWithWheelInfo() = 0; 
};

//The interface for a game subject
class IGameSubject
{
public:
	virtual void Attach(IGameObserver*) = 0;
	virtual void Notify() = 0;
};

//The interface for a wheel subject
class IWheelSubject
{
public:
	virtual void Attach(IWheelObserver*) = 0;
	virtual void Notify() = 0;
};

//Represents a Game
class Game : virtual public IGameSubject
{
private:
	GameState state;
	list<IGameObserver*> observers;
public:
	GameState GetState();
	void SetState(GameState);
	Game();
	virtual void Attach(IGameObserver*);
	virtual void Notify();
};


//TODO: Test class for a wheel
class Wheel : virtual public IWheelSubject
{
private:
	int angle;
	WheelState state;
	list<IWheelObserver*> observers;
public:
	int GetAngle();
	void SetAngle();
	Wheel();
	virtual void Attach(IWheelObserver*);
	virtual void Notify();
	WheelState GetState();
	void SetState();
	void SetAngle(int value);

};



#endif /* Model */