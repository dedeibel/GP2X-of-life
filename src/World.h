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

#ifndef _WORLD_H_
#define _WORLD_H_

#include "debug.h"

namespace GP2XOfLife
{

class World
{

// Attributes

public:
	enum EdgeMode {
		WRAP,
		DEAD
	};

private:

	// The current world and the world for the next step
	// For efficient border handling, the fields have one extra dead cell as border
	bool **newWorld;
	bool **currentWorld;

	EdgeMode edgeMode;

	Util::Vec2u size;
	unsigned int activeCells;

	Util::Vec2u min;
	Util::Vec2u max;

// Operations

public:
	World(const Util::Vec2u &size);
	~World();

	void step();
	
	void toggle(unsigned int x, unsigned int y)
	{
		gpassert(x < size.x);
		gpassert(y < size.y);
		++y;
		++x;

		if ( (currentWorld[y][x] = (!currentWorld[y][x])) ) {
			activeCells++;

			if (x <= min.x && x > 1) min.x = x - 1;
			if (x >= max.x && x < size.x) max.x = x + 1;
			if (y <= min.y && y > 1) min.y = y - 1;
			if (y >= max.y && y < size.y) max.y = y + 1;
		}
		else {
			activeCells--;
		}
	}

	void set(unsigned int x, unsigned int y, bool value)
	{
		gpassert(x < size.x);
		gpassert(y < size.y);
		++y;
		++x;

		if (!currentWorld[y][x] && value) {
			activeCells++;

			if (x <= min.x && x > 1) min.x = x - 1;
			if (x >= max.x && x < size.x) max.x = x + 1;
			if (y <= min.y && y > 1) min.y = y - 1;
			if (y >= max.y && y < size.y) max.y = y + 1;
		}
		else if (currentWorld[y][x] && !value) {
			activeCells--;
		}

		currentWorld[y][x] = value;

	}
	
	bool isAlive(unsigned int x, unsigned int y)
	{
		if (x >= size.x || y >= size.y) {
			return false;
		}

		return currentWorld[y + 1][x + 1];
	}

	void clearWorld();
	const Util::Vec2u center() const;
	const Util::Vec2u getCells() const;
	unsigned int getActiveCells() const;

	friend std::ostream &operator<<(std::ostream &os, const World &w);
	friend std::istream &operator>>(std::istream &os, World &w);

private:
	unsigned int neighbours(unsigned int xr, unsigned int yr);
	void switchWorlds();
	void randomize(unsigned int fract);

	void checkMinMax();
};

	std::ostream &operator<<(std::ostream &os, const World &w);
	std::istream &operator>>(std::istream &os, World &w);

};

#endif /* !_WORLD_H_ */

