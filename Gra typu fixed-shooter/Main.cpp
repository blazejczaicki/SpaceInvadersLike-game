#include <typeinfo>
#include <thread>
#include"ObjectCreator.h"
#include "Ship.h"
#include "Bullet.h"
#include "Cannon.h"
#include"TextDisplay.h"
#include"Collision.h"
#include"ComputerStrategy.h"
#include"HumanStrategy.h"
#include"ScreenData.h"
#include"GameManager.h"


void createAmmo(std::map<size_t, std::shared_ptr<Ammunition>> &ammunitions)
{
	size_t idBullet = 1;
	int numberBullets = 100;
	double fireRatio = 0.6;
	double extendRatio = 0.2;
	for (size_t i = 1; i < 7; i++)
	{
		ammunitions.insert(std::pair<size_t, std::shared_ptr<Ammunition>>(i, std::make_shared<Ammunition>(idBullet, numberBullets, fireRatio)));
		idBullet++;
		numberBullets -= 10;
		if(i%3)
		fireRatio += extendRatio;
	}
}

void game(const size_t &scenarioID, const size_t &playerTypeShID, TextDisplay &td)
{
	GameObjects gameObjects;
	Collision collision;
	HumanStrategy schemePlayer;
	GameManager gameManager(scenarioID);

	std::map<size_t, std::shared_ptr<Ammunition>> ammunitions;
	createAmmo(ammunitions);

	size_t playerID;
	size_t computerShips = 0;
	char quit = 0;
	bool isDestroyed = true;
	GameObjects playerGameObjects;
	std::mutex mtx;
	std::thread t(&TextDisplay::playerMove, &td, std::ref(quit), std::ref(schemePlayer), std::ref(gameObjects), std::ref(playerGameObjects), ref(mtx), std::ref(td));
	while (quit != 27)
	{
		if (gameManager.checkWave(computerShips))
		{
			gameManager.addWave( gameObjects, td, ammunitions);
		}
		if (isDestroyed)
		{
			gameManager.changeLifes();
			if (gameManager.checkLifes())
			{
				gameManager.newPlayerShip(schemePlayer, gameObjects, td, ammunitions, playerID, playerTypeShID);
				isDestroyed = false;
			}
		}

		for (const auto& object : gameObjects)
		{
			object.second->changePosition();
		}
		gameManager.checkComputerStrategies(gameObjects, td);
		collision.giveObjectOnQuadrant(gameObjects);
		collision.checkingCollisionsAreas(gameObjects);
		collision.checkObjectIsOutside(gameObjects);
		collision.removeObjects(gameObjects, gameManager, schemePlayer, playerID, isDestroyed, computerShips);


		td.printGrid();//do wyłączenia i modyfikacji

		for (auto& object : gameObjects)
		{
			td.printObject(object.first, object.second->getPosition(), object.second->getObjectPoints());
		}
		if (gameObjects.find(playerID) != gameObjects.end())
			td.displayUI(gameObjects[playerID]->getHP(), gameManager.getLifes(), gameObjects[playerID]->getAmmoID(), gameObjects[playerID]->getAmmoNumber());
		//////////////////////////////////////////////////////////
		/*Point<double> place({ 1, 3 });
		std::string str;
		for (auto& object : gameObjects)
		{
			if (typeid(*object.second) != typeid(Bullet))
			{
				str = "ID: " + std::to_string(object.second->getID()) + "  " + object.second->getName() + "\n Pozycja glowna:  " +
					std::to_string(object.second->getPosition().x) + ", " + std::to_string(object.second->getPosition().y) + "\n HP: " + std::to_string(object.second->getHP()) + "\n";
				for (auto p : object.second->getPositionOnGrid())
				{
					str += std::to_string(p) + ", ";
				}
				td.printText(str, place);
				place.y += 5;
			}
		}*/
		//////////////////////////////////////////////////////////

		std::unique_lock<std::mutex> lck(mtx);
		gameObjects.insert(playerGameObjects.begin(), playerGameObjects.end());
		playerGameObjects.clear();
		lck.unlock();
		td.wait();

		if (gameManager.checkWin(computerShips))
		{
			td.displayEnd(true);
			quit = 27;
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			break;
		}
		else if (!gameManager.checkLifes())
		{
			td.displayEnd(false);
			quit = 27;
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			break;
		}
	}
	t.join();
}

int main(int argc, char * args[])
{
	TextDisplay td;
	size_t scenarioID, playerTypeShID;
	while (td.menu(scenarioID, playerTypeShID))
	{
		game(scenarioID, playerTypeShID, td);
		TextDisplay td;
	}
	return 0;
}