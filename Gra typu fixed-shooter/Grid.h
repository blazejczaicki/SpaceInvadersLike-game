#pragma once
#include<iostream>
#include<map>
#include<set>
#include <vector>
#include"Point.h"
#include "GameObject.h"
#include"GameObjects.h"

class Grid
{
	unsigned TILE_HEIGHT;
	unsigned TILE_WIDTH;
	unsigned NUMBER_COLUMNS;
	unsigned NUMBER_LINES;
	std::map<int, std::set<unsigned>> objectsOnQuadrants;
public:
	Grid(unsigned TILE_HEIGHT, unsigned TILE_WIDTH, unsigned NUMBER_COLUMNS, unsigned NUMBER_LINES);
	~Grid()=default;
	
	void giveObjectOnQuadrant(const GameObjects &allObjects);
	void checkingCollisionsAreas(GameObjects &allObjects);
	void calculateIDMap(std::vector<int> &idMap, std::shared_ptr<GameObject> gameObject);

	unsigned getTileHeight();
	unsigned getTileWidth();
};