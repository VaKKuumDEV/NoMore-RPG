#include "LivingGameObject.h"

#pragma once
class PlayerObject: public LivingGameObject
{
public:
	const int DAMAGE = 2;
	PlayerObject(int x, int y, int borderX, int borderY);
	void executeCollision(GameObject* obj) override;
	int executeDamage(LivingGameObject* obj) override;
	GameObject::Matrix getMatrix() override;
	void process() override;
	void preprocess() override;
};

