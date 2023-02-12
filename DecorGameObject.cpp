#include "DecorGameObject.h"

DecorGameObject::DecorGameObject(int x, int y, bool isThick): GameObject(x, y) {
	this->isThick = isThick;
}

bool DecorGameObject::isCollisingWith(GameObject& obj) {
	if (this->isThick) return false;
	if (typeid(obj) == typeid(DecorGameObject) && ((DecorGameObject&)obj).isThickingObject()) return false;
	return GameObject::isCollisingWith(obj);
}