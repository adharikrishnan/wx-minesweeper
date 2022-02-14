#pragma once
#include "wx/wx.h"
#include <wx/artprov.h>

class Game : public wxMDIParentFrame
{
public:
	Game();
	~Game();
public:
	// tile grid dimensions
	int h_tile_count = 10;
	int v_tile_count = 10;

	// mine array and a variable for the number of mine(for difficulty settings)
	int* mine_field = nullptr;
	int land_mines = 0;
	bool start_game = true;

	// 2d array of buttons for tile grid 
	wxButton** tiles;

	wxMenuBar* m_menu = nullptr;

	void menu_new_game(wxCommandEvent& event);

	void menu_easy(wxCommandEvent& event);
	void menu_normal(wxCommandEvent& event);
	void menu_hard(wxCommandEvent& event);
	
	void menu_exit(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();

	void first_press(wxCommandEvent& event);
	void reset_tiles();


};

