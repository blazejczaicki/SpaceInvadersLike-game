#pragma once
#include "Strategy.h"

enum Steering
{
	up = 119,
	down = 115,
	right = 100,
	left = 97,
	shot = 32,
	change='`'
};

class HumanStrategy
	:public Strategy
{
	bool destroyed;
	std::shared_ptr<GameObject> playerObject;
public:
	HumanStrategy();
	HumanStrategy(const HumanStrategy &object);
	void loadObject(const std::shared_ptr<GameObject> &object) override;
	void MovementStrategy(GameObjects &gameObjects, char &c) override;
	void FireStrategy(GameObjects &playerGameObjects, TextDisplay &td, std::mutex &mtx);

	bool checkPlayerShipDestroyed();
	void keyControler(char &c, GameObjects &gameObjects, GameObjects &playerGameObjects, TextDisplay &td, std::mutex &mtx);
	size_t getPlayerID();
};