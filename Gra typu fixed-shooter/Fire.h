#pragma once
#include "ObjectCreator.h"
#include "Cannon.h"

class Fire
{
public:
	bool check(std::shared_ptr<Cannon> &cannon);
	void shot(std::shared_ptr<Cannon> &cannon, const Point<double> &pos, GameObjects &gameObjects, TextDisplay &td, bool direction);
	void shot(std::shared_ptr<Cannon> &cannon, const Point<double> &pos, GameObjects &playerGameObjects, TextDisplay &td, bool direction, std::mutex &mtx);
};
