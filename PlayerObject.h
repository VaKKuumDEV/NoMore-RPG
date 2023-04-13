#include "LivingGameObject.h"
#include "DecorGameObject.h"

#pragma once
class PlayerObject: public LivingGameObject
{
private:
	float damageRadius = 1.5;
public:
	PlayerObject(int x, int y, int borderX, int borderY);
	void executeCollision(GameObject* obj) override;
	GameObject::Matrix getMatrix() override;
	void process() override;
	void preprocess() override;
};

