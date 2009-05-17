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

#ifndef _VEC2_H_
#define _VEC2_H_

#include <iostream>
#include "Box.h"

namespace Util
{

// Forward declarations *eeew*
template<class T> class Vec2;

template<class T> bool operator>(const Vec2<T> &a, const Vec2<T> &b);
template<class T> bool operator>=(const Vec2<T> &a, const Vec2<T> &b);

template<class T> bool operator==(const Vec2<T> &a, const Vec2<T> &b);
template<class T> bool operator!=(const Vec2<T> &a, const Vec2<T> &b);

template<class T> const Vec2<T> operator+(const Vec2<T> &a, const T &b);
template<class T> const Vec2<T> operator+(const Vec2<T> &a, const Vec2<T> &b);

template<class T> const Vec2<T> operator-(const Vec2<T> &a, const T &b);
template<class T> const Vec2<T> operator-(const Vec2<T> &a, const Vec2<T> &b);

template<class T> Vec2<T>& operator+=(Vec2<T> &a, const T &b);
template<class T> Vec2<T>& operator+=(Vec2<T> &a, const Vec2<T> &b);

template<class T> Vec2<T>& operator-=(Vec2<T> &a, const T &b);
template<class T> Vec2<T>& operator-=(Vec2<T> &a, const Vec2<T> &b);

template<class T> std::ostream& operator<<(std::ostream &os, const Vec2<T> &a);
template<class T> std::istream& operator>>(std::istream &is, Vec2<T> &a);

template<class T>
class Vec2
{
public:
	Vec2()
	{

	}

	Vec2(const T &x, const T &y)
	: x(x)
	, y(y)
	{

	}

	~Vec2()
	{

	}

	friend bool operator><>(const Vec2<T> &a, const Vec2<T> &b);
	friend bool operator>=<>(const Vec2<T> &a, const Vec2<T> &b);

	friend bool operator==<>(const Vec2<T> &a, const Vec2<T> &b);
	friend bool operator!=<>(const Vec2<T> &a, const Vec2<T> &b);

	friend const Vec2<T> operator+<>(const Vec2<T> &a, const T &b);
	friend const Vec2<T> operator+<>(const Vec2<T> &a, const Vec2<T> &b);

	friend const Vec2<T> operator-<>(const Vec2<T> &a, const T &b);
	friend const Vec2<T> operator-<>(const Vec2<T> &a, const Vec2<T> &b);

	friend Vec2<T>& operator+=<>(Vec2<T> &a, const T &b);
	friend Vec2<T>& operator+=<>(Vec2<T> &a, const Vec2<T> &b);

	friend Vec2<T>& operator-=<>(Vec2<T> &a, const T &b);
	friend Vec2<T>& operator-=<>(Vec2<T> &a, const Vec2<T> &b);

	friend std::ostream& operator<<<>(std::ostream &os, const Vec2<T> &a);
	friend std::istream& operator>><>(std::istream &is, Vec2<T> &a);

public:
	T x;
	T y;
};

typedef Vec2<int> Vec2i;
typedef Vec2<unsigned int> Vec2u;
typedef Vec2<float> Vec2f;
typedef Vec2<double> Vec2d;

template<class T> bool operator>(const Vec2<T> &a, const Vec2<T> &b)
{
	return a.x > b.x && a.y > b.y;
}

template<class T> bool operator>=(const Vec2<T> &a, const Vec2<T> &b)
{
	return a.x >= b.x && a.y >= b.y;
}

template<class T> 
bool operator==(const Vec2<T> &a, const Vec2<T> &b)
{
	return a.x == b.x && a.y == b.y;
}

template<class T>
bool operator!=(const Vec2<T> &a, const Vec2<T> &b)
{
	return a.x != b.x || a.y != b.y;
}

template<class T>
const Vec2<T> operator+(const Vec2<T> &a, const T &b)
{
	return Vec2<T>(a.x + b, a.y + b);
}

template<class T>
const Vec2<T> operator+(const Vec2<T> &a, const Vec2<T> &b)
{
	return Vec2<T>(a.x + b.x, a.y + b.y);
}

template<class T>
const Vec2<T> operator-(const Vec2<T> &a, const T &b)
{
	return Vec2<T>(a.x - b, a.y - b);
}

template<class T>
const Vec2<T> operator-(const Vec2<T> &a, const Vec2<T> &b)
{
	return Vec2<T>(a.x - b.x, a.y - b.y);
}

template<class T>
Vec2<T>& operator+=(Vec2<T> &a, const T &b)
{
	a.x += b;
	a.y += b;
	return a;
}

template<class T>
Vec2<T>& operator+=(Vec2<T> &a, const Vec2<T> &b)
{
	a.x += b.x;
	a.y += b.y;
	return a;
}

template<class T>
Vec2<T>& operator-=(Vec2<T> &a, const T &b)
{
	a.x -= b;
	a.y -= b;
	return a;
}

template<class T>
Vec2<T>& operator-=(Vec2<T> &a, const Vec2<T> &b)
{
	a.x -= b.x;
	a.y -= b.y;
	return a;
}

template<class T> std::ostream& operator<<(std::ostream &os, const Vec2<T> &a)
{
	return os << a.x << ',' << a.y;
}

template<class T> std::istream& operator>>(std::istream &is, Vec2<T> &a)
{
	T x;
	T y;
	char c = 0;

	is >> x;
	is >> c;

	if (c == ',') {
		is >> y;
	}
	else {
		is.clear(std::ios_base::badbit);
	}

	if (is) a = Vec2<T>(x, y);

	return is;
}

};

#endif /* !_VEC2_H_ */
