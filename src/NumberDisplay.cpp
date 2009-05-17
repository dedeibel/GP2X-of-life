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

#include <sstream>
#include "debug.h"
#include "NumberDisplay.h"

using namespace GP2XOfLife;

NumberDisplay::NumberDisplay(SDL_Surface *screen, const Util::Vec2u &destination)
: screen(screen)
, destination(destination)
, textSurface(0)
, prevAlive(0)
, prevTotal(0)
{
	if(TTF_Init() == -1) {
    	error("TTF_Init: %s", TTF_GetError());
	}

	font = TTF_OpenFont("font/VeraMono.ttf", 10);
	if(font == 0) {
    	error("TTF_OpenFont: %s", TTF_GetError());
		TTF_Quit();
	}

	color.r = 0;
	color.g = 0;
	color.b = 0;
}

NumberDisplay::~NumberDisplay()
{
	TTF_CloseFont(font);
	TTF_Quit();
}
	
void NumberDisplay::draw(unsigned int alive, unsigned int total)
{
	if (alive != prevAlive || total != prevTotal)
	{
		if (textSurface != 0) {
    		SDL_FreeSurface(textSurface);
			textSurface = 0;
		}

		std::ostringstream ss;
		ss.width(5);
		ss << alive << " of " << total;

		textSurface = TTF_RenderText_Solid(font, ss.str().c_str(), color);
		if (textSurface == 0) {
			error("TTF_RenderText_Solid: %s", TTF_GetError());
		}

		prevAlive = alive;
		prevTotal = total;
	}

	SDL_Rect dst;
	dst.x = destination.x;
	dst.y = destination.y;

	if (SDL_BlitSurface(textSurface, 0, screen, &dst) != 0) {
		error("Blitting textSurface to screen failed: %s", SDL_GetError());
	}
}
