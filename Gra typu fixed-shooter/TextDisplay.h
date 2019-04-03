#pragma once
#include<vector>
#include<curses.h>
#include<sstream>
#include<algorithm>
#include"Display.h"


class TextDisplay : public Display
{
	int rows, columns;
	std::vector<std::string> objects;
public:
	TextDisplay();
	~TextDisplay();
	void printGrid() override;
	void printObject(const size_t objectId, const Point<double>& pos, const std::set<Point<int>>& obj) override;
	std::set<Point<int>> getObject(const size_t &objectId) override;
	void wait() override;
	bool menu(size_t &scenarioID, size_t &playerTypeShID) override;
	void displayUI(const int &hp, const size_t &lifes, const size_t &ammoID, const int &ammo) const override;
	void displayEnd(bool win) override;
	void playerMove(char &quit, HumanStrategy &scheme, GameObjects &gameObjects, GameObjects &playerGameObjects, std::mutex &mtx, TextDisplay &td) override;

	void printText(const std::string& text, const Point<double>& p) const;
	size_t loadObject(const std::string& object);
};
