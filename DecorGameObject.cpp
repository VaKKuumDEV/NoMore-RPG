#include "DecorGameObject.h"

DecorGameObject::DecorGameObject(int x, int y, int borderX, int borderY, bool isThick): GameObject(x, y, borderX, borderY) {
	this->isThick = isThick;
}

bool DecorGameObject::isCollisingWith(GameObject& obj) {
	if (this->isThick) return false;
	if (typeid(obj) == typeid(DecorGameObject) && ((DecorGameObject&)obj).isThickingObject()) return false;
	return GameObject::isCollisingWith(obj);
}