#include "LivingGameObject.h"

#pragma once
class PlayerObject: public LivingGameObject
{
private:
	float damageRadius = 1.5;
public:
	PlayerObject(int x, int y, int borderX, int borderY);
	GameObject::Matrix getMatrix() override;
	void process() override;
};

