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

#include <SDL/SDL.h>
#include "GPJoystick.h"
#include "GP2XMappings.h"

#include "debug.h"

using namespace GP2XOfLife;

GPJoystick::GPJoystick()
: Joystick::Joystick()
{
	SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	joystick = SDL_JoystickOpen(0);

	gpassert(joystick != 0);
}

GPJoystick::~GPJoystick()
{
	SDL_JoystickClose(joystick);
}


void GPJoystick::pollInput()
{
	SDL_Event event;

	Joystick::pollInput();

	while(SDL_PollEvent(&event)) {
    	switch(event.type)
		{
        /* Look for a keypress */
        case SDL_JOYBUTTONDOWN:
            /* Check the SDLKey values and move change the coords */
            switch(event.jbutton.button){
				// Movement
                case GP2X_BUTTON_UP:
					active[UP] = true;
                break;
                case GP2X_BUTTON_UPLEFT:
					active[UP_LEFT] = true;
                break;
                case GP2X_BUTTON_UPRIGHT:
					active[UP_RIGHT] = true;
                break;
                case GP2X_BUTTON_DOWN:
					active[DOWN] = true;
                break;
                case GP2X_BUTTON_DOWNLEFT:
					active[DOWN_LEFT] = true;
                break;
                case GP2X_BUTTON_DOWNRIGHT:
					active[DOWN_RIGHT] = true;
                break;
                case GP2X_BUTTON_LEFT:
					active[LEFT] = true;
                break;
                case GP2X_BUTTON_RIGHT:
					active[RIGHT] = true;
                break;

				// Buttons
				case GP2X_BUTTON_CLICK:
				case GP2X_BUTTON_X:
					active[STEP] = true;
				break;
				case GP2X_BUTTON_Y:
					active[MOVE_VIEW] = true;
				break;
				case GP2X_BUTTON_A:
					active[PAUSE] = true;
				break;
				case GP2X_BUTTON_B:
					active[ACTIVATE] = true;
				break;
				case GP2X_BUTTON_L:
					active[MENU_L] = true;
				break;
				case GP2X_BUTTON_R:
					active[MENU_R] = true;
				break;
				case GP2X_BUTTON_START:
					active[QUIT] = true;
				break;
                default:
					
                break;
            }
		break;
        case SDL_JOYBUTTONUP:
            switch(event.jbutton.button)
			{
                case GP2X_BUTTON_UP:
					active[UP] 		  = false;
					dirRequested[UP]  = 0;
					dirLastRepeat[UP] = 0;
                break;
                case GP2X_BUTTON_UPLEFT:
					active[UP_LEFT] 	   = false;
					dirRequested[UP_LEFT]  = 0;
					dirLastRepeat[UP_LEFT] = 0;
                break;
                case GP2X_BUTTON_UPRIGHT:
					active[UP_RIGHT]	    = false;
					dirRequested[UP_RIGHT]  = 0;
					dirLastRepeat[UP_RIGHT] = 0;
                break;
                case GP2X_BUTTON_DOWN:
					active[DOWN] 		= false;
					dirRequested[DOWN]  = 0;
					dirLastRepeat[DOWN] = 0;
                break;
                case GP2X_BUTTON_DOWNLEFT:
					active[DOWN_LEFT] 	   	 = false;
					dirRequested[DOWN_LEFT]  = 0;
					dirLastRepeat[DOWN_LEFT] = 0;
                break;
                case GP2X_BUTTON_DOWNRIGHT:
					active[DOWN_RIGHT]	      = false;
					dirRequested[DOWN_RIGHT]  = 0;
					dirLastRepeat[DOWN_RIGHT] = 0;
                break;
                case GP2X_BUTTON_LEFT:
					active[LEFT] 		= false;
					dirRequested[LEFT]  = 0;
					dirLastRepeat[LEFT] = 0;
                break;
                case GP2X_BUTTON_RIGHT:
					active[RIGHT] 		 = false;
					dirRequested[RIGHT]  = 0;
					dirLastRepeat[RIGHT] = 0;
                break;

				case GP2X_BUTTON_Y:
					active[MOVE_VIEW] = false;
				break;

				default:

				break;
			}
        }
    }
}

