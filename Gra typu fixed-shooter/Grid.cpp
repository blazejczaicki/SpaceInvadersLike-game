#include "Grid.h"

Grid::Grid(unsigned tileHeight, unsigned tileWidth, unsigned numColumns, unsigned numLines)
{
	this->tileHeight = tileHeight;
	this->tileWidth = tileWidth;
	this->numColumns = numColumns;
	this->numLines = numLines;
}



void Grid::calculateIDMap(std::vector<int> &idMap, std::shared_ptr<GameObject> gameObject)
{
	Point<int> pos;
	pos = gameObject->getCenter();
	idMap.push_back(pos.Y /tileHeight  * numColumns + pos.X / tileWidth);
	idMap.push_back((pos.Y + gameObject->getSize().Y) / tileHeight * numColumns + pos.X / tileWidth);
	idMap.push_back(pos.Y / tileHeight * numColumns + (pos.X + gameObject->getSize().X) / tileWidth);
	idMap.push_back((pos.Y + gameObject->getSize().Y) / tileHeight * numColumns + (pos.X + gameObject->getSize().X) / tileWidth);
	sort(idMap.begin(), idMap.end());
	idMap.erase(unique(idMap.begin(), idMap.end()), idMap.end());//usuwanie duplikatow id kwadrantu
}

void Grid::giveObjectOnQuadrant(const GameObjects &allObjects)
{
	std::vector<int> idMap;
	for(auto& gameObject : allObjects)
	{
		int mm;
		for (auto &deleteOld : gameObject.second->getPositionOnGrid()) //przejscie po id kwadrantow na ktorych jest obiekt
		{
			//objectsOnQuadrants[deleteOld].erase(gameObject->getID());
			auto it = objectsOnQuadrants.find(deleteOld); //wyszukiwanie tego id kwadrantu
			if (it != objectsOnQuadrants.end())
			{
				it->second.erase(gameObject.second->getID());///////////////////dzialanie erase
				/*
				auto it2 = std::find_if(it->second.begin(), it->second.end(), [&allObjects](auto& id) { return id == allObjects[i].getID(); }); //wyszukiwanie w setcie id statku
				if (it2 != it->second.end())
				{
					objectsOnQuadrants.second.erase(it2);//usuwanie
				}
				*/
			}
			else {
				// b³¹d
			}
		}
		// instrukcje poni¿ej- przeksztalcanie rogow box collidera na id kwadrantow
		calculateIDMap(idMap, gameObject.second);
		for (auto& id:idMap) // petla wprowadzajaca do tych id kwadrantow id statku 
		{
			objectsOnQuadrants[id].insert(gameObject.second->getID()); // 1,2,3 -> 1,2 2,3 1,3
			/*// s1 = (0,0)(1,0)(2,0)(1,1)
			// s2 = (2,0)(3,0),(4,0)
			// std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end()) -> (2,0)
			
			// X
			//XXX

			// X
			//XXX
			//XXX
			//XXX

			//         X
			// OOOOOOOOXOOOOOOOOOO
			//         X
			//         X

			// 1024/768
			// 10/7 > 102/109
			// 80x80 -> 6400
			// 20x20 -> 400

			//auto it = objectsOnQuadrants.find(id);
			//if (it != objectsOnQuadrants.end())
			//{
			//	it->second.insert(gameObject->getID());//jesli kwadrant istnieje w kontenerze to dodaje id statku do seta
			//}
			//else
			//{
				//objectsOnQuadrants.insert(std::pair<int, std::set<unsigned int>>(id, second.insert(allObjects[i]->getID())));// jesli nie tworzy nowy element kontenera
			//}*/
		}
		gameObject.second->setPositionOnGrid(idMap);//wprowadzanie do mapy
		idMap.clear();
	}
	for(auto it=objectsOnQuadrants.begin(); it != objectsOnQuadrants.end();)
	{
		if (it->second.empty())
			objectsOnQuadrants.erase(it++);
		else
			it++;
	}
}	

void Grid::checkingCollisionsAreas(GameObjects &allObjects)
{
	for (auto &quadrant: objectsOnQuadrants)
	{
		if (quadrant.second.size() > 1) // 1, 2, 3
		{
			auto end = quadrant.second.end(); // 4
			for(auto it = quadrant.second.begin(); it != quadrant.second.end(); ++it)
			{
				auto current = *it; // 1
				it++; //2
				if (it != quadrant.second.end())
				{
					//allObjects[current]->checkingCollision(allObjects, it, end);
				}
				else
				{
					break;
				}
			}
		}
	}
}

unsigned Grid::getTileHeight()
{
	return tileHeight;
}

unsigned Grid::getTileWidth()
{
	return tileWidth;
}