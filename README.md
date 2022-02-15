# Wx-Minesweeper
A Minesweeper clone created with the WxWidgets GUI library. I understand it makes no sense to use a GUI library for a game, but it was more or less for learning purposes.
![Game](https://github.com/adharikrishnan/wx-minesweeper/blob/master/game.png)
# Overview 
The game uses buttons to represent a 10x10 tile grid representing the minefield. The starts at the first button pressed. If a tile (button) has mine on it and is clicked, it's a game over. If there is no mine on the tile, the number of mines surrounding that tile is displayed on it. There are three difficulty options, Easy, Normal and Hard, which affect the number of mines in the field. If you have played Minesweeper before, you'll feel right at home.
# Requirements
Win32 binaries are included for both debug and release configurations, so you can run the executables if you want to try out the game. 

If you are trying to build from source, [WxWidgets](https://www.wxwidgets.org/) is required ,along with Visual Studio (2019 or higher). WxWidgets also requires you to build the libraries from source before you can link to your project. There are no prebuilt libraries available. 

A faster approach would be to use [vcpkg](https://vcpkg.io/en/index.html) package manager. It's relatively easy to set up and the included JSON manifest file will take care of the dependencies. Beware, that files downloaded and built by vcpkg can be quite heavy.

# Updates and Expansions 
The game is still relatively basic and I have got a number of expansions and fixes planned for the future. On opening the game, the game defaults to Normal mode and the game must be restarted with the required difficulty. A separate menu would mostly likely streamline this. The difficulty settings can also be expanded on to include a larger or smaller ratio of tiles depending on the setting.

# Copyright 
#### &copy; Advaith Harikrishnan, 2020
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
