#include "DecorGameObject.h"

#pragma once
class BorderDecorObject : public DecorGameObject
{
private:
	int screenWidth = 0, screenHeight = 0;
public:
	BorderDecorObject(int borderX, int borderY);
	GameObject::Point getScreen() { return GameObject::Point{ screenWidth, screenHeight }; }
	void setScreen(GameObject::Point point) { screenWidth = point.x; screenHeight = point.y; }
	void process() override;
	void preprocess() override;
	GameObject::Matrix getMatrix() override;
};