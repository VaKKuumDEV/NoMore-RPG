#include "DecorGameObject.h"

DecorGameObject::DecorGameObject(int x, int y, int borderX, int borderY): GameObject(x, y, borderX, borderY) {
	
}

bool DecorGameObject::isCollisingWith(GameObject& obj) {
	if (typeid(obj) == typeid(DecorGameObject) && ((DecorGameObject&)obj).isThick()) return false;
	return GameObject::isCollisingWith(obj);
}