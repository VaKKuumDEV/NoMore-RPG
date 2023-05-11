#include "DecorGameObject.h"
#include <string>

#pragma once
class LabelObject : public DecorGameObject
{
private:
	bool awaitDeath = false;
	int awaitDeathTicks = 0;
	std::string text;
public:
	LabelObject(std::string text, bool isAwaitingDeath, int awaitingDeathTicks, int x, int y, int borderX, int borderY);
	bool isCollisingWith(GameObject& obj);
	bool isAwaitDeath() { return awaitDeath; }
	int getAwaitDeathTicks() { return awaitDeathTicks; }
	std::string getText() { return text; }
	void setText(std::string text) { this->text = text; }
	int setX(int x) { this->x = x; }
	int setY(int y) { this->y = y; }
	GameObject::Matrix getMatrix() override;
	void process() override;
};

