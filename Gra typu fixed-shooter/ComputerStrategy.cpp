#include "ComputerStrategy.h"

ComputerStrategy::ComputerStrategy(size_t _id, std::list<Point<int>> _list, const std::vector<int> &_shipsType)
	: Strategy(), path{ _list }, it{ path.begin() }, schemeID{ _id }, shipsType{ _shipsType }
{
	it = path.begin();
}

ComputerStrategy::ComputerStrategy(const ComputerStrategy& object)
	:Strategy(object) 
{
	startPos = object.startPos;
	path = object.path;
	it = path.begin();
}

ComputerStrategy& ComputerStrategy::operator=(const ComputerStrategy &object)
{
	startPos = object.startPos;
	path = object.path;
	it = path.begin();
	schemeID = object.schemeID;
	fire = object.fire;
	return *this;
}

void ComputerStrategy::loadObject(const std::shared_ptr<GameObject> &object)
{
	startPos.insert(std::pair<int, Point<double>>(object->getID(), object->getPosition()));
}

void ComputerStrategy::MovementStrategy(GameObjects &gameObjects, char &c)
{
	for (const auto& sp : startPos)
	{
		if (checkPos(gameObjects.find(sp.first)->second))
		{
			if (++it == path.end())
			{
				it = path.begin();
			}
			for (const auto& sp2 : startPos)
			{
				gameObjects[sp2.first]->setDestination((*it + startPos[gameObjects[sp2.first]->getID()]), speed);
			}
			break;
		}
	}
}

bool ComputerStrategy::checkPos(const std::shared_ptr<GameObject> &object)
{
	auto d = object->getPosition() - object->getDestination();
	return (fabs(d.x) < 1 && fabs(d.y) < 1);
}

void ComputerStrategy::FireStrategy(GameObjects& gameObjects, TextDisplay &td)
{
	for (const auto& id : startPos)
	{
		gameObjects[id.first]->fire(*fire, td, gameObjects);
	}
}

void ComputerStrategy::removeFromScheme(const size_t &id)
{
	startPos.erase(id);
}

std::vector<int> ComputerStrategy::getShipsType() const
{
	return shipsType;
}

void ComputerStrategy::goDown()
{
	for (auto& sp : startPos)
	{
		sp.second = {sp.second.x ,sp.second.y + 10.0 };
	}
}