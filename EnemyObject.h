#include "LivingGameObject.h"
#include <cmath>

#pragma once
class EnemyObject : public LivingGameObject
{
public:
	enum EnemyTypes {
		NEUTRAL,
		AGRESSIVE,
		FRIENDLY,
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
	double visionRadius;
	int skippingTicks = ACTION_SKIP;
	EnemyTypes type;
	EnemyActions action = STAING_FIRST;
public:
	EnemyObject() :LivingGameObject(0, 0, 0, 0, 0, 0){ }
	EnemyObject(int x, int y, int borderX, int borderY, int health, int maxHealth, double radius, EnemyTypes type);
	double getRadius() { return visionRadius; }
	EnemyTypes getType() { return type; }
	EnemyActions getAction() { return action; }
	bool isInVisionPole(int x, int y);
	void setWalkingAnimation();
	void process() override;
};

