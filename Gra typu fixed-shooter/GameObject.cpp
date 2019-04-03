#include"GameObject.h"
#include "Fire.h"
#include "GameObjects.h"

GameObject::GameObject(const Point<double> &xy, const std::set<Point<int>> &points, const size_t &_id, const Point<int> &_size, const int &_hp, const std::string &_name, std::vector<std::shared_ptr<Cannon>> _cannons, const int &_damage)
	: position{ xy }, size{ _size }, id{ _id }, name{ _name }, hp{ _hp }, speed{ 1 }, schemeID{ 0 }, cannons{ _cannons }, damage{_damage }
{
	destinationPoint = xy;
	upDirection = false;
	for (auto p : points) { objectPoints.insert(p); };
}

void GameObject::fire(Fire fire, TextDisplay &td, GameObjects &gameObjects)
{
	for (auto& cannon : cannons)
	{

		if (fire.check(cannon))
		{
			fire.shot(cannon, position, gameObjects, td, upDirection);
		}
	}
}

void GameObject::fire(Fire fire, TextDisplay &td, GameObjects &playerGameObjects, std::mutex &mtx)
{
	for (auto& cannon : cannons)
	{
		if (fire.check(cannon))
		{
			fire.shot(cannon, position, playerGameObjects, td, upDirection, mtx);
		}
	}
}

void GameObject::changeAmmo(const char &c)
{
	for (auto& cannon : cannons)
	{
		cannon->changeAmmo();
	}
}

void GameObject::changePosition()
{
	Point<double> d = { static_cast<double>(destinationPoint.x) - position.x, static_cast<double>(destinationPoint.y) - position.y };
	double l = std::sqrt(d.x*d.x + d.y * d.y);
	if(!(std::fabs(l)<0.001))
	{ 
	double l2 = 1.0*speed / l;
	d.x = d.x*l2;
	d.y = d.y*l2;
	if (std::sqrt(d.x*d.x + d.y * d.y)<=l)
	{
		position = { round(position.x + d.x) , round(position.y + d.y) };
	}
	else
	{
		position = destinationPoint;
	}
	}
 }

void GameObject::damageObject(const int &hp2, const int &dmg)
{
	if (hp2 > 0)
		hp = hp - hp2 - dmg;
}

void GameObject::destroyObject()
{
	objectPoints.clear();
	hp = 0;
}

bool GameObject::destroyed()
{
	return hp <= 0;
}

void GameObject::setDirection(bool d)
{
	upDirection = d;
}
void GameObject::setPosition(const Point<double> &p)
{
	position = p;
}
void GameObject::setDestination(const Point<int> &d,const int &s)
{
	destinationPoint = d;
	speed = s;
}
void GameObject::setPositionOnGrid(const std::vector<int> &idMap)
{
	positionOnGrid = idMap;
}

void GameObject::setSchemeID(const size_t &id)
{
	schemeID = id;
}

size_t GameObject::getSchemeID() const
{
	return schemeID;
}
std::set<Point<int>> GameObject::getObjectPoints() const
{
	Point<int> pos;
	pos = position;
	std::set<Point<int>> posObject;
	std::transform(objectPoints.begin(), objectPoints.end(), std::inserter(posObject, posObject.end()),
		[&pos](const Point<int>& p) {return p + pos; });
	return posObject;
}
Point<int> GameObject::getDestination() const
{
	return destinationPoint;
}
std::vector<int> GameObject::getPositionOnGrid() const
{
	return positionOnGrid;
}
size_t GameObject::getID() const
{
	return id;
}
Point<double> GameObject::getPosition() const
{
		return position;
}
Point<int> GameObject::getSize() const
{
	return size;
}
std::string GameObject::getName() const
{
	return name;
}
int GameObject::getHP() const
{
	return hp;
}

int GameObject::getDamage() const
{
	return damage;
}

size_t GameObject::getAmmoID() const
{
	return cannons[0]->getCurrentAmmoID();
}

int  GameObject::getAmmoNumber() const
{
	return cannons[0]->getNumberOfCurrentAmmo();
}