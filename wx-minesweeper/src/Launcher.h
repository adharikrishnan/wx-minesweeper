#pragma once

#include "wx/wx.h"
#include "Game.h" 

/*
	Launcher class that inherits form the wxApp class.
	This class will act as the launcher for the game and 
	invokes the main function.
*/
class Launcher : public wxApp
{
public:
	Launcher();
	~Launcher();
	virtual bool OnInit(); // OnInit function is required to create an actual window
private:
	Game* game_frame = nullptr; 

};

