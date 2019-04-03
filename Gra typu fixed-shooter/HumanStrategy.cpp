#include "HumanStrategy.h"
HumanStrategy::HumanStrategy()
	:Strategy()
{
	destroyed = false;
}

HumanStrategy::HumanStrategy(const HumanStrategy &object) 
	:Strategy(object) 
{}

void HumanStrategy::loadObject(const std::shared_ptr<GameObject> &object)
{
	playerObject = object;
}

void HumanStrategy::keyControler(char &c, GameObjects &gameObjects, GameObjects &playerGameObjects, TextDisplay &td, std::mutex &mtx)
{
	if (playerObject == nullptr || destroyed) return;
	size_t t = 0;
	if (isalpha(c))
	{
		MovementStrategy(gameObjects, c);
	}
	else if (c == shot)
	{
		FireStrategy(playerGameObjects, td, mtx);
	}
	else if (c == change)
	{
		playerObject->changeAmmo(c);
	}
	c = 0;
}

void HumanStrategy::MovementStrategy(GameObjects &gameObjects, char &c)
{
	
		if (c == right)
		{
			if (playerObject != nullptr)
			playerObject->setDestination({ static_cast<int>(playerObject->getPosition().x + speed) , static_cast<int>(playerObject->getPosition().y) }, speed);
		}
		else if (c == left)
		{
			if (playerObject != nullptr)
			playerObject->setDestination({ static_cast<int>(playerObject->getPosition().x - speed) , static_cast<int>(playerObject->getPosition().y) }, speed);
		}
		else if (c == up)
		{
			if (playerObject != nullptr)
			playerObject->setDestination({ static_cast<int>(playerObject->getPosition().x) , static_cast<int>(playerObject->getPosition().y - speed) }, speed);
		}
		else if (c == down)
		{
			if (playerObject != nullptr)
			playerObject->setDestination({ static_cast<int>(playerObject->getPosition().x) , static_cast<int>(playerObject->getPosition().y + speed) }, speed);
		}
	
}

void HumanStrategy::FireStrategy(GameObjects &playerGameObjects, TextDisplay &td, std::mutex &mtx)
{
 	playerObject->fire(*fire, td, playerGameObjects, mtx);
}	


bool HumanStrategy::checkPlayerShipDestroyed()
{
	if (playerObject->destroyed())
	{
		destroyed = true;
		return true;
	}
	destroyed = false;
	return false;
}

size_t HumanStrategy::getPlayerID()
{
	return playerObject->getID();
}

void changeShip()
{

}