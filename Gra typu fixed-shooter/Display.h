#pragma once
#include<tuple>
#include <set>
#include <thread>
#include <mutex>
#include <chrono>
#include"Point.h"
#include"ScreenData.h"
class GameObjects;
class HumanStrategy;
class TextDisplay;

class Display
{
protected:
	std::mutex mts;
	virtual void printGrid() = 0;
	virtual void printObject(const size_t objectId, const Point<double>& pos, const std::set<Point<int>>& obj) = 0;
	virtual std::set<Point<int>> getObject(const size_t &objectId) = 0;
	virtual void displayUI(const int &hp, const size_t &lifes, const size_t &ammoID, const int &ammo) const = 0;
	virtual bool menu(size_t &scenarioID, size_t &playerTypeShID) = 0;
	virtual void displayEnd(bool win) = 0;
	virtual void playerMove(char &quit, HumanStrategy &scheme, GameObjects &gameObjects, GameObjects &playerGameObjects, std::mutex &mtx, TextDisplay &td) = 0;
	virtual void wait() = 0;
};