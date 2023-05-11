#include <typeinfo>
#include "GameObject.h"

#pragma once
class DecorGameObject : public GameObject
{
private:
	bool isThick;
public:
	DecorGameObject(int x, int y, int borderX, int borderY, bool isThick);
	bool isCollisingWith(GameObject& obj) override;
	bool isThickingObject() { return isThick; }
};

