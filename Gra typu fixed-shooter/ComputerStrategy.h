#pragma once
#include "Strategy.h"

class ComputerStrategy
	:public Strategy
{
	std::map<size_t, Point<double>> startPos;
	std::list<Point<int>> path;
	std::list<Point<int>>::iterator it;
	std::vector<int> shipsType;
	size_t schemeID;
	bool checkPos(const std::shared_ptr<GameObject> &object);
public:
	ComputerStrategy() = default;
	ComputerStrategy(const ComputerStrategy& object);
	ComputerStrategy(size_t _id, std::list<Point<int>> _list, const std::vector<int> &_shipsType);
	void loadObject(const std::shared_ptr<GameObject> &object) override;
	void MovementStrategy(GameObjects &gameObjects, char &c) override;
	void FireStrategy(GameObjects &gameObjects, TextDisplay &td);
	void goDown();// zejœcie obiektów ni¿ej
	ComputerStrategy &operator=(const ComputerStrategy &object);
	void removeFromScheme(const size_t &id);
	std::vector<int> getShipsType() const;
};