#pragma once
#include <chrono>
#include <map>
#include<memory>
#include "Point.h"
#include "Ammunition.h"
class Cannon
{
	double angle, interval;
	int radius;//wraz z angle do tworzenia punktu przeznaczenia dla pocisku
	Point<double> position;
	std::chrono::high_resolution_clock::time_point startTime;
	std::chrono::high_resolution_clock::time_point controlTime;
	std::map<size_t, std::shared_ptr<Ammunition>> ammunitionTypes;
	size_t currentAmmoID;
public:
	Cannon() = delete;
	Cannon(const double &ang, const Point<double> &pos, const double &_interval);

	bool checkInterval();
	bool cannonShot();
	void changeAmmo();

	void setCurrentAmmoID(const size_t &_id);
	void setAmmo(const std::shared_ptr<Ammunition> &_ammo);

	size_t getCurrentAmmoID() const;
	int getNumberOfCurrentAmmo() const;
	Point<double> getPosition(const Point<double> &shipPos) const;
	Point<int> getDestination(const Point<double> &shipPos) const;
};