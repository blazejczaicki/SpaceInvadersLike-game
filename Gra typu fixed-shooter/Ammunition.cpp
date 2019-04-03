#include "Ammunition.h"

Ammunition::Ammunition(const size_t &_id, const int &_quantity, const double &_fireRatio)
	:id{ _id }, quantity{ _quantity }, fireRatio{ _fireRatio }
{}

bool Ammunition::changeQuantity()
{
	if (quantity > 0)
	{
		quantity--;
		return true;
	}
	return false;
}
size_t Ammunition::getId() const
{
	return id;
}
double Ammunition::getFireRatio() const
{
	return fireRatio;
}
int Ammunition::getNumAmmo() const
{
	return quantity;
}