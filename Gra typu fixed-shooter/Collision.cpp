#include"Collision.h"

Collision::Collision()
{
	destroyingArea[0] = 0 - TILE_WIDTH;
	destroyingArea[1] = 0 - TILE_HEIGHT*2;
	destroyingArea[2] = SCREEN_WIDTH + TILE_WIDTH;
	destroyingArea[3] = SCREEN_HEIGHT + 5;
}


void Collision::calculateIDMap(std::vector<int> &idMap, std::shared_ptr<GameObject> &gameObject)
{
	Point<int> pos;
	pos = gameObject->getPosition();
	idMap.push_back(pos.y / TILE_HEIGHT * NUMBER_COLUMNS + pos.x / TILE_WIDTH);
	idMap.push_back((pos.y + gameObject->getSize().y) / TILE_HEIGHT * NUMBER_COLUMNS + pos.x / TILE_WIDTH);
	idMap.push_back(pos.y / TILE_HEIGHT * NUMBER_COLUMNS + (pos.x + gameObject->getSize().x) / TILE_WIDTH);
	idMap.push_back((pos.y + gameObject->getSize().y) / TILE_HEIGHT * NUMBER_COLUMNS + (pos.x + gameObject->getSize().x) / TILE_WIDTH);
	sort(idMap.begin(), idMap.end());
	idMap.erase(unique(idMap.begin(), idMap.end()), idMap.end());//usuwanie duplikatow id kwadrantu
}

void Collision::giveObjectOnQuadrant(GameObjects &allObjects)
{
	std::vector<int> idMap;
	for (auto& gameObject : allObjects)
	{
		for (auto &deleteOld : gameObject.second->getPositionOnGrid()) //przejscie po id kwadrantow na ktorych jest obiekt
		{
			auto it = objectsOnQuadrants.find(deleteOld); //wyszukiwanie tego id kwadrantu
			if (it != objectsOnQuadrants.end())
			{
				it->second.erase(gameObject.second->getID());
			}
		}
		calculateIDMap(idMap, gameObject.second);// instrukcje poni¿ej- przeksztalcanie rogow box collidera na id kwadrantow
		for (auto& id : idMap) // petla wprowadzajaca do tych id kwadrantow id statku 
		{
			objectsOnQuadrants[id].insert(gameObject.second->getID());
		}
		gameObject.second->setPositionOnGrid(idMap);//wprowadzanie do mapy
		idMap.clear();
	}
	for (auto it = objectsOnQuadrants.begin(); it != objectsOnQuadrants.end();)
	{
		if (it->second.empty())
			objectsOnQuadrants.erase(it++);
		else
			it++;
	}
}

void Collision::checkObjectIsOutside(GameObjects &objects)
{
	Point<double> p;
	for (auto& obj : objects) 
	{
		p = obj.second->getPosition();
		if (p.y > destroyingArea[3] || p.y < destroyingArea[1] || p.x<destroyingArea[0] || p.x>destroyingArea[2])
		{
			obj.second->destroyObject();
		}
	}
}

void Collision::removeObjects(GameObjects &objects, GameManager &gameManager, HumanStrategy &humanStrategy, size_t &playerID, bool &isDestroyed, size_t &computerShips)
{
	isDestroyed = humanStrategy.checkPlayerShipDestroyed();
	for (auto it = objects.begin(); it != objects.end();)
	{
		if (it->second->destroyed())
		{
			if (it->first != playerID)
			{
			if (typeid(*it->second) != typeid(Bullet))// rtti :)
			{
				computerShips--;
			}
				if (it->second->getSchemeID() != 0)
				{
					gameManager.removeFromScheme(it->second->getSchemeID(), it->second->getID());
				}
				for (auto& q : objectsOnQuadrants)
				{
					q.second.erase(it->first);
				}
				it = objects.erase(it);
			}
			else
			{
				++it;
			}
		}
		else
			++it;
	}
	if (isDestroyed)
	{
		for (auto& q : objectsOnQuadrants)
		{
			q.second.erase(playerID);
		}
		objects.erase(playerID);
	}


}

void Collision::checkingCollisionsAreas(GameObjects &allObjects)
{
	for (auto &quadrant : objectsOnQuadrants)
	{
		if (quadrant.second.size() > 1) 
		{
			auto end = quadrant.second.end(); 
			for (auto it = quadrant.second.begin(); it != quadrant.second.end(); )
			{
				auto current = *it; 
				it++; 
				if (it != quadrant.second.end())
				{
					checkingCollision(allObjects[current], allObjects, it, end);
				}
				else
				{
					break;
				}
			}
		}
	}
}

void Collision::checkingCollision(std::shared_ptr<GameObject> &object, GameObjects &objects, std::set<unsigned>::iterator &objectsOnQuadrant, std::set<unsigned>::iterator &end)
{
	for (auto it = objectsOnQuadrant; it != end; ++it)
	{
		if (detectCollision(object, objects[*it]))
		{
			int tempHp = object->getHP();
			object->damageObject(objects[*it]->getHP(), objects[*it]->getDamage());
			objects[*it]->damageObject(tempHp, object->getDamage());
			//bezposredniaIDob1 = object->getID();
			//bezposredniaIDob2 = objects[*it]->getID();
		}
	}
}

bool Collision::detectCollision(std::shared_ptr<GameObject> &obj1, std::shared_ptr<GameObject> &obj2)
{
	if (obj1->getPosition().x <= (obj2->getPosition().x + obj2->getSize().x) && obj1->getPosition().y <= (obj2->getPosition().y + obj2->getSize().y)
		&& obj2->getPosition().x <= (obj1->getPosition().x + obj1->getSize().x) && obj2->getPosition().y <= (obj1->getPosition().y + obj1->getSize().y))
	{
		//posredniaIDob1 = obj1->getID();
		//posredniaIDob2 = obj2->getID();
		auto objectPoints1 = obj1->getObjectPoints();
		auto objectPoints2 = obj2->getObjectPoints();
		std::set<Point<int>> intersection;
		std::set_intersection(objectPoints1.begin(), objectPoints1.end(), objectPoints2.begin(), objectPoints2.end(),
			std::inserter(intersection, intersection.end()));
		return  intersection.empty() ? false : true;
	}
	return false;
}
