#include "LivingGameObject.h"

#pragma once
class RabbitEnemy : public LivingGameObject
{
public:
	RabbitEnemy(int x, int y, int borderX, int borderY);
	GameObject::Matrix getMatrix() override;
	void process() override;
	void preprocess() override;
	bool isThick() override { return false; }
};

