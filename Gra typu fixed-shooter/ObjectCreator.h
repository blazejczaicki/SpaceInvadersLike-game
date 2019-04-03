#pragma once
#include<fstream>
#include <sstream>
#include<list>
#include <string>
#include"Ship.h"
#include"Bullet.h"
#include "GameObjects.h"
#include "TextDisplay.h"
#include "Ammunition.h"

class ObjectCreator
{
	bool isObjectName(std::string line);
	std::string loadShipData(const std::string &filename, const size_t &spriteID, Point<int>& size, std::vector<std::shared_ptr<Cannon>> &cannons, std::string& name, const std::map<size_t, std::shared_ptr<Ammunition>> &ammunitions);
	std::string loadBulletData(const std::string &filename, const size_t &spriteID, Point<int>& size, std::string& name, int &damage);
public:
	size_t createShip(GameObjects& gameObjects, const Point<double>& pos, const std::string &filename, TextDisplay &td, const size_t &idSprite, const std::map<size_t, std::shared_ptr<Ammunition>> &ammunitions);
	size_t createBullet(GameObjects& gameObjects,Point<double> bulletPos, const std::string &filename, TextDisplay &td, const size_t &idSprite, const bool &direction);
};
