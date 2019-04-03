#pragma once
#include <chrono>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include "ComputerStrategy.h"
#include "ObjectCreator.h"
#include "GameObjects.h"
#include "TextDisplay.h"
#include "Ammunition.h"
#include "ScreenData.h"
#include "HumanStrategy.h"

class GameManager
{
	size_t idScenario, nextWave;
	std::map<size_t, size_t> numShipsOnWave;//id fali i liczba statkow na fale
	std::map<size_t, size_t> schemeOnWave;// schemat na fale 
	std::map<size_t, std::shared_ptr<ComputerStrategy>> computerSchemes;
	double waveInterval;
	int lifes;
	std::chrono::high_resolution_clock::time_point startTime;
	std::chrono::high_resolution_clock::time_point controlTime;
	void loadScenario(std::string filename);
	void loadComputerSchemes(const std::string &filename);
public:
	GameManager() = delete;
	GameManager(size_t scenarioID);

	void addWave( GameObjects &gameObjects, TextDisplay &td,const std::map<size_t, std::shared_ptr<Ammunition>> &ammunitions);
	void removeFromScheme(const size_t &schemeID, const size_t &idObject);
	void newPlayerShip(HumanStrategy &schemePlayer, GameObjects &gameObjects, TextDisplay &td, const std::map<size_t, std::shared_ptr<Ammunition>> &ammunitions, size_t &playerID, const size_t &playerTypeShID);
	void changeLifes();

	bool checkWave(size_t &compShipsAlive);
	void checkComputerStrategies(GameObjects &gameObjects, TextDisplay &td);
	bool checkLifes();
	bool checkWin(size_t computerShips);
	
	int getShipsOfWave();
	int getLifes();
};