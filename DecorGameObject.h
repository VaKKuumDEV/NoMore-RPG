#include <typeinfo>
#include "GameObject.h"

#pragma once
class DecorGameObject : public GameObject
{
private:
	bool isThick;
public:
	DecorGameObject(int x, int y, bool isThick);
	bool isCollisingWith(GameObject& obj);
	bool isThickingObject() { return isThick; }
};

