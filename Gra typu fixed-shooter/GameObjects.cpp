#include "GameObjects.h"

size_t GameObjects::erase(const size_t &id)
{
	return mapa.erase(id);
}

GameObjects::map_t::iterator GameObjects::erase(const map_t::iterator &it)
{
	return mapa.erase(it);
}

GameObjects::map_t::iterator GameObjects::begin()
{
	return mapa.begin();
}
GameObjects::map_t::iterator GameObjects::end()
{
	return mapa.end();
}
GameObjects::map_t::iterator GameObjects::find(const size_t& x)
{
	return mapa.find(x);
}

std::shared_ptr<GameObject> & GameObjects::operator[](const size_t &key)
{
	return mapa[key];
};

void GameObjects::clear()
{
	mapa.clear();
}

void GameObjects::insert(map_t::iterator first, map_t::iterator last)
{
	for (map_t::iterator it = first; it != last; ++it)
	{
		mapa.insert(*it);
	}
}