#pragma once
#include"GameObjects.h"
#include"ComputerStrategy.h"
#include"HumanStrategy.h"
#include"ScreenData.h"
#include"GameManager.h"

class Collision
{
	int destroyingArea[4];
	std::map<int, std::set<unsigned>> objectsOnQuadrants;
public:
	Collision();
	void calculateIDMap(std::vector<int> &idMap, std::shared_ptr<GameObject> &gameObject);
	void giveObjectOnQuadrant(GameObjects &allObjects);
	void checkingCollisionsAreas(GameObjects &allObjects);

	void checkObjectIsOutside(GameObjects &objects);
	void removeObjects(GameObjects &objects, GameManager &gameManager, HumanStrategy &humanStrategy, size_t &playerID, bool &isDestroyed, size_t &computerShips);

	void checkingCollision(std::shared_ptr<GameObject> &object, GameObjects &objects, std::set<unsigned>::iterator &objectsOnQuadrant, std::set<unsigned>::iterator &end);
	bool detectCollision(std::shared_ptr<GameObject> &object, std::shared_ptr<GameObject> &otherObject);

	/*int bezposredniaIDob1 = -1;
	int bezposredniaIDob2 = -1;
	int posredniaIDob1 = -1;
	int posredniaIDob2 = -1;*/
};