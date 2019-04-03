#pragma once
#include <list>
#include"GameObjects.h"
#include "Fire.h"

class Strategy
{
protected:
	int speed;
	std::shared_ptr<Fire> fire;
public:
	Strategy();
	Strategy(const Strategy &object);
	virtual void loadObject(const std::shared_ptr<GameObject> &object) = 0;
	virtual void MovementStrategy(GameObjects &gameObjects, char &c) = 0;
};