#include "LabelObject.h"

LabelObject::LabelObject(std::string text, bool isAwaitingDeath, int awaitingDeathTicks, int x, int y, int borderX, int borderY) : DecorGameObject(x, y, borderX, borderY, true)
{
	this->text = text;
	this->awaitDeath = isAwaitingDeath;
	this->awaitDeathTicks = awaitingDeathTicks;
}

bool LabelObject::isCollisingWith(GameObject& obj)
{
	return false;
}

GameObject::Matrix LabelObject::getMatrix()
{
	GameObject::Matrix matr = std::vector<std::vector<char>>(1, std::vector<char>(text.size(), ' '));
	for (int i = 0; i < matr.size(); i++) {
		for (int j = 0; j < matr[i].size(); j++) matr[i][j] = text[j];
	}

	return matr;
}

void LabelObject::process()
{
	if (isAwaitDeath()) {
		awaitDeathTicks--;
		if (getAwaitDeathTicks() <= 0) setClosed();
	}
}
