#include "Bullet.h"

Bullet::Bullet(const Point<double> &xy, const std::set<Point<int>> &points, const size_t &_id, const Point<int> &_size, const int &_hp, const std::string &_name, std::vector<std::shared_ptr<Cannon>> _cannons, const int &_damage)
	:GameObject(xy, points, _id, _size, _hp, _name, _cannons, _damage)
{}