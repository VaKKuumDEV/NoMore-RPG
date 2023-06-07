#include "LivingGameObject.h"

#pragma once
class PlayerObject: public LivingGameObject
{
public:
	const int MIN_DAMAGE = 1, MAX_DAMAGE = 3;
	PlayerObject(int x, int y, int borderX, int borderY);
	bool isThick() override { return false; }
	void executeCollision(GameObject* obj) override;
	int executeDamage(LivingGameObject* obj) override;
	GameObject::Matrix getMatrix() override;
	void process() override;
	void preprocess() override;
};

