#pragma once
#include "GameObject.h"


class Bullet
	:public GameObject
{
public:
	Bullet() = delete;
	Bullet(const Point<double> &xy, const std::set<Point<int>> &points, const size_t &_id, const Point<int> &_size, const int &_hp, const std::string &_name, std::vector<std::shared_ptr<Cannon>> _cannons, const int &_damage);
};
