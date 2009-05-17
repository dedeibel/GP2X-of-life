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

#include <ctime>
#include <cstring>
#include <cstdlib>

#include "debug.h"
#include "Util.h"
#include "World.h"

using namespace GP2XOfLife;

World::World(const Util::Vec2u &size)
: newWorld(0)
, currentWorld(0)
, edgeMode(DEAD)
, size(size)
, activeCells(0)
, min(Util::Vec2u(size.x / 2, size.y / 2))
, max(Util::Vec2u(size.x / 2, size.y / 2))
{
	// Create the cells
	
	currentWorld = new bool*[size.y + 2];
	newWorld     = new bool*[size.y + 2];

	// For each row including the border
	for (unsigned int i = 0; i < size.y + 2; ++i) {
		currentWorld[i] = new bool[size.x + 2];
		newWorld[i]     = new bool[size.x + 2];

		memset(currentWorld[i], 0, (size.x + 2) * sizeof(bool));
		memset(newWorld[i],     0, (size.x + 2) * sizeof(bool));
	}
}

World::~World()
{
	for (unsigned int i = 0; i < size.y + 2; ++i) {
		delete[] currentWorld[i];
		delete[] newWorld[i];
	}

	delete[] currentWorld;
	delete[] newWorld;
}

void World::step()
{
	unsigned int nb;
	activeCells = 0;

	Util::Vec2u newMax = max;
	Util::Vec2u newMin = min;

	// debug("Min (%u,%u) Max (%u,%u)", min.x, min.y, max.x, max.y);

	/*
	 * Step goes from 1 to size.y + 1 because the world has actually a
	 * 1 cell border to make the handling easier
	 */
	for (unsigned int y = min.y; y <= max.y; ++y)
	{
		// Same here, 1 cell border
		for (unsigned int x = min.x; x <= max.x; ++x)
		{
			nb = neighbours(x, y);

			// If it's a living cell
			if (currentWorld[y][x]) {
				// If it has enough nbs, stay alive
				if (nb == 2 || nb == 3) {
					newWorld[y][x] = true;
					activeCells++;

					if (x <= newMin.x && x > 1) newMin.x = x - 1;
					if (x >= newMax.x && x < size.x) newMax.x = x + 1;
					if (y <= newMin.y && y > 1) newMin.y = y - 1;
					if (y >= newMax.y && y < size.y) newMax.y = y + 1;
				}
			}
			// If it is dead and has anough nbs, come to live
			else if (nb == 3) {
				newWorld[y][x] = true;
				activeCells++;

				if (x <= newMin.x && x > 1) newMin.x = x - 1;
				if (x >= newMax.x && x < size.x) newMax.x = x + 1;
				if (y <= newMin.y && y > 1) newMin.y = y - 1;
				if (y >= newMax.y && y < size.y) newMax.y = y + 1;
			}
		}
	}

	// Kill all cells
	for (unsigned int i = 0; i < size.y + 2; ++i) {
		memset(currentWorld[i], 0, (size.x + 2) * sizeof(bool));
	}

	min = newMin;
	max = newMax;

	switchWorlds();
}

inline unsigned int World::neighbours(unsigned int xr, unsigned int yr)
{
	unsigned int count = 0;

	if (currentWorld[yr - 1][xr - 1]) ++count;
	if (currentWorld[yr - 1][xr    ]) ++count;
	if (currentWorld[yr - 1][xr + 1]) ++count;

	if (currentWorld[yr    ][xr - 1]) ++count;
	if (currentWorld[yr    ][xr + 1]) ++count;

	if (currentWorld[yr + 1][xr - 1]) ++count;
	if (currentWorld[yr + 1][xr    ]) ++count;
	if (currentWorld[yr + 1][xr + 1]) ++count;

	return count;
}

void World::clearWorld()
{
	min = Util::Vec2u(size.x / 2, size.y / 2);
	max = Util::Vec2u(size.x / 2, size.y / 2);

	// Kill all cells
	for (unsigned int i = 0; i < size.y + 2; ++i) {
		memset(currentWorld[i], 0, (size.x + 2) * sizeof(bool));
		memset(newWorld[i], 0, (size.x + 2) * sizeof(bool));
	}

	activeCells = 0;
}

void World::switchWorlds()
{
	bool **tmp   = currentWorld;
	currentWorld = newWorld;
	newWorld     = tmp;
}

void World::randomize(unsigned int fract)
{
	unsigned int fields = size.x * size.y / fract;

	srand(time(0));
	clearWorld();

	while (--fields) {
		currentWorld[rand() % size.y + 1][rand() % size.x + 1] = true;
	}

	checkMinMax();
}

const Util::Vec2u World::center() const
{
	return Util::Vec2u(size.x / 2, size.y / 2);
}

const Util::Vec2u World::getCells() const
{
	return size;
}

unsigned int World::getActiveCells() const
{
	return activeCells;
}

void World::checkMinMax()
{
	min = Util::Vec2u(size.x / 2, size.y / 2);
	max = Util::Vec2u(size.x / 2, size.y / 2);

	for (unsigned int y = 1; y < size.y + 1; ++y) {
		for (unsigned int x = 1; x < size.x + 1; ++x) {
			if (currentWorld[y][x]) {
				if (x <= min.x && x > 1) min.x = x - 1;
				if (x >= max.x && x < size.x) max.x = x + 1;
				if (y <= min.y && y > 1) min.y = y - 1;
				if (y >= max.y && y < size.y) max.y = y + 1;
			}
		}
	}
}

std::istream &GP2XOfLife::operator>>(std::istream &is, World &w)
{
	Util::Vec2u s = Util::Vec2u();
	char c = 0;

	is >> s;

	if (is.bad()) {
		debug("Could not read the dimensions");
		return is;
	}

	if (s.x < 25 || s.y < 25) {
		is.clear(std::ios_base::badbit);
		error("Please choose a fieldsize bigger than 25x25.");
	}

	// If the size of the world has changed
	if (s != w.size) {
		debug("The size of the world has changed");

		unsigned int cells = 0;

		bool **buff1 = new bool*[s.y + 2];
		bool **buff2 = new bool*[s.y + 2];

		// For each row, including the borders
		for (unsigned int y = 0; y < s.y + 2; ++y) {
			buff1[y] = new bool[s.x + 2];
			buff2[y] = new bool[s.x + 2];

			memset(buff1[y], 0, (s.x + 2) * sizeof(bool));
			memset(buff2[y], 0, (s.x + 2) * sizeof(bool));
		}
			
		// For each row
		for (unsigned int y = 1; y < s.y + 1; ++y)
		{
			for (unsigned int x = 1; x < s.x + 1; ++x) {
				is >> c;

				// If the end of the file comes before all cells are read
				if (!is) {
					debug("The file ended earlier than expected");
					is.clear(std::ios_base::badbit);
				}

				if (c == 'x') {
					buff1[y][x] = true;
					cells++;
				}
				else if (c == '.') {
					buff1[y][x] = false;
				}
				else {
					debug("Unknown character read '%c'", c);
					is.clear(std::ios_base::badbit);
				}
			}
		}

		// Read over the last newline
		is >> c;

		// If everything went fine
		if (!is.bad() && is.eof())
		{
			debug("Reading went fine");
			// delete the original buffer and replace it
			for (unsigned int y = 0; y < w.size.y + 2; ++y) {
				delete[] w.currentWorld[y];
				delete[] w.newWorld[y];
			}

			delete[] w.currentWorld;
			delete[] w.newWorld;

			w.currentWorld = buff1;
			w.newWorld     = buff2;
			
			w.activeCells  = cells;
			w.size		   = s;
		}
		else {
			debug("There was a problem while reading the file, maybe trailing characters");

			is.clear(std::ios_base::badbit);

			// Destroy the temporary buffer
			for (unsigned int y = 0; y < s.y + 2; ++y) {
				delete[] buff1[y];
				delete[] buff2[y];
			}

			delete[] buff1;
			delete[] buff2;
		}
	}
	// If the size hasn't changed
	else {
		debug("The size of the world has not changed");

		// For each row
		for (unsigned int y = 1; y < s.y + 1; ++y)
		{
			for (unsigned int x = 1; x < s.x + 1; ++x) {
				is >> c;

				// If the end of the file comes before all cells are read
				if (!is) {
					debug("The file ended earlier than expected");
					is.clear(std::ios_base::badbit);
				}
				
				if (c == 'x') {
					w.currentWorld[y][x] = true;
					w.activeCells++;
				}
				else if (c == '.') {
					w.currentWorld[y][x] = false;
				}
				else {
					debug("Unknown character read '%c'", c);
					is.clear(std::ios_base::badbit);
				}
			}
		}

		// Read over the last newline
		is >> c;

		// If everything went fine
		if (!is.bad() && is.eof()) {
			debug("Reading went fine");
			w.size = s;
		}
		else {
			debug("There was a problem while reading the file, maybe trailing characters");
			is.clear(std::ios_base::badbit);
			w.clearWorld();
		}
	}

	w.checkMinMax();
	return is;
}

std::ostream &GP2XOfLife::operator<<(std::ostream &os, const World &w)
{
	os << w.size << std::endl;
	for (unsigned int y = 1; y < w.size.y + 1; ++y) {
		for (unsigned int x = 1; x < w.size.x + 1; ++x) {
			// 'x' and '.' are better readable
			os << ((w.currentWorld[y][x]) ? 'x' : '.');
		}
		os << std::endl;
	}

	return os;
}


