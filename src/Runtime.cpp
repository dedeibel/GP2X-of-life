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
	#include <sys/time.h>
}

#include <ctime>
#include <ostream>

#include "Runtime.h"

Runtime::Runtime()
{
	startTime.tv_sec  = 0;
	startTime.tv_usec = 0;

	stopTime.tv_sec  = 0;
	stopTime.tv_usec = 0;
}

Runtime::~Runtime()
{

}

void Runtime::start()
{
	if (gettimeofday(&startTime, 0) == -1) {
		startTime.tv_sec  = 0;
		startTime.tv_usec = 0;
	}
}

void Runtime::stop()
{
	if (gettimeofday(&stopTime, 0) == -1) {
		stopTime.tv_sec  = 0;
		stopTime.tv_usec = 0;
	}
}

unsigned int Runtime::getTime() const
{
	unsigned long diff = 0;

	if (startTime.tv_sec != stopTime.tv_sec) {
		diff = (stopTime.tv_sec - startTime.tv_sec) * 1000000L;
	}

	diff += stopTime.tv_usec - startTime.tv_usec;

	return diff;
}

std::ostream &operator<<(std::ostream &os, const Runtime &r)
{
	return os << r.getTime();
}
