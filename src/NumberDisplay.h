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

#ifndef _NUMBERDISPLAY_H_
#define _NUMBERDISPLAY_H_

#include "Util.h"

namespace GP2XOfLife {

class NumberDisplay
{
// Attributes
private:
	TTF_Font *font;
	SDL_Color color;
	SDL_Surface *screen;
	Util::Vec2u destination;
	SDL_Surface *textSurface;


	unsigned int prevAlive;
	unsigned int prevTotal;
	
// Operations
public:
	NumberDisplay(SDL_Surface *screen, const Util::Vec2u &destination);
	~NumberDisplay();

	void draw(unsigned int alive, unsigned int total);
};

};

#endif /* !_NUMBERDISPLAY_H_ */
