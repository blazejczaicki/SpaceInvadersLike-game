#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include "ScreenData.h"
class Ship
	: public GameObject
{
public:
	Ship() = delete;
	Ship(const Point<double> &xy, const std::set<Point<int>> &points, const size_t &_id, const Point<int> &_size, const int &_hp, const std::string &_name, std::vector<std::shared_ptr<Cannon>> _cannons, const int &_damage);
	void setDestination(const Point<int> &d, const int &s) override;
};


