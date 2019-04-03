#include "GameManager.h"

GameManager::GameManager(size_t scenarioID)
{
	lifes = 3;
	waveInterval = 60;
	nextWave = 1;
	idScenario = scenarioID;
	loadScenario("Scenariusze.txt");
	loadComputerSchemes("Schematy.txt");
}

void GameManager::loadScenario(std::string filename)
{
	size_t id, numberShips, wave, schemeID;
	wave = id = 1;
	std::string line;
	std::fstream file;
	file.open(filename, std::ios::in);
	if (file.good())
	{
		while (getline(file, line))
		{
			std::istringstream iss(line);
			if (idScenario == id && iss >> numberShips >> schemeID)
			{
				numShipsOnWave.insert(std::pair<size_t, size_t>( wave, numberShips));
				schemeOnWave.insert(std::pair<size_t, size_t>(wave, schemeID));
				wave++;
			}
			else if (line == ";")
			{
				id++;
				wave = 1;
			}
		}
		file.close();
	}
}

void GameManager::loadComputerSchemes(const std::string &filename)
{
	std::list<Point<int>> list;
	std::vector<int> shipTypes;
	int x, y;
	size_t id = 1;
	std::string line;
	std::fstream file;
	file.open(filename, std::ios::in);
	if (file.good())
	{
		while (getline(file, line))
		{

			std::istringstream iss(line);
			if (iss >> x)
			{
				if (iss >> y)
				{
					list.push_back({ x,y });
				}
				else
				{
					shipTypes.push_back(x);
				}
			}
			else if (line == ";")
			{
				computerSchemes[id] = std::make_shared<ComputerStrategy>(id, list, shipTypes);
				list.clear();
				shipTypes.clear();
				id++;
			}
		}
		file.close();
	}
}

void GameManager::addWave( GameObjects &gameObjects, TextDisplay &td,const std::map<size_t, std::shared_ptr<Ammunition>> &ammunitions)
{
	ObjectCreator oc;
	size_t objectID;
	Point<double> pos;
	double numSh = SCREEN_WIDTH/numShipsOnWave.find(nextWave)->second;
	double tempNumSh = numSh*0.5;

	auto shipsType = computerSchemes.find(schemeOnWave.find(nextWave)->second)->second->getShipsType();
	size_t index = 0;
	for (size_t i = 0; i < numShipsOnWave.find(nextWave)->second; i++)
	{
		pos = { tempNumSh, -20.0 };
		objectID = oc.createShip(gameObjects, pos, "Statki.txt", td, shipsType[index], ammunitions);
		computerSchemes.find(schemeOnWave.find(nextWave)->second)->second->loadObject(gameObjects[objectID]);
		gameObjects[objectID]->setSchemeID(schemeOnWave.find(nextWave)->second);
		tempNumSh += numSh;
			if(++index==shipsType.size())//¿eby kolejny statek by³ inny w zale¿noœci od iloœci typów
				index = 0;
	}
	for (size_t i = 1; i < nextWave; i++)
	{
		computerSchemes[schemeOnWave.find(i)->second]->goDown();
	}
	nextWave++;
	startTime = std::chrono::high_resolution_clock::now();
}

bool GameManager::checkWave(size_t &compShipsAlive)
{
	controlTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(controlTime - startTime);
	if (compShipsAlive == 0 || timeSpan.count() > waveInterval)
	{
		if (numShipsOnWave.find(nextWave) == numShipsOnWave.end())
		{
			return false;
		}
		else
		{
			compShipsAlive += numShipsOnWave.find(nextWave)->second;
			return true;
		}
	}
	return false;
}

void GameManager::checkComputerStrategies(GameObjects &gameObjects, TextDisplay &td)
{
	char c;//( c zape³niacz do nieu¿ywanego parametru typu char);
	for (auto& scheme : computerSchemes)
	{
		scheme.second->MovementStrategy(gameObjects, c);
		scheme.second->FireStrategy(gameObjects, td);
	}
}

void GameManager::removeFromScheme(const size_t &schemeID, const size_t &idObject)
{
	computerSchemes[schemeID]->removeFromScheme(idObject);
}

bool GameManager::checkLifes()
{
	if (lifes < 0)
	{
		return false;
	}
	return true;
}

void GameManager::changeLifes()
{
	lifes--;
}

int GameManager::getLifes()
{
	return lifes;
}

int GameManager::getShipsOfWave()
{
	return numShipsOnWave.find(nextWave)->second;
}

bool GameManager::checkWin(size_t computerShips)
{
	if (numShipsOnWave.find(nextWave) == numShipsOnWave.end() && computerShips==0)
	{
		return true;
	}
	return false;
}

void GameManager::newPlayerShip(HumanStrategy &schemePlayer, GameObjects &gameObjects, TextDisplay &td, const std::map<size_t, std::shared_ptr<Ammunition>> &ammunitions, size_t &playerID, const size_t &playerTypeShID)
{
	ObjectCreator oc;
	playerID = oc.createShip(gameObjects, {SCREEN_WIDTH/2, SCREEN_HEIGHT-10}, "Statki.txt", td, playerTypeShID, ammunitions);
	gameObjects[playerID]->setDirection(true);
	schemePlayer.loadObject(gameObjects[playerID]);
	schemePlayer.checkPlayerShipDestroyed();
}