#include <vector>

#pragma once

class GameObject {
public:
	struct Point {
		int x, y;
	};
	const char T = '@';
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
	Point getPoint() { return Point{ x = this->x, y = this->y }; }
	int getWidth();
	int getHeight();
	bool isCollisingWith(GameObject& obj);
	virtual Matrix getMatrix() = 0;
	virtual void process() = 0;
};