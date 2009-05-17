/*
 * 
 * This file is part of GP2XOfLife.
 * 
 * GP2XOfLife is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * GP2XOfLife is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GP2XOfLife; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 * 
 * Copyright 2006 Benjamin Peter <BenjaminPeter@arcor.de>
 * 
 */

#ifndef _MENU_H_
#define _MENU_H_

namespace GP2XOfLife {
class Game;
class Joystick;

class Menu
{
private:
	enum MenuSelection {
		FIRST_SELECTION,
		SPEED,
		SIZE,
		CLEAR,
		LOAD,
		SAVE,
		QUIT,
		LAST_SELECTION
	};

	unsigned int selection;

	SDL_Surface* screen;

	SDL_Surface* background;
	SDL_Surface* rulesImage;
	SDL_Surface* optionsImage;
	SDL_Surface* loadImage;
	SDL_Surface* saveImage;
	SDL_Surface* speedImage;
	SDL_Surface* sizeImage;
	SDL_Surface* arrowImage;

	Game& game;
	Joystick& input;

	bool rules;
	bool options;

	bool saveGame;
	bool loadGame;
	unsigned int selectedSlot;

	static const unsigned int numberOfSaveslots;

public:
	Menu(SDL_Surface *screen, Game &game, Joystick &input);
	void draw();

	void setRulesActive(bool active);
	void setOptionsActive(bool active);
	bool isRulesActive() const;
	bool isOptionsActive() const;
	void handleInput();

private:
	void drawOptions();
	void drawLoadGame();
	void drawSaveGame();

	void handleOptionsInput();
	void handleLoadGameInput();
	void handleSaveGameInput();
};

};

#endif /* !_MENU_H_ */
