#pragma once
#include <cmath>
#include <string>
#include <algorithm>
#include <iterator>
#include <map>
#include <vector>
#include <set>
#include<memory>//
#include "curses.h"
#include "Point.h"
#include "TextDisplay.h"
#include "Cannon.h"

#define _use_math_defines

class Fire;
class GameObjects;
class Bullet;
class BulletTypes;

class GameObject
{
protected:
	int hp, speed, damage;
	size_t id, schemeID;
	std::string name;

	bool upDirection;

	Point<double> position;
	Point<int> size, destinationPoint;
	std::vector<std::shared_ptr<Cannon>> cannons;
	std::set<Point<int>> objectPoints;
	std::vector<int> positionOnGrid;
public:
	GameObject() = delete;
	GameObject(const Point<double> &xy, const std::set<Point<int>> &points, const size_t &_id, const Point<int> &_size, const int &_hp, const std::string &_name, std::vector<std::shared_ptr<Cannon>> _cannons, const int &_damage);

	 void changePosition();
	 void damageObject(const int &hp2, const int &dmg);
	 void destroyObject();
	 bool destroyed();
	 void fire(Fire fire, TextDisplay &td, GameObjects &gameObjects);
	 void fire(Fire fire, TextDisplay &td, GameObjects &playerGameObjects, std::mutex &mtx);
	 void changeAmmo(const char &c);

	void setDirection(bool d);
	void setPositionOnGrid(const std::vector<int> &idMap);
	void setPosition(const Point<double> &p);
	virtual void setDestination(const Point<int> &d, const int &s);
	void setSchemeID(const size_t &id);

	size_t getSchemeID() const;
	Point<int> getDestination() const;
	std::set<Point<int>> getObjectPoints() const;
	size_t getID() const;
	Point<int> getSize() const;
	Point<double> getPosition() const;
	std::vector<int> getPositionOnGrid() const;
	std::string getName() const;
	int getHP() const;
	int getDamage() const;

	size_t getAmmoID() const;
	int getAmmoNumber() const;
};