#include "LivingGameObject.h"

#pragma once
class RabbitEnemy : public LivingGameObject
{
private:
	int walkingTicks = 5, walkingCalculatingTicks = 60;
public:
	RabbitEnemy(int x, int y, int borderX, int borderY);
	GameObject::Matrix getMatrix() override;
	void process() override;
	void preprocess() override;
	bool isThick() override { return false; }
	int applyDamage(int damagePoints, LivingGameObject* damager) override;
	void calculateMotion() override;
	void executeCollision(GameObject* obj) override;
	int getScore() override { return 2; }
};

