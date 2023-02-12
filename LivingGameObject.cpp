#include "LivingGameObject.h"

LivingGameObject::LivingGameObject(int x, int y, int health, int maxHealth) : GameObject(x, y) {
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