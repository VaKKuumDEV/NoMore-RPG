#include "EnemyObject.h"

EnemyObject::EnemyObject(int x, int y, int borderX, int borderY, int health, int maxHealth, double radius, EnemyTypes type):LivingGameObject(x, y, borderX, borderY, health, maxHealth)
{
	visionRadius = radius;
	this->type = type;
}

bool EnemyObject::isInVisionPole(int x, int y) {
	return pow((double)x - getX(), 2) + pow((double)y - getY(), 2) <= visionRadius;
}

void EnemyObject::setWalkingAnimation()
{
	if (action == WALKING_FIRST && skippingTicks <= 0) {
		action = WALKING_SECOND;
		skippingTicks = ACTION_SKIP;
	}
	else if (action == WALKING_SECOND && skippingTicks <= 0) {
		action = WALKING_FIRST;
		skippingTicks = ACTION_SKIP;
	}
	else if (action == STAING_FIRST || action == STAING_SECOND) {
		action = WALKING_FIRST;
		skippingTicks = ACTION_SKIP;
	}
}

void EnemyObject::process()
{
	if (skippingTicks > 0) skippingTicks--;
	else {
		if (action == STAING_FIRST) {
			action = STAING_SECOND;
			skippingTicks = ACTION_SKIP;
		}
		else if (action == STAING_SECOND) {
			action = STAING_FIRST;
			skippingTicks = ACTION_SKIP;
		}
		else if (action == WALKING_FIRST) {
			action = STAING_FIRST;
			skippingTicks = ACTION_SKIP;
		}
		else if (action == WALKING_SECOND) {
			action = STAING_FIRST;
			skippingTicks = ACTION_SKIP;
		}
	}
}
