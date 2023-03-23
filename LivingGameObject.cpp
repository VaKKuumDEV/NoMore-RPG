#include "LivingGameObject.h"

LivingGameObject::LivingGameObject(int x, int y, int borderX, int borderY, int health, int maxHealth) : GameObject(x, y, borderX, borderY) {
	this->health = health;
	this->maxHealth = maxHealth;
}

void LivingGameObject::applyDamage(int damagePoints) {
	this->health -= damagePoints;
	if (this->health <= 0) processDeath();
	else processDamage(damagePoints);
}

void LivingGameObject::heal(int healPoints) {
	this->health += healPoints;
	if (this->health > this->maxHealth) this->health = this->maxHealth;
}

void LivingGameObject::processDamage(int damaged) {

}

void LivingGameObject::processDeath() {

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