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

#ifndef _WORLDDISPLAY_H_
#define _WORLDDISPLAY_H_

namespace GP2XOfLife
{
class World;

class WorldDisplay
{
// Attributes

private:
	SDL_Surface *screen;

	Util::Boxu dim;
	Util::Vec2u cellWidth;
	Util::Vec2u cells;
	World world;
	unsigned int borderWidth;

	Util::Boxu  cursorBoundary;
	Util::Vec2u cursorPos;

	Util::Vec2u worldPos;

	bool pause;
	unsigned int interval;
	Uint32 updateWorldTimer;

// Operations
	
public:
	WorldDisplay(
		SDL_Surface *screen,
		const Util::Boxu dimension, 
		const Util::Vec2u worldSize
	);
	~WorldDisplay();

	void draw();
	void step();

	bool setCellWidth(const Util::Vec2u &width);
	Util::Vec2u getCellWidth() const;

	Util::Boxu getDimension() const;

	void setInterval(unsigned int interval);
	unsigned int getInterval() const;

	void setPause(bool pause);
	bool isPaused() const;

	bool moveCursor(const Util::Vec2i &delta);
	bool moveView(const Util::Vec2i &delta);
	void toggleCell();

	void setCursorBoundary(const Util::Boxu &box);
	Util::Boxu getCursorBoundary() const;

	void setBorderWidth(unsigned int px);
	unsigned int getBorderWidth() const;

	unsigned int getActiveCells() const;
	unsigned int getTotalCells() const;

	void clear();

	friend std::istream &operator>>(std::istream &os, WorldDisplay &wd);
	friend std::ostream &operator<<(std::ostream &os, const WorldDisplay &wd);

private:
	bool updateWorld();
	void drawBorders();
	void drawLivingCells();
	void drawCursor();
	void calculateCells();
};

};

#endif /* !_WORLDDISPLAY_H_ */
