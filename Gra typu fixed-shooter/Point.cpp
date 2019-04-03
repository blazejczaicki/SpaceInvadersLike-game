#include "Point.h"
template<>
template<>
Point<int>& Point<int>::operator=(const Point<double>& object)
{
	x = static_cast<int>(object.x);
	y = static_cast<int>(object.y);
	return *this;
}

template<>
template<>
Point<double>& Point<double>::operator=(const Point<int>& object)
{
	x = static_cast<double>(object.x);
	y = static_cast<double>(object.y);
	return *this;
}

template<>
template<>
Point<double> Point<double>::operator+(const Point<int>&object) const
{
	return { x + static_cast<double>(object.x), y + static_cast<double>(object.y) };
}

template<>
template<>
Point<int> Point<int>::operator+(const Point<double>&object) const
{
	return { x + static_cast<int>(object.x), y + static_cast<int>(object.y) };
}

template<>
template<>
Point<double> Point<double>::operator-(const Point<int> &object) const
{
	return { x - static_cast<double>(object.x), y - static_cast<double>(object.y) };
}

template<>
template<>
Point<int> Point<int>::operator-(const Point<double> &object) const
{
	return { x - static_cast<int>(object.x), y - static_cast<int>(object.y) };
}

