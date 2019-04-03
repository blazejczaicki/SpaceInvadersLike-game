#include "Cannon.h"

Cannon::Cannon(const double &ang, const Point<double> &pos, const double &_interval)
	: position{ pos }, interval{ _interval }, radius{ 100 }
{
	angle = ang * 0.0174532925199432957692;
	startTime = std::chrono::high_resolution_clock::now();
}

bool Cannon::checkInterval()
{
	controlTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(controlTime - startTime);
	if (timeSpan.count() >= interval * ammunitionTypes[currentAmmoID]->getFireRatio())
	{
		startTime = std::chrono::high_resolution_clock::now();
		return true;
	}
	return false;
}
bool  Cannon::cannonShot()
{
	return ammunitionTypes[currentAmmoID]->changeQuantity();
}
void Cannon::changeAmmo()
{
	auto it = ammunitionTypes.find(currentAmmoID);
		if (++it!=ammunitionTypes.end())
		{
			currentAmmoID = it->first;
		}
		else
		{
			currentAmmoID = ammunitionTypes.begin()->first;
		}
}

void  Cannon::setCurrentAmmoID(const size_t &_id)
{
	currentAmmoID = _id;
}
void  Cannon::setAmmo(const std::shared_ptr<Ammunition> &_ammo)
{
	ammunitionTypes.insert(std::pair<size_t, std::shared_ptr<Ammunition>>(_ammo->getId(), std::make_shared<Ammunition>(*_ammo)));
}

size_t  Cannon::getCurrentAmmoID() const
{
	return currentAmmoID;
}
int Cannon::getNumberOfCurrentAmmo() const
{
	return ammunitionTypes.find(currentAmmoID)->second->getNumAmmo();
}
Point<double>  Cannon::getPosition(const Point<double> &shipPos) const
{
	return position + shipPos;
}
Point<int>  Cannon::getDestination(const Point<double> &shipPos) const
{
	return { static_cast<int>(round((position.x + shipPos.x) + cos(angle)*radius)),static_cast<int>((position.y + shipPos.y) + sin(angle)*radius) };
}