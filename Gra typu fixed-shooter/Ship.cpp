#include"Ship.h"


Ship::Ship(const Point<double> &xy, const std::set<Point<int>> &points, const size_t &_id, const Point<int> &_size, const int &_hp, const std::string &_name, std::vector<std::shared_ptr<Cannon>> _cannons, const int &_damage)
	: GameObject(xy, points, _id, _size, _hp, _name, _cannons, _damage)
{}

void Ship::setDestination(const Point<int> &d, const int &s)
{
	if (d.x > 0 && d.x+size.x < SCREEN_WIDTH &&  d.y > 0 && d.y+4 < SCREEN_HEIGHT)// zabezpieczenie przed wylotem z mapy
	{
		destinationPoint = d;
		speed = s;
	}
}