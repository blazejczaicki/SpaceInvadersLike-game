#pragma once


class Ammunition
{
	int quantity;
	size_t id;// id pocisku
	double fireRatio;
public:
	Ammunition() = delete;
	Ammunition(const size_t &_id, const int &_quantity, const double &_fireRatio);
	bool changeQuantity();
	size_t getId() const;
	double getFireRatio() const;
	int getNumAmmo() const;
};
