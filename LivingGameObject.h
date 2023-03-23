#include "GameObject.h"

#pragma once
class LivingGameObject: public GameObject
{
public:
	enum Orientation {
		LEFT,
		RIGHT,
	};
private:
	int health = 0;
	int maxHealth = 0;
	Orientation currentOrientation = RIGHT;
public:
	LivingGameObject(int x, int y, int borderX, int borderY, int health, int maxHealth);
	bool isLive() { return health > 0; }
	Orientation getOrientation() { return currentOrientation; }
	void heal(int healPoints);
	void applyDamage(int damagePoints);
	void processDamage(int damaged);
	void processDeath();
	void addX(int diffX);
	void addY(int diffY);
	void setOrientation(bool isLeft);
};

