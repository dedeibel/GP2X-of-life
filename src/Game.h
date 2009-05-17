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

#ifndef _GAME_H_
#define _GAME_H_

#ifdef TARGET_GP2X
	#include "GPJoystick.h"
#else
	#include "Keyboard.h"
#endif

#include "Util.h"

namespace GP2XOfLife
{
class WorldDisplay;
class Menu;
class NumberDisplay;

class Game
{
// Attributes

private:
	WorldDisplay *worldDisplay;
	Menu *menu;
	NumberDisplay *numberDisplay;

	SDL_Surface *screen;
#ifdef TARGET_GP2X
	GPJoystick input;
#else
	Keyboard input;
#endif
	bool moveView;

	unsigned int fpsInterval;
	Uint32 nextTime;
	unsigned int worldSize;

	static const Util::Vec2u cellSizes[];
	static const unsigned int numCellSizes;
	static const unsigned int maxSpeed;


// Operations:

public:
	Game();
	~Game();

	void mainLoop();
	static void quit();

	unsigned int getSpeed() const;
	bool setSpeed(unsigned int speed);

	unsigned int getSize() const;
	bool setSize(unsigned int size);

	void clear();

	bool saveIntoSlot(unsigned int slot);
	bool loadFromSlot(unsigned int slot);

private:
	Uint32 timeLeft();
	void handleInput();
};

};

#endif /* !_GAME_H_ */
