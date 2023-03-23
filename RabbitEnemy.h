#include "EnemyObject.h"

#pragma once
class RabbitEnemy : public EnemyObject
{
public:
	RabbitEnemy(int x, int y, int borderX, int borderY);
	GameObject::Matrix getMatrix() override;
	void process() override;
};

