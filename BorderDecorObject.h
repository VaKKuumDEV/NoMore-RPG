#include "DecorGameObject.h"

#pragma once
class BorderDecorObject : public DecorGameObject
{
private:
	int screenWidth = 0, screenHeight = 0, screenOffsetX = 0, screenOffsetY = 0;
public:
	const char SYMBOL = '*';
	BorderDecorObject(int borderX, int borderY);
	bool isThick() override { return false; }
	GameObject::Point getScreen() { return GameObject::Point{ screenWidth, screenHeight }; }
	GameObject::Point getOffset() { return GameObject::Point{ screenOffsetX, screenOffsetY }; }
	void setScreen(GameObject::Point pointScreen, GameObject::Point pointOffset) { screenWidth = pointScreen.x; screenHeight = pointScreen.y; screenOffsetX = pointOffset.x; screenOffsetY = pointOffset.y; }
	void process() override;
	void preprocess() override;
	GameObject::Matrix getMatrix() override;
	int getX() override { return screenOffsetX; }
	int getY() override { return screenOffsetY; }
};