#include "LivingGameObject.h"

LivingGameObject::LivingGameObject(int x, int y, int borderX, int borderY, int health, int maxHealth, double radius, EnemyTypes type) : GameObject(x, y, borderX, borderY) {
	this->health = health;
	this->maxHealth = maxHealth;
	this->type = type;
	this->visionRadius = radius;
}

double LivingGameObject::getDistance(int x, int y) {
	int centerX = getX() + getWidth() / 2;
	int centerY = getY() + getHeight() / 2;

	return sqrt(pow((double)x - centerX, 2) + pow((double)y - centerY, 2));
}

bool LivingGameObject::isInVisionPole(int x, int y, int width, int height) {
	int centerX = getX() + getWidth() / 2;
	int centerY = getY() + getHeight() / 2;

	int enemyCenterX = x + width / 2;
	int enemyCenterY = y + height / 2;

	int xDiff = enemyCenterX - centerX;
	if (getOrientation() == LEFT && xDiff > 0) return false;
	else if (getOrientation() == RIGHT && xDiff < 0) return false;
	double distance = getDistance(enemyCenterX, enemyCenterY);

	return distance <= visionRadius;
}

int LivingGameObject::applyDamage(int damagePoints, LivingGameObject* damager) {
	int calculatedDamage = processDamage(damagePoints);

	this->health -= calculatedDamage;
	if (this->health <= 0) processDeath();
	damageCooldown = 10;

	return calculatedDamage;
}

void LivingGameObject::heal(int healPoints) {
	this->health += healPoints;
	if (this->health > this->maxHealth) this->health = this->maxHealth;
}

int LivingGameObject::processDamage(int damaged) {
	return damaged;
}

void LivingGameObject::processDeath() {
	setClosed();
}

void LivingGameObject::addX(int diffX) {
	int calculatedX = getX() + diffX;
	if (calculatedX < 0) calculatedX = 0;
	else if (calculatedX > getBorderX()) calculatedX = getBorderX();

	setX(calculatedX);
}

void LivingGameObject::addY(int diffY) {
	int calculatedY = getY() + diffY;
	if (calculatedY < 0) calculatedY = 0;
	else if (calculatedY > getBorderY()) calculatedY = getBorderY();

	setY(calculatedY);
}

void LivingGameObject::setOrientation(bool isLeft) {
	currentOrientation = isLeft ? LEFT : RIGHT;
}

void LivingGameObject::setWalkingAnimation()
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

void LivingGameObject::process()
{
	if (getDiffX() != 0 || getDiffY() != 0) setWalkingAnimation();
	if (getDiffX() > 0) setOrientation(false);
	else if(getDiffX() < 0) setOrientation(true);

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
		else if (action == DAMAGING) {
			action = STAING_FIRST;
			skippingTicks = ACTION_SKIP;
		}
	}

	if (damageCooldown > 0) damageCooldown--;
}

void LivingGameObject::executeCollision(GameObject* obj) {
	if (!obj->isThick()) {
		if (isCollisingWith(*obj) || obj->isCollisingWith(*this)) cancelMovingX();
		if (isCollisingWith(*obj) || obj->isCollisingWith(*this)) cancelMovingY();
	}
}

void LivingGameObject::setDamagingAnimation() {
	action = DAMAGING;
	skippingTicks = ACTION_SKIP / 2;
}

int LivingGameObject::executeDamage(LivingGameObject* obj) {
	if (obj->isClosed() || !obj->isLive()) return 0;

	return 0;
}