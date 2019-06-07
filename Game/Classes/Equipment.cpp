#include "Equipment.h"

Equipment::Equipment(std::string name) {
	if (name == "Helmet") {
		plusMaxHp = 10000;
		plusDamage = 0;
		plusMoveSpeed = 0;
	}
	else if (name == "Shoe") {
		plusMaxHp = 0;
		plusDamage = 0;
		plusMoveSpeed = 70;
	}
	else if (name == "Sword") {
		plusMaxHp = 0;
		plusDamage = 900;
		plusMoveSpeed = 0;
	}
	isOccupied = true;
	Price = 100;
	Name = name;
}