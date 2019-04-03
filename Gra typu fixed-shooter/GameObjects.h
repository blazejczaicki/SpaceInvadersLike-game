#pragma once
#include<memory>
#include<mutex>
#include"GameObject.h"

class GameObjects
{
	typedef std::map<size_t, std::shared_ptr<GameObject>> map_t;
	map_t mapa;
public:
	size_t erase(const size_t &id);
	map_t::iterator erase(const map_t::iterator &it);
	map_t::iterator begin();
	map_t::iterator end();
	map_t::iterator find(const size_t& x);
	std::shared_ptr<GameObject> & operator[](const size_t &key);
	void clear();
	void insert(map_t::iterator first, map_t::iterator last);
};