#include "DecorGameObject.h"
#include <string>

#pragma once
class LabelObject : public DecorGameObject
{
private:
	bool awaitDeath = false;
	int awaitDeathTicks = 0;
	std::string text, format;
public:
	LabelObject(std::string text, bool isAwaitingDeath, int awaitingDeathTicks, int x, int y, int borderX, int borderY);
	bool isCollisingWith(GameObject& obj);
	bool isAwaitDeath() { return awaitDeath; }
	int getAwaitDeathTicks() { return awaitDeathTicks; }
	std::string getText() { return text; }
	void setText(std::string text) { this->text = text; }
	void setFormat(std::string format) { this->format = format; }
	std::string getFormat() { return format; }
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
	GameObject::Matrix getMatrix() override;
	void process() override;
};

