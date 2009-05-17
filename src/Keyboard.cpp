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
#include "Keyboard.h"

#include "debug.h"

using namespace GP2XOfLife;

Keyboard::Keyboard()
: Joystick::Joystick()
{

}

Keyboard::~Keyboard()
{

}


void Keyboard::pollInput()
{
	SDL_Event event;

	Joystick::pollInput();

	while(SDL_PollEvent(&event)) {
    	switch(event.type)
		{
        /* Look for a keypress */
        case SDL_KEYDOWN:
            /* Check the SDLKey values and move change the coords */
            switch(event.key.keysym.sym){
                case SDLK_LEFT:
					active[LEFT] = true;
                break;
                case SDLK_RIGHT:
					active[RIGHT] = true;
                break;
                case SDLK_UP:
					active[UP] = true;
                break;
                case SDLK_DOWN:
					active[DOWN] = true;
                break;
				case SDLK_SPACE:
					active[ACTIVATE] = true;
				break;
				case SDLK_a:
					active[PAUSE] = true;
				break;
				case SDLK_l:
					active[MENU_L] = true;
				break;
				case SDLK_r:
					active[MENU_R] = true;
				break;
				case SDLK_s:
					active[STEP] = true;
				break;
				case SDLK_v:
					active[MOVE_VIEW] = true;
				break;
				case SDLK_q:
					active[QUIT] = true;
				break;
                default:
					
                break;
            }
		break;
        case SDL_KEYUP:
            switch(event.key.keysym.sym)
			{
                case SDLK_LEFT:
					active[LEFT]		= false;
					dirRequested[LEFT]  = 0;
					dirLastRepeat[LEFT] = 0;
                break;
                case SDLK_RIGHT:
					active[RIGHT] 		 = false;
					dirRequested[RIGHT]  = 0;
					dirLastRepeat[RIGHT] = 0;
                break;
                case SDLK_UP:
					active[UP] 		 = false;
					dirRequested[UP]  = 0;
					dirLastRepeat[UP] = 0;
                break;
                case SDLK_DOWN:
					active[DOWN] 		 = false;
					dirRequested[DOWN]  = 0;
					dirLastRepeat[DOWN] = 0;
                break;
				case SDLK_v:
					active[MOVE_VIEW] = false;
				break;

				default:

				break;
			}
        }
    }
}

