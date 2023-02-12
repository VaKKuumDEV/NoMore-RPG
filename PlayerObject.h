#include "LivingGameObject.h"

#pragma once
class PlayerObject: public LivingGameObject
{
private:
	const int ACTION_SKIP = 10;
	enum PlayerActions {
		STAING_FIRST,
		STAING_SECOND,
		WALKING_FIRST,
		WALKING_SECOND,
		DAMAGING,
	};
	float damageRadius = 1.5;
	int skippingTicks = ACTION_SKIP;
	PlayerActions currentAction = STAING_FIRST;
public:
	PlayerObject(int x, int y);
	GameObject::Matrix getMatrix() override;
	void process() override;
};

