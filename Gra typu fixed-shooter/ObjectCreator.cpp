#include"ObjectCreator.h"

bool ObjectCreator::isObjectName(std::string line)
{
	return std::all_of(line.begin(), line.end(), [](char c) {return c == 32 || isalnum(c); });
}

std::string ObjectCreator::loadBulletData(const std::string &filename, const size_t &spriteID, Point<int>& size, std::string& name, int &damage)
{
	int objectWidth = 0;
	std::string sprite;
	std::string line;
	std::fstream file;
	file.open(filename, std::ios::in);
	size_t id = 1;
	if (file.good())
	{
		while (getline(file, line))
		{
			std::istringstream iss(line);
			if (spriteID == id && *line.begin() == ',')
			{
				line.erase(line.begin());
				if (isObjectName(line))
					name = line;
			}
			else if (spriteID == id && iss>>damage)
			{}
			else if (spriteID == id && line != ";")
			{
				size.y++;
				sprite += line + '\n';
				objectWidth = line.size();
				if (objectWidth > size.x)
					size.x = objectWidth;
			}

			if (line == ";")
			{
				id++;
			}
		}
		file.close();
	}
	return sprite;
};

std::string ObjectCreator::loadShipData(const std::string &filename, const size_t &spriteID, Point<int>& size, std::vector<std::shared_ptr<Cannon>> &cannons, std::string& name, const std::map<size_t, std::shared_ptr<Ammunition>> &ammunitions)
{
	int objectWidth = 0;
	double angleForCannon;
	Point<double> posForCannon;
	double intervalForCannon;
	std::string sprite;
	bool readAmmoID = false;
	std::string line;
	std::fstream file;
	file.open(filename, std::ios::in);
	size_t id = 1;
	if (file.good())
	{
		while (getline(file, line))
		{
			std::istringstream iss(line);
			if (spriteID == id && *line.begin() == '=')
			{
				line.erase(line.begin());
				if (isObjectName(line))
					name = line;
			}
			else if (readAmmoID)
			{
				size_t i;
				while (iss >> i)
				{
					cannons.back()->setAmmo(ammunitions.find(i)->second);
					cannons.back()->setCurrentAmmoID(ammunitions.find(i)->second->getId());
				}
				readAmmoID = false;
			}
			else if (spriteID == id && iss >> angleForCannon >> posForCannon.x >> posForCannon.y >> intervalForCannon)
			{
				cannons.push_back(std::make_shared<Cannon>(angleForCannon, posForCannon, intervalForCannon));
				readAmmoID = true;
			}
			else if (spriteID == id && line != ";")
			{
				size.y++;
				sprite += line + '\n';
				objectWidth = line.size();
				if (objectWidth > size.x)
					size.x = objectWidth;
			}

			if (line == ";")
			{
				id++;
			}
		}
		file.close();
	}
	return sprite;
};

size_t ObjectCreator::createShip(GameObjects& gameObjects, const Point<double>& pos, const std::string &filename, TextDisplay &td, const size_t &idSprite, const std::map<size_t, std::shared_ptr<Ammunition>> &ammunitions)
{
	std::string name;
	std::vector<std::shared_ptr<Cannon>> cannons;
	Point<int> size{ 0, 0 };
	std::string sprite = loadShipData(filename, idSprite, size, cannons, name, ammunitions);
	auto id = td.loadObject(sprite);
	std::set<Point<int>> object = td.getObject(id);
	gameObjects[id] = std::make_unique<Ship>(pos, object, id, size, object.size(), name, cannons, 0);
	return id;
}

size_t ObjectCreator::createBullet(GameObjects& gameObjects, Point<double> bulletPos, const std::string &filename, TextDisplay &td, const size_t &idSprite, const bool &direction)
{
	std::string name;
	int damage;
	std::vector<std::shared_ptr<Cannon>> cannons;
	Point<int> size{ 0, 0 };
	std::string sprite = loadBulletData(filename, idSprite, size, name, damage);/////////////////////////
	if (direction)
		bulletPos = { bulletPos.x - round(size.x*0.5) , bulletPos.y - size.y };
	else
		bulletPos = { bulletPos.x - round(size.x*0.5) , bulletPos.y };

	auto id = td.loadObject(sprite);
	std::set<Point<int>> object = td.getObject(id);
	gameObjects[id] = std::make_unique<Bullet>(bulletPos, object, id, size, object.size(), name, cannons, damage);
	return id;
}