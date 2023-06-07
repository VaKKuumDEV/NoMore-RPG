#include "DecorGameObject.h"

#pragma once
class LittleHouseDecorObject : public DecorGameObject
{
public:
	LittleHouseDecorObject(int x, int y, int borderX, int borderY);
	void process() override;
	GameObject::Matrix getMatrix() override;
	bool isThick() override { return false; }
};

