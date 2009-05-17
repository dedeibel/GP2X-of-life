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

#include <iostream>

extern "C" {
	#include <SDL/SDL.h>
	#include <SDL/SDL_ttf.h>
}

#include "debug.h"

#include "Util.h"
#include "World.h"
#include "WorldDisplay.h"
#include "NumberDisplay.h"
#include "Game.h"

using namespace GP2XOfLife;

int main(int argc, char** argv)
{
	debug("Creating Game.");

	Game game;

	debug("Entering Mainloop.");
	game.mainLoop();

	debug("Exiting.");

	exit(0);
}
