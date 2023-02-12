#include <vector>

#pragma once

class GameObject {
private:
	int x, y;
public:
	using Matrix = std::vector<std::vector<char>>;
	GameObject(int x, int y);
	int getX() { return x; };
	int getY() { return y; };
	int getWidth();
	int getHeight();
	bool isCollisingWith(GameObject& obj);
protected:
	virtual Matrix getMatrix() = 0;
	virtual void process() = 0;
};