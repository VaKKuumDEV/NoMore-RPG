#include <vector>

#pragma once

class GameObject {
private:
	int x, y;
	int borderX, borderY;
public:
	using Matrix = std::vector<std::vector<char>>;
	GameObject(int x, int y, int borderX, int borderY);
	int getX() { return x; }
	int getY() { return y; }
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
	int getBorderX() { return borderX; }
	int getBorderY() { return borderY; }
	int getWidth();
	int getHeight();
	bool isCollisingWith(GameObject& obj);
protected:
	virtual Matrix getMatrix() = 0;
	virtual void process() = 0;
};