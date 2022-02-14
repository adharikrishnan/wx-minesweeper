#include "Launcher.h"

wxIMPLEMENT_APP(Launcher);

Launcher::Launcher()
{

}

Launcher::~Launcher()
{

}

/*
Main Game Launcher
Uses the game class to create the instance and launches it
Launcher inherits from wxApp.

*/

bool Launcher::OnInit()
{
	game_frame = new Game();
	game_frame->Show();

	return true;
}

