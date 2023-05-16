#include "LivingGameObject.h"

LivingGameObject::LivingGameObject(int x, int y, int borderX, int borderY, int health, int maxHealth, double radius, EnemyTypes type) : GameObject(x, y, borderX, borderY) {
	this->health = health;
	this->maxHealth = maxHealth;
	this->type = type;
	this->visionRadius = radius;
}

bool LivingGameObject::isInVisionPole(int x, int y, int width, int height) {
	int centerX = getX() + getWidth() / 2;
	int centerY = getY() + getHeight() / 2;

	int enemyCenterX = x + width / 2;
	int enemyCenterY = y + height / 2;

	int xDiff = enemyCenterX - centerX;
	if (getOrientation() == LEFT && xDiff > 0) return false;
	else if (getOrientation() == RIGHT && xDiff < 0) return false;

	return sqrt(pow((double)enemyCenterX - centerX, 2) + pow((double)enemyCenterY - centerY, 2)) <= visionRadius;
}

int LivingGameObject::applyDamage(int damagePoints) {
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
	if (calculatedY <= 0) calculatedY = 1;
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
	auto castedToLivingObject = dynamic_cast<LivingGameObject*>(obj);
	if (castedToLivingObject != NULL && !castedToLivingObject->isThick()) cancelMoving();

	auto castedToDecorObject = dynamic_cast<DecorGameObject*>(obj);
	if (castedToDecorObject != NULL && !castedToDecorObject->isThickingObject()) cancelMoving();
}

void LivingGameObject::setDamagingAnimation() {
	action = DAMAGING;
	skippingTicks = ACTION_SKIP / 2;
}

int LivingGameObject::executeDamage(LivingGameObject* obj) {
	if (obj->isClosed()) return 0;

	return 0;
}