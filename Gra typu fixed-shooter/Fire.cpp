#include"Fire.h"

bool Fire::check(std::shared_ptr<Cannon> &cannon)
{
	return cannon->checkInterval();
}


void Fire::shot(std::shared_ptr<Cannon> &cannon, const Point<double> &pos, GameObjects &gameObjects, TextDisplay &td, bool direction)
{
	if (cannon->cannonShot())
	{
		ObjectCreator oc;
		auto id = oc.createBullet(gameObjects, cannon->getPosition(pos), "Pociski.txt", td, cannon->getCurrentAmmoID(), direction);
		gameObjects[id]->setDestination(cannon->getDestination(pos), 1);
	}
	else
	{
		cannon->changeAmmo();
	}
}

void Fire::shot(std::shared_ptr<Cannon> &cannon, const Point<double> &pos, GameObjects &playerGameObjects, TextDisplay &td, bool direction, std::mutex &mtx)
{
	if (cannon->cannonShot())
	{
		ObjectCreator oc;
		std::unique_lock<std::mutex> lck(mtx);
		auto id = oc.createBullet(playerGameObjects, cannon->getPosition(pos), "Pociski.txt", td, cannon->getCurrentAmmoID(), direction);
		playerGameObjects[id]->setDestination(cannon->getDestination(pos), 1);
		lck.unlock();
	}
	else
	{
		cannon->changeAmmo();
	}
}