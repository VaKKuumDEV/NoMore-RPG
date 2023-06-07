#include <typeinfo>
#include "GameObject.h"

#pragma once
class DecorGameObject : public GameObject
{
public:
	DecorGameObject(int x, int y, int borderX, int borderY);
	bool isCollisingWith(GameObject& obj) override;
};

