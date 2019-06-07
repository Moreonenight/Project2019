#include "Equipment.h"

Equipment::Equipment(std::string name) {
	if (name == "Shoe") {
		plusDamage = 0;
		plusMaxHp = 0;
		plusMoveSpeed = 100;
	}
	else if (name == "Hat") {
		plusDamage = 0;
		plusMaxHp = 10000;
		plusMoveSpeed = 0;
	}
	else if (name == "Sword") {
		plusDamage = 400;
		plusMaxHp = 0;
		plusMoveSpeed = 0;
	}
	isOccupied = true;
	Price = 200;
	Name = name;
}