#include "GameObject.h"

#pragma once
class LivingGameObject: public GameObject
{
public:
	enum Orientation {
		LEFT,
		RIGHT,
	};
	enum EnemyTypes {
		NEUTRAL,
		AGRESSIVE,
		FRIENDLY,
		PLAYER,
	};
	enum EnemyActions {
		STAING_FIRST,
		STAING_SECOND,
		WALKING_FIRST,
		WALKING_SECOND,
		DAMAGING,
	};
	const int ACTION_SKIP = 10;
private:
	int health = 0;
	int maxHealth = 0;
	Orientation currentOrientation = RIGHT;
	double visionRadius;
	int skippingTicks = ACTION_SKIP;
	EnemyTypes type;
	EnemyActions action = STAING_FIRST;
public:
	LivingGameObject(int x, int y, int borderX, int borderY, int health, int maxHealth, double radius, EnemyTypes type);
	bool isLive() { return health > 0; }
	Orientation getOrientation() { return currentOrientation; }
	void heal(int healPoints);
	void applyDamage(int damagePoints);
	void processDamage(int damaged);
	void processDeath();
	void addX(int diffX);
	void addY(int diffY);
	void setOrientation(bool isLeft);
	double getRadius() { return visionRadius; }
	EnemyTypes getType() { return type; }
	EnemyActions getAction() { return action; }
	bool isInVisionPole(int x, int y);
	void setWalkingAnimation();
	virtual bool isThick() { return true; }
	void process() override;
};

