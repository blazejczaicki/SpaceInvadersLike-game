#pragma once

template<class T>
struct Point
{
	T x = 0;
	T y = 0;
	Point()=default;
	Point( T xx, T yy);
	template <class U>
	Point<T> &operator=(const Point<U>& object);
	Point<T> operator+(const Point<T>&object) const;
	template<class U>
	Point<T> operator+(const Point<U>&object) const;
	Point<T> operator-(const Point<T> &object) const;
	template <class U>
	Point<T> operator-(const Point<U> &object) const;
	Point<T> operator*(int value) const;
	Point<T> operator/(int value) const;
	bool operator<(const Point<T>& object) const;
	bool operator==(const Point<T>& object)const;

};	

	template<class T>
	Point<T>::Point(T xx, T yy)
	{
		x = xx;
		y = yy;
	}

	template<class T>
	bool Point<T>::operator==(const Point<T>& object) const
	{
		return x == object.x && y == object.y;
	}

	template<class T>
	bool Point<T>::operator<(const Point<T>& object) const
	{
		return x < object.x || (x == object.x && y < object.y);
	}

	template<class T>
	Point<T> Point<T>::operator+(const Point<T> &object) const
	{
		return{ x + object.x, y + object.y };
	}

	template<class T>
	Point<T> Point<T>::operator-(const Point<T> &object) const
	{
		return{ x - object.x, y - object.y };
	}

	template<class T>
	Point<T> Point<T>::operator*(int value) const
	{
		return{ x * value, y * value };
	}

	template<class T>
	Point<T> Point<T>::operator/(int value) const
	{
		return{ x / value, y / value };
	}