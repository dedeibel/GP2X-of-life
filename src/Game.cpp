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

#include <sstream>
#include <fstream>
#include <iostream>

extern "C" {
	#include <SDL/SDL.h>
	#include <SDL/SDL_ttf.h>

	#include <sys/time.h>
}

#include <ctime>
#include "Runtime.h"

#include "debug.h"
#include "Keyboard.h"
#include "Menu.h"
#include "Util.h"
#include "World.h"
#include "NumberDisplay.h"
#include "WorldDisplay.h"

#include "Game.h"

using namespace GP2XOfLife;

const Util::Vec2u Game::cellSizes[] = {
	Util::Vec2u(8, 8),
	Util::Vec2u(5, 5),
	Util::Vec2u(4, 4),
	Util::Vec2u(3, 3)
};

const unsigned int Game::numCellSizes = 4;
const unsigned int Game::maxSpeed = 4;

Game::Game() 
: worldDisplay(0)
, menu(0)
, screen(0)
, fpsInterval(60)
, nextTime(0)
, worldSize(1)
{
    /* Initialize the SDL library */
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr,
                "Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    /* Clean up on exit */
    atexit(SDL_Quit);
    
    /*
     * Initialize the display in a 640x480 16-bit palettized mode,
     * requesting a software surface
     */
    screen = SDL_SetVideoMode(320, 240, 16, SDL_SWSURFACE);
    if ( screen == NULL ) {
        fprintf(stderr, "Couldn't set 640x480x16 video mode: %s\n",
                        SDL_GetError());
        exit(1);
    }

	SDL_ShowCursor(SDL_DISABLE);

	worldDisplay  = new WorldDisplay(screen, Util::Boxu(0, 20, 320, 220), Util::Vec2u(300, 250));
	menu 		  = new Menu(screen, *this, input);
	numberDisplay = new NumberDisplay(screen, Util::Vec2u(115, 3));
}

Game::~Game()
{
	delete worldDisplay;
	delete menu;
	delete numberDisplay;
}

void Game::mainLoop()
{
#ifdef DEBUG
	static unsigned int frames = 0;
	static unsigned int next   = 0;
#endif

	worldDisplay->setPause(true);
	loadFromSlot(1);

	while (true) {
		handleInput();

		worldDisplay->draw();

		menu->draw();
#ifdef TARGET_GP2X
		numberDisplay->draw(worldDisplay->getActiveCells(), worldDisplay->getTotalCells());
#endif

    	SDL_Flip(screen);

		SDL_Delay(timeLeft());

#ifdef DEBUG
		frames++;
		Uint32 now = SDL_GetTicks();
		if (now >= next) {
			debug("FPS: %u", frames);
			next = now + 1000;
			frames = 0;
		}
#endif
	}
}

Uint32 Game::timeLeft()
{
    Uint32 now;

    now = SDL_GetTicks();
    if (now >= nextTime) {
        nextTime = now + fpsInterval;
        return 0;
    }

    return nextTime - now;
}

void Game::handleInput()
{
	// Update the input information
	input.pollInput();

	// If the menu is active, let it pick it's controls first
	if (menu->isOptionsActive()) {
		menu->handleInput();

		if (input.isActive(Joystick::MENU_L)) {
			menu->setRulesActive(!menu->isRulesActive());
		}
		if (input.isActive(Joystick::MENU_R)) {
			menu->setOptionsActive(!menu->isOptionsActive());
		}
		if (input.isActive(Joystick::PAUSE)) {
			worldDisplay->setPause(!worldDisplay->isPaused());
		}
		if (input.isActive(Joystick::STEP)) {
			worldDisplay->step();
		}
		if (input.isActive(Joystick::QUIT)) {
			quit();
		}

		return;
	}

	// Handle what is left
	moveView = false;

	if (input.isActive(Joystick::MOVE_VIEW)) {
		moveView = true;
	}

	if (input.isActive(Joystick::UP_LEFT)) {
		if (moveView) {
			worldDisplay->moveView(Util::Vec2i(-1, -1));
		}
		else {
			worldDisplay->moveCursor(Util::Vec2i(-1, -1));
		}
	}
	else if (input.isActive(Joystick::UP)) {
		if (moveView) {
			worldDisplay->moveView(Util::Vec2i(0, -1));
		}
		else {
			worldDisplay->moveCursor(Util::Vec2i(0, -1));
		}
	}
	else if (input.isActive(Joystick::UP_RIGHT)) {
		if (moveView) {
			worldDisplay->moveView(Util::Vec2i(1, -1));
		}
		else {
			worldDisplay->moveCursor(Util::Vec2i(1, -1));
		}
	}
	else if (input.isActive(Joystick::RIGHT)) {
		if (moveView) {
			worldDisplay->moveView(Util::Vec2i(1, 0));
		}
		else {
			worldDisplay->moveCursor(Util::Vec2i(1, 0));
		}
	}
	else if (input.isActive(Joystick::DOWN_RIGHT)) {
		if (moveView) {
			worldDisplay->moveView(Util::Vec2i(1, 1));
		}
		else {
			worldDisplay->moveCursor(Util::Vec2i(1, 1));
		}
	}
	else if (input.isActive(Joystick::DOWN)) {
		if (moveView) {
			worldDisplay->moveView(Util::Vec2i(0, 1));
		}
		else {
			worldDisplay->moveCursor(Util::Vec2i(0, 1));
		}
	}
	else if (input.isActive(Joystick::DOWN_LEFT)) {
		if (moveView) {
			worldDisplay->moveView(Util::Vec2i(-1, 1));
		}
		else {
			worldDisplay->moveCursor(Util::Vec2i(-1, 1));
		}
	}
	else if (input.isActive(Joystick::LEFT)) {
		if (moveView) {
			worldDisplay->moveView(Util::Vec2i(-1, 0));
		}
		else {
			worldDisplay->moveCursor(Util::Vec2i(-1, 0));
		}
	}

	if (input.isActive(Joystick::MENU_L)) {
		menu->setRulesActive(!menu->isRulesActive());
	}
	
	if (input.isActive(Joystick::MENU_R)) {
		menu->setOptionsActive(!menu->isOptionsActive());
	}

	if (input.isActive(Joystick::ACTIVATE)) {
		worldDisplay->toggleCell();
	}
	if (input.isActive(Joystick::PAUSE)) {
		worldDisplay->setPause(!worldDisplay->isPaused());
	}
	if (input.isActive(Joystick::STEP)) {
		worldDisplay->step();
	}
	if (input.isActive(Joystick::QUIT)) {
		quit();
	}
}

unsigned int Game::getSpeed() const
{
	return 400 / worldDisplay->getInterval() - 1;
}

bool Game::setSpeed(unsigned int speed)
{
	if (speed > maxSpeed) {
		return false;
	}

	worldDisplay->setInterval(400 / (speed + 1));

	return true;
}

unsigned int Game::getSize() const
{
	return worldSize;
}

bool Game::setSize(unsigned int size)
{
	if (size >= numCellSizes) {
		return false;
	}

	if (worldDisplay->setCellWidth(cellSizes[size])) {
		worldSize = size;
		return true;
	}

	return false;
}

void Game::clear()
{
	worldDisplay->clear();
}

bool Game::saveIntoSlot(unsigned int slot)
{
	std::stringstream ss;
	ss << "saves/savegame" << slot << ".sav";

	std::ofstream of(ss.str().c_str());
	if (!of) {
		error("Could not open file '%s' for writing.", ss.str().c_str());
		return false;
	}

	debug("Saving world to file %s", ss.str().c_str());

	of << *worldDisplay;

	if (of.bad()) {
		error("There was an error while writing to file '%s'.", ss.str().c_str());
		return false;
	}

	return true;
}

bool Game::loadFromSlot(unsigned int slot)
{
	std::stringstream ss;
	ss << "saves/savegame" << slot << ".sav";

	std::ifstream in(ss.str().c_str());
	if (!in) {
		error("Could not open file '%s' for reading.", ss.str().c_str());
		return false;
	}

	debug("Loading world from file %s", ss.str().c_str());

	in >> *worldDisplay;

	if (in.bad()) {
		error("There was an error while reading from file '%s'.", ss.str().c_str());
		return false;
	}

	return true;
}

void Game::quit()
{
	SDL_Quit();

#ifdef TARGET_GP2X
	chdir("/usr/gp2x");
	execl("/usr/gp2x/gp2xmenu", "/usr/gp2x/gp2xmenu", NULL);
#else
	exit(0);
#endif
}
