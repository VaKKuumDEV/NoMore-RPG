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
	enum PlayerOrientation {
		LEFT,
		RIGHT,
	};

	float damageRadius = 1.5;
	int skippingTicks = ACTION_SKIP;
	PlayerActions currentAction = STAING_FIRST;
	PlayerOrientation currentOrientation = RIGHT;
public:
	PlayerObject(int x, int y, int borderX, int borderY);
	GameObject::Matrix getMatrix() override;
	void process() override;
	void setWalkingAnimation();
	void setOrientation(bool isLeft);
};

