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
}

#include <ctime>
#include "Runtime.h"

#include "debug.h"
#include "Util.h"
#include "World.h"

#include "WorldDisplay.h"

using namespace GP2XOfLife;

WorldDisplay::WorldDisplay(
	SDL_Surface *screen,
	const Util::Boxu dimension,
	const Util::Vec2u worldSize
)
: screen(screen)
, dim(dimension)
, cellWidth(5, 5)
, world(worldSize)
, borderWidth(1)
, worldPos(world.center())

, pause(false)
, interval(100)
, updateWorldTimer(0)
{
	calculateCells();
}

WorldDisplay::~WorldDisplay()
{

}

void WorldDisplay::draw()
{
	SDL_Rect canvas = dim;
    Uint32 	 white;
	int retval;

	if (updateWorld() && !pause) {
		world.step();
	}

    white = SDL_MapRGB(screen->format, 0xff, 0xff, 0xff);

	// Get a clean cut
	SDL_SetClipRect(screen, &canvas);

	// draw background
	retval = SDL_FillRect(screen, &canvas, white);
	if (retval != 0) {
		std::cerr << "Problem beim Zeichnen des Rechtecks\n";
	}

	drawBorders();
	drawLivingCells();
	drawCursor();

	// Maybe better to save the old value and set it back here ...
	SDL_SetClipRect(screen, 0);
}

void WorldDisplay::drawBorders()
{
	int retval;
    Uint32 grey;

    grey  = SDL_MapRGB(screen->format, 0xcc, 0xcc, 0xcc);

	// Draw vertical lines until the end of the draw area is reached
	for (unsigned int cx = dim.x; cx < dim.w + dim.x; cx += cellWidth.x + borderWidth)
	{
		SDL_Rect line;
		line.x = cx;
		line.y = dim.y;
		line.w = borderWidth;
		line.h = dim.h;

		/*
		std::cout << "Drawing border line " << line.x << "x" << line.y << " "
											<< line.w << "x" << line.h << std::endl;
		*/

		retval = SDL_FillRect(screen, &line, grey);
		if (retval != 0) {
			std::cerr << "Problem beim Zeichnen des Rechtecks\n";
		}
	}


	// Draw horizontal lines until the end of the draw area is reached
	for (unsigned int cy = dim.y; cy < dim.h + dim.y; cy += cellWidth.y + borderWidth)
	{
		SDL_Rect line;
		line.x = dim.x;
		line.y = cy;
		line.w = dim.w;
		line.h = borderWidth;

		retval = SDL_FillRect(screen, &line, grey);
		if (retval != 0) {
			std::cerr << "Problem beim Zeichnen des Rechtecks\n";
		}
	}
}

void WorldDisplay::drawLivingCells()
{
	SDL_Rect cell;
    Uint32 black;
	int retval;

    black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);

	Util::Vec2u effectiveCellsize = cellWidth + borderWidth;

	// y coordinate of the cell in virtual coordinates
	unsigned int y = 0;
	// y coordinate of the top border of the cell in surface coordinates
	unsigned int cy = dim.y + borderWidth;

	// Draw cells in y direction until the border is reached
	while (cy < dim.h + dim.y) 
	{
		// x coordinate of the cell in virtual coordinates
		unsigned int x = 0;
		// x coordinate of the left border of the cell in surface coordinates
		unsigned int cx = dim.x + borderWidth;

		// Draw cells in x direction until the border is reached
		while (cx < dim.w + dim.x)
		{
			if (world.isAlive(x + worldPos.x, y + worldPos.y)) {
				cell.x = cx;
				cell.y = cy;
				cell.w = cellWidth.x;
				cell.h = cellWidth.y;

				retval = SDL_FillRect(screen, &cell, black);
				if (retval != 0) {
					std::cerr << "Problem beim Zeichnen des Rechtecks\n";
				}
			}

			x++;
			cx += effectiveCellsize.x;
		}

		y++;
		cy += effectiveCellsize.y;
	}
}

void WorldDisplay::drawCursor()
{
    Uint32 red;
	SDL_Rect cursor;
	int retval;

    red = SDL_MapRGB(screen->format, 0xff, 0x00, 0x00);

	// Inside the dimension + position * effective cellsize
	cursor.x = dim.x + cursorPos.x * (cellWidth.x + borderWidth) - borderWidth;
	cursor.y = dim.y + cursorPos.y * (cellWidth.y + borderWidth) - borderWidth;
	cursor.w = cellWidth.x + borderWidth + borderWidth + borderWidth + borderWidth;
	cursor.h = borderWidth + borderWidth;

	// draw cursor
	retval = SDL_FillRect(screen, &cursor, red);
	if (retval != 0) {
		std::cerr << "Problem beim Zeichnen des Rechtecks\n";
	}

	cursor.y += cellWidth.y + borderWidth + borderWidth;

	// draw cursor
	retval = SDL_FillRect(screen, &cursor, red);
	if (retval != 0) {
		std::cerr << "Problem beim Zeichnen des Rechtecks\n";
	}

	// Inside the dimension + position * effective cellsize
	cursor.x = dim.x + cursorPos.x * (cellWidth.x + borderWidth) - borderWidth;
	cursor.y = dim.y + cursorPos.y * (cellWidth.y + borderWidth) - borderWidth;
	cursor.w = borderWidth + borderWidth;
	cursor.h = cellWidth.y + borderWidth + borderWidth + borderWidth + borderWidth;

	// draw cursor
	retval = SDL_FillRect(screen, &cursor, red);
	if (retval != 0) {
		std::cerr << "Problem beim Zeichnen des Rechtecks\n";
	}

	// Inside the dimension + position * effective cellsize
	cursor.x += cellWidth.x + borderWidth + borderWidth;

	// draw cursor
	retval = SDL_FillRect(screen, &cursor, red);
	if (retval != 0) {
		std::cerr << "Problem beim Zeichnen des Rechtecks\n";
	}
}

void WorldDisplay::step()
{
	updateWorldTimer = SDL_GetTicks() + interval;
	world.step();
}

bool WorldDisplay::updateWorld()
{
    Uint32 now = SDL_GetTicks();

    if (updateWorldTimer <= now) {
        updateWorldTimer = now + interval;
		return true;
    }

	return false;
}

void WorldDisplay::setInterval(unsigned int interval)
{
	this->interval = interval;
}

unsigned int WorldDisplay::getInterval() const
{
	return interval;
}

void WorldDisplay::setPause(bool pause)
{
	this->pause = pause;
}

bool WorldDisplay::isPaused() const
{
	return pause;
}

bool WorldDisplay::moveCursor(const Util::Vec2i &delta)
{
	if (cursorPos.x + delta.x >= cursorBoundary.x &&
		cursorPos.x + delta.x < cursorBoundary.w)
	{
		cursorPos.x += delta.x;
	}
	else {
		return moveView(delta);
	}

	if (cursorPos.y + delta.y >= cursorBoundary.y &&
		cursorPos.y + delta.y < cursorBoundary.h)
	{
		cursorPos.y += delta.y;
	}
	else {
		return moveView(delta);
	}

	return true;
}

void WorldDisplay::toggleCell()
{
	world.toggle(cursorPos.x + worldPos.x, cursorPos.y + worldPos.y);
}

bool WorldDisplay::moveView(const Util::Vec2i &delta)
{
	if ((delta.x < 0 && static_cast<int>(worldPos.x) < abs(delta.x)) ||
		(delta.x + worldPos.x + cells.x > world.getCells().x))
	{
		return false;
	}

	if ((delta.y < 0 && static_cast<int>(worldPos.y) < abs(delta.y)) ||
		(delta.y + worldPos.y + cells.y > world.getCells().y))
	{
		return false;
	}

	worldPos.x += delta.x;
	worldPos.y += delta.y;

	return true;
}

bool WorldDisplay::setCellWidth(const Util::Vec2u &width)
{
	gpassert(width.x < dim.w && width.y < dim.h);

	unsigned int maxX = (dim.w - borderWidth) / (width.x + borderWidth) + 1 + worldPos.x;
	unsigned int maxY = (dim.h - borderWidth) / (width.y + borderWidth) + 1 + worldPos.y;

	if (maxX > world.getCells().x) {
		return false;
	}
	if (maxY > world.getCells().y) {
		return false;
	}

	this->cellWidth = width;
	calculateCells();

	return true;
}

Util::Vec2u WorldDisplay::getCellWidth() const
{
	return cellWidth;
}

Util::Boxu WorldDisplay::getDimension() const
{
	return dim;
}

void WorldDisplay::setCursorBoundary(const Util::Boxu &box)
{
	cursorBoundary = box;
	cursorPos.x = box.x + box.w / 2;
	cursorPos.y = box.y + box.h / 2;
}

Util::Boxu WorldDisplay::getCursorBoundary() const
{
	return cursorBoundary;
}

void WorldDisplay::setBorderWidth(unsigned int px)
{
	borderWidth = px;

	calculateCells();
}

unsigned int WorldDisplay::getBorderWidth() const
{
	return borderWidth;
}

void WorldDisplay::calculateCells()
{
	// Number of cells displayed
	cells.x = (dim.w - borderWidth) / (cellWidth.x + borderWidth) + 1;
	cells.y = (dim.h - borderWidth) / (cellWidth.y + borderWidth) + 1;

	// Border width
	cursorBoundary.x = cells.y / 6;
	cursorBoundary.y = cells.y / 6;
	cursorBoundary.w = cells.x - cells.y / 6;
	cursorBoundary.h = cells.y - cells.y / 6;

	// Position of the cursor
	cursorPos.x = cursorBoundary.w / 2;
	cursorPos.y = cursorBoundary.h / 2;
}

void WorldDisplay::clear()
{
	world.clearWorld();
}

unsigned int WorldDisplay::getActiveCells() const
{
	return world.getActiveCells();
}

unsigned int WorldDisplay::getTotalCells() const
{
	return world.getCells().x * world.getCells().y;
}

std::istream &GP2XOfLife::operator>>(std::istream &is, WorldDisplay &wd)
{
	is >> wd.world;

	if (!is.bad()) {
		wd.worldPos = wd.world.center();

		if (wd.cells >= wd.world.getCells()) {
			wd.worldPos.x = 0;
			wd.worldPos.y = 0;
		}
	}

	return is;
}

std::ostream &GP2XOfLife::operator<<(std::ostream &os, const WorldDisplay &wd)
{
	return os << wd.world;
}

