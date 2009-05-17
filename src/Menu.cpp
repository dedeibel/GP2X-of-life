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

extern "C" {
	#include <SDL/SDL.h>
	#include <SDL/SDL_ttf.h>
}

#include "debug.h"
#include "Joystick.h"
#include "NumberDisplay.h"
#include "Game.h"

#include "Menu.h"

using namespace GP2XOfLife;

const unsigned int Menu::numberOfSaveslots = 6;

Menu::Menu(SDL_Surface *screen, Game &game, Joystick &input)
: selection(SPEED)
, screen(screen)
, game(game)
, input(input)
, rules(false)
, options(false)

, saveGame(false)
, loadGame(false)
, selectedSlot(1)
{
	background = SDL_LoadBMP("./img/MenuBackground.bmp");
	if (background == 0) {
		fatal("Could not load './img/MenuBackground.bmp'");
	}

	rulesImage = SDL_LoadBMP("./img/Rules.bmp");
	if (rulesImage == 0) {
		fatal("Could not load './img/Rules.bmp'");
	}

	optionsImage = SDL_LoadBMP("./img/Options.bmp");
	if (optionsImage == 0) {
		fatal("Could not load './img/Options.bmp'");
	}

	saveImage = SDL_LoadBMP("./img/SaveGame.bmp");
	if (saveImage == 0) {
		fatal("Could not load './img/SaveGmage.bmp'");
	}

	loadImage = SDL_LoadBMP("./img/LoadGame.bmp");
	if (loadImage == 0) {
		fatal("Could not load './img/LoadGame.bmp'");
	}

	speedImage = SDL_LoadBMP("./img/SpeedImage.bmp");
	if (speedImage == 0) {
		fatal("Could not load './img/SpeedImage.bmp'");
	}
	SDL_SetColorKey(speedImage, SDL_SRCCOLORKEY, SDL_MapRGB(background->format, 0, 0, 0xFF));

	sizeImage = SDL_LoadBMP("./img/SizeImage.bmp");
	if (sizeImage == 0) {
		fatal("Could not load './img/SizeImage.bmp'");
	}
	SDL_SetColorKey(sizeImage, SDL_SRCCOLORKEY, SDL_MapRGB(background->format, 0, 0, 0xFF));

	arrowImage = SDL_LoadBMP("./img/Arrow.bmp");
	if (arrowImage == 0) {
		fatal("Could not load './img/Arrow.bmp'");
	}
	SDL_SetColorKey(arrowImage, SDL_SRCCOLORKEY, SDL_MapRGB(background->format, 0, 0, 0xFF));
}

void Menu::draw()
{
	SDL_BlitSurface(background, 0, screen, 0);

	if (rules) {
		SDL_Rect pos;
		pos.x = 0;
		pos.y = 15;

		SDL_BlitSurface(rulesImage, 0, screen, &pos);
	}
	
	if (options) {
		if (loadGame) {
			drawLoadGame();
		}
		else if (saveGame) {
			drawSaveGame();
		}
		else {
			drawOptions();
		}
	}
}

void Menu::drawOptions()
{
	// Options Layer
	SDL_Rect pos;
	pos.x = screen->w - optionsImage->w;
	pos.y = 15;

	SDL_BlitSurface(optionsImage, 0, screen, &pos);

	// Display the speed 
	pos.x += 10;

	SDL_Rect dst;
	dst.x = pos.x + 65;
	dst.y = pos.y + 45;

	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.h = speedImage->h;
	src.w = (game.getSpeed() + 1) * 10;

	SDL_BlitSurface(speedImage, &src, screen, &dst);

	// Display the size
	dst.x = pos.x + 65;
	dst.y = pos.y + 65;

	src.x = 0;
	src.y = 0;
	src.h = speedImage->h;
	src.w = (game.getSize() + 1) * 10;

	SDL_BlitSurface(sizeImage, &src, screen, &dst);

	// Mark the current selection
	SDL_Rect mark;
	mark.x = pos.x - 3;
	mark.y = pos.y + 24 + selection * 20;

	SDL_BlitSurface(arrowImage, 0, screen, &mark);
}

void Menu::drawLoadGame()
{
	// Options Layer
	SDL_Rect pos;
	pos.x = screen->w - loadImage->w;
	pos.y = 15;

	SDL_BlitSurface(loadImage, 0, screen, &pos);

	// Mark the current selection
	SDL_Rect mark;
	mark.x = pos.x + 7;
	mark.y = pos.y + 24 + selectedSlot * 20;

	SDL_BlitSurface(arrowImage, 0, screen, &mark);
}

void Menu::drawSaveGame()
{
	// Options Layer
	SDL_Rect pos;
	pos.x = screen->w - saveImage->w;
	pos.y = 15;

	SDL_BlitSurface(saveImage, 0, screen, &pos);

	// Mark the current selection
	SDL_Rect mark;
	mark.x = pos.x + 7;
	mark.y = pos.y + 24 + selectedSlot * 20;

	SDL_BlitSurface(arrowImage, 0, screen, &mark);
}

void Menu::setRulesActive(bool active)
{
	rules = active;
}

void Menu::setOptionsActive(bool active)
{
	options = active;
}

bool Menu::isRulesActive() const
{
	return rules;
}

bool Menu::isOptionsActive() const
{
	return options;
}

void Menu::handleInput()
{
	if (loadGame) {
		handleLoadGameInput();
	}
	else if (saveGame) {
		handleSaveGameInput();
	}
	else {
		handleOptionsInput();
	}
}

void Menu::handleOptionsInput()
{
	// Directions
	
	if (input.isActive(Joystick::UP)) {
		if (--selection == FIRST_SELECTION) selection = LAST_SELECTION - 1;
	}
	else if (input.isActive(Joystick::DOWN)) {
		if (++selection == LAST_SELECTION) selection = SPEED;
	}
	else if (input.isActive(Joystick::RIGHT)) {
		if (selection == SPEED) {
			game.setSpeed(game.getSpeed() + 1);
		}
		else if (selection == SIZE) {
			game.setSize(game.getSize() + 1);
		}
	}
	else if (input.isActive(Joystick::LEFT)) {
		if (selection == SPEED) {
			if (game.getSpeed() != 0) {
				game.setSpeed(game.getSpeed() - 1);
			}
		}
		else if (selection == SIZE) {
			if (game.getSize() != 0) {
				game.setSize(game.getSize() - 1);
			}
		}
	}

	// Buttons

	if (input.isActive(Joystick::ACTIVATE)) {
		if (selection == CLEAR) {
			game.clear();
		}
		else if (selection == LOAD) {
			loadGame = true;
			selectedSlot = 1;
		}
		else if (selection == SAVE) {
			saveGame = true;
			selectedSlot = 1;
		}
		else if (selection == QUIT) {
			Game::quit();
		}
	}
	else if (input.isActive(Joystick::STEP)) {
		setOptionsActive(false);
	}
}

void Menu::handleSaveGameInput()
{
	// Directions
	
	if (input.isActive(Joystick::UP)) {
		if (--selectedSlot == 0) selectedSlot = numberOfSaveslots;
	}
	else if (input.isActive(Joystick::DOWN)) {
		if (++selectedSlot > numberOfSaveslots) selectedSlot = 1;
	}

	if (input.isActive(Joystick::STEP)) {
		saveGame = false;
	}

	if (input.isActive(Joystick::ACTIVATE)) {
		if (selectedSlot == numberOfSaveslots) {
			saveGame = false;
		}
		else {
			game.saveIntoSlot(selectedSlot);
		}
	}
}

void Menu::handleLoadGameInput()
{
	// Directions
	
	if (input.isActive(Joystick::UP)) {
		if (--selectedSlot == 0) selectedSlot = numberOfSaveslots;
	}
	else if (input.isActive(Joystick::DOWN)) {
		if (++selectedSlot > numberOfSaveslots) selectedSlot = 1;
	}

	if (input.isActive(Joystick::STEP)) {
		loadGame = false;
	}

	if (input.isActive(Joystick::ACTIVATE)) {
		if (selectedSlot == numberOfSaveslots) {
			loadGame = false;
		}
		else {
			game.loadFromSlot(selectedSlot);
		}
	}
}
