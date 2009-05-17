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

#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <cstdarg>
#include <cstdio>

#include "Game.h"

namespace GP2XOfLife {

#ifdef DEBUG

	// You can change __BASE_FILE__ to __FILE__ for compatibility reasons
	#define debug(format, args...) debugOutput(__BASE_FILE__, __LINE__, format, ## args)

	inline void debugOutput(const char* file, unsigned int line, const char* format, ...)
	{
		fprintf(stderr, "DEBUG (%s, Line %u): ", file, line);

		va_list args;
		va_start(args, format);

		vfprintf(stderr, format, args);

		va_end(args);

		fprintf(stderr, "\n");
	}
#else
	#define debug(format, args...) ;
#endif

#ifdef ASSERT
	#define gpassert(cond) assertion(__BASE_FILE__, __LINE__, #cond, cond)

	inline void assertion(const char* file, unsigned int line, const char* cond, bool value)
	{
		if (!value) {
			fprintf(stderr, "ASSERT FAILED (%s, Line %u): %s\n", file, line, cond);
		}
	}
#else
	#define gpassert(cond) ;
#endif

	#define error(format, args...) errorOutput(__BASE_FILE__, __LINE__, format, ## args)
	#define fatal(format, args...) fatalOutput(__BASE_FILE__, __LINE__, format, ## args)

	inline void errorOutput(const char* file, unsigned int line, const char* format, ...)
	{
		fprintf(stderr, "ERROR (%s, Line %u): ", file, line);

		va_list args;
		va_start(args, format);

		vfprintf(stderr, format, args);

		va_end(args);

		fprintf(stderr, "\n");
	}

	inline void fatalOutput(const char* file, unsigned int line, const char* format, ...)
	{
		fprintf(stderr, "ERROR (%s, Line %u): ", file, line);

		va_list args;
		va_start(args, format);

		vfprintf(stderr, format, args);

		va_end(args);

		fprintf(stderr, "\n");
		Game::quit();
	}

}

#endif /* !_DEBUG_H_ */
