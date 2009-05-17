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

#ifndef _BOX_H_
#define _BOX_H_

extern "C" {
	#include <SDL/SDL.h>
}

namespace Util
{

template<class T>
class Box
{
public:
	Box()
	: x(0), y(0), w(0), h(0)
	{

	}

	Box(const T &x, const T &y, const T &w, const T &h)
	: x(x), y(y), w(w), h(h)
	{

	}

	~Box()
	{

	}

	operator SDL_Rect() const
	{
		SDL_Rect rect;
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
		return rect;
	}

public:
	T x;
	T y;
	T w;
	T h;

};

typedef Box<int> Boxi;
typedef Box<unsigned int> Boxu;
typedef Box<float> Boxf;
typedef Box<double> Boxd;
};

#endif /* !_VEC2_H_ */
