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

#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

extern "C" {
	#include <SDL/SDL.h>
}

namespace GP2XOfLife
{

class Joystick
{
// Attributes

public:
	Joystick();
	~Joystick();

	enum BUTTONS {
		// Directions
		UP,
		UP_RIGHT,
		RIGHT,
		DOWN_RIGHT,
		DOWN,
		DOWN_LEFT,
		LEFT,
		UP_LEFT,

		DIRECTIONS_END, // Pseudo element

		// Hold buttons
		MOVE_VIEW,

		HOLD_END, // Pseudo element

		// One press buttons
		MENU_L,
		MENU_R,
		ACTIVATE,
		PAUSE,
		STEP,
		QUIT,

		LAST // Pseudo element
	};

protected:
	Uint32 dirRequested[DIRECTIONS_END];
	Uint32 dirLastRepeat[DIRECTIONS_END];

	bool   active[LAST];

private:
	Uint32 repeatDelay;
	Uint32 repeatInterval;

// Operations

public:
	void pollInput();

	bool isActive(Joystick::BUTTONS button);
	void setRepeatDelay(Uint32 delay);
	void setRepeatInterval(Uint32 interval);
	Uint32 getRepeatDelay() const;
	Uint32 getRepeatInterval() const;

protected:
	void clearButtons();
};

};

#endif /* !_JOYSTICK_H_ */
