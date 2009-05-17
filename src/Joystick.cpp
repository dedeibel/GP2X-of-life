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
}

#include <cstring>

#include "Joystick.h"
#include "debug.h"

using namespace GP2XOfLife;

Joystick::Joystick()
: repeatDelay(150)
, repeatInterval(40)
{
	memset(dirRequested,  0, DIRECTIONS_END * sizeof(Uint32));
	memset(dirLastRepeat, 0, DIRECTIONS_END * sizeof(Uint32));

	memset(active, 0, LAST * sizeof(bool));
}

Joystick::~Joystick()
{

}

void Joystick::pollInput()
{
	clearButtons();
	// Yeah ... do something in the son classes
}

bool Joystick::isActive(Joystick::BUTTONS button)
{
	switch (button)
	{
		// Directions
		case UP:
		case UP_RIGHT:
		case RIGHT:
		case DOWN_RIGHT:
		case DOWN:
		case DOWN_LEFT:
		case LEFT:
		case UP_LEFT:
			if (active[button]) {
				Uint32 now = SDL_GetTicks();

				// It is the first time the button is requested
				if (dirRequested[button] == 0) {
					dirRequested[button] = now + repeatDelay;
					return true;
				}
				// If the button was requested before and the repeat delay is reached
				else if (now > dirRequested[button]) {
					// If the repeat delay was reached
					if (now > dirLastRepeat[button]) {
						dirLastRepeat[button] = now + repeatInterval;
						return true;
					}
				}
			}

			return false;
		break;

		// Hold buttons
		case MOVE_VIEW:
			if (active[button]) {
				return true;
			}
		break;
		
		// One press buttons
		case MENU_L:
		case MENU_R:
		case ACTIVATE:
		case PAUSE:
		case STEP:
		case QUIT:
			if (active[button]) {
				active[button] = false;
				return true;
			}
		break;
		case HOLD_END:
			error("HOLD_END is only a pseudo button, don't check it.");
		break;
		case DIRECTIONS_END:
			error("DIRECTIONS_END is only a pseudo button, don't check it.");
		break;
		case LAST:
			error("LAST is only a pseudo button, don't check it.");
		break;
	}

	return false;
}

void Joystick::setRepeatDelay(Uint32 delay)
{
	repeatDelay = delay;
}

void Joystick::setRepeatInterval(Uint32 interval)
{
	repeatInterval = interval;
}

Uint32 Joystick::getRepeatDelay() const
{
	return repeatDelay;
}

Uint32 Joystick::getRepeatInterval() const
{
	return repeatDelay;
}

void Joystick::clearButtons()
{
	for (unsigned int i = HOLD_END; i != LAST; ++i) {
		active[i] = false;
	}
}
