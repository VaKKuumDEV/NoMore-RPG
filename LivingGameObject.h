#include "GameObject.h"
#include "DecorGameObject.h"

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
protected:
	int damageCooldown = 0;
	GameObject::Point motionPoint = GameObject::Point{ -1, -1 };
	LivingGameObject* lastDamager = NULL;
public:
	LivingGameObject(int x, int y, int borderX, int borderY, int health, int maxHealth, double radius, EnemyTypes type);
	bool isLive() { return health > 0; }
	Orientation getOrientation() { return currentOrientation; }
	void heal(int healPoints);
	virtual int applyDamage(int damagePoints, LivingGameObject* damager);
	virtual int processDamage(int damaged);
	void processDeath();
	void addX(int diffX);
	void addY(int diffY);
	int getHealth() { return health; }
	int getMaxHealth() { return maxHealth; }
	void setOrientation(bool isLeft);
	double getRadius() { return visionRadius; }
	EnemyTypes getType() { return type; }
	EnemyActions getAction() { return action; }
	int getDamageCooldown() { return damageCooldown; }
	double getDistance(int x, int y);
	bool isInVisionPole(int x, int y, int width, int height);
	void setWalkingAnimation();
	void setDamagingAnimation();
	virtual int executeDamage(LivingGameObject* obj);
	void process() override;
	void executeCollision(GameObject* obj) override;
	virtual void calculateMotion() { motionPoint = GameObject::Point{ -1,-1 }; }
	virtual int getScore() { return 0; }
};

