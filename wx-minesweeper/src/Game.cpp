#include "Game.h"
#include <algorithm>

wxBEGIN_EVENT_TABLE(Game, wxMDIParentFrame) 
EVT_MENU(201, Game::menu_exit) // for main menu exit 

EVT_MENU(300, Game::menu_easy) // for the difficulty submenu
EVT_MENU(301, Game::menu_normal)
EVT_MENU(302, Game::menu_hard)
wxEND_EVENT_TABLE()


Game::Game() : wxMDIParentFrame(nullptr, wxID_ANY, "WXMinesweeper", wxPoint(30, 30), wxSize(800, 600))
{
	/*
	  The constructor creates the array of buttons in Row-major order for contiguous memory allocation for faster insertions and access.
	  The array objects are then passed to the grid sizer to create a grid of buttons that will act as the tiles for the game.
      The minefield array is also created and the elements are all initialized to zero.
	  The buttons are also binded to the main game function(first_press)
	*/
	tiles = new wxButton * [h_tile_count * v_tile_count];
	wxGridSizer* tile_grid = new wxGridSizer(v_tile_count, h_tile_count, 0, 0);
	wxFont countFont(28, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
	mine_field = new int[h_tile_count * v_tile_count]{};

	for (int x = 0; x < v_tile_count; x++)
	{
		for (int y = 0; y < h_tile_count; y++)
		{
			tiles[y * v_tile_count + x] = new wxButton(this, 10000 + (y * v_tile_count + x));
			tiles[y * v_tile_count + x]->SetFont(countFont);
			tile_grid->Add(tiles[y * v_tile_count + x], 1, wxEXPAND | wxALL);

			tiles[y * v_tile_count + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Game::first_press, this);

		}
	}

	this->SetSizer(tile_grid);
	tile_grid->Layout();

	// Creates menu bar and drop-down menu for game options 
	// Submenus are used for difficulty options(temporary solution)
	m_menu = new wxMenuBar();
	this->SetMenuBar(m_menu);
	wxMenu* m_options = new wxMenu();

	wxMenu* new_game = new wxMenu();
	wxMenu* difficulty_set = new wxMenu();
	difficulty_set->Append(300, "Easy");
	difficulty_set->Append(301, "Medium");
	difficulty_set->Append(302, "Hard");

	new_game->AppendSubMenu(difficulty_set, "Difficulty");
	m_options->AppendSubMenu(new_game, "New Game");

	m_options->AppendSeparator();

	wxMenuItem* exit_item = new wxMenuItem(m_options, 201, "Exit");
	exit_item->SetBitmap(wxArtProvider::GetBitmap("wxART_QUIT"));
	m_options->Append(exit_item);


	m_menu->Append(m_options, "Options");
}

// clean up
Game::~Game()
{
	delete[]tiles;
	delete[]mine_field;
}

// resets all the tiles(buttons) and in turn the game 
void Game::reset_tiles()
{
	start_game = true;
	land_mines = 0;
	std::fill(mine_field, mine_field + 100, 0);

	for (int x = 0; x < v_tile_count; x++)
	{
		for (int y = 0; y < h_tile_count; y++)
		{

			tiles[y * v_tile_count + x]->SetLabel("");
			tiles[y * v_tile_count + x]->Enable(true);

		}
	}
}

// difficulty set command event functions
void Game::menu_new_game(wxCommandEvent& event)
{
	reset_tiles();
	event.Skip();

}

void Game::menu_easy(wxCommandEvent& event)
{	
	reset_tiles();
	land_mines = 15;
	event.Skip();
}

void Game::menu_normal(wxCommandEvent& event)
{
	reset_tiles();
	land_mines = 25;
	event.Skip();
}

void Game::menu_hard(wxCommandEvent& event)
{
	reset_tiles();
	land_mines = 35;
	event.Skip();
}

// for exit option in drop-down menu
void Game::menu_exit(wxCommandEvent& event)
{
	Close();
	event.Skip();
}

// main game function activated when a button is pressed
void Game::first_press(wxCommandEvent& event)
{
	// Translates the button's ID to more approximate coordiantes 
	int x = (event.GetId() - 10000) % v_tile_count;
	int y = (event.GetId() - 10000) / v_tile_count;

	 // defaults the game to normal mode
	if (land_mines == NULL) { land_mines = 25; }

	/*
	First button cannot be a mine, so the first button pressed 
	is used as a trigger to the land mines in the field.
	The mine_field array is then used as a figurative reference to the array of buttons  
	to check if any button pressed afterwards has a mine on it.
	*/
	if (start_game)
	{
		while (land_mines)
		{
			int rx = rand() % v_tile_count;
			int ry = rand() % h_tile_count;

			if (mine_field[ry * v_tile_count + rx] == 0 && rx != x && ry != y)
			{
				mine_field[ry * v_tile_count + rx] = -1;
				land_mines--;
			}

			// to signal the start of the game. Important for resets.
			start_game = false;
		}
	}
	// disables the button after it has clicked
	tiles[y * v_tile_count + x]->Enable(false);

	// fail condition when a mine has been pressed
	if (mine_field[y * v_tile_count + x] == -1)
	{
		wxMessageBox("Game Over");
		reset_tiles();
	}

	// using a count variable to count the number of mine surrounding the 
	// button pressed(the button is not a mine) and displaying the count on that tile
	else
	{
		int mine_count = 0;

		for (int a = -1; a < 2; a++)
		{
			for (int b = -1; b < 2; b++)
			{
				if (x + a >= 0 && x + a < v_tile_count && y + b >= 0 && y + b < h_tile_count)
				{
					if (mine_field[(y + b) * v_tile_count + (x + a)] == -1)
					{
						mine_count++;
					}
				}
			}
		}

		if (mine_count > 0)
		{
			tiles[y * v_tile_count + x]->SetLabel(std::to_string(mine_count));
		}
	}

	// skips event hierachy to speed things up.
	event.Skip();

}

