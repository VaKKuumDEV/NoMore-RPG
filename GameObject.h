#include <vector>
#include <string>

#pragma once

class GameObject {
public:
	struct Point {
		int x, y;
	};
private:
	int diffX = 0, diffY = 0;
	int borderX, borderY;
	bool closed = false;
protected:
	int x, y;
public:
	using Matrix = std::vector<std::vector<char>>;
	GameObject(int x, int y, int borderX, int borderY);
	virtual int getX() { return x; }
	virtual int getY() { return y; }
	int getDiffX() { return diffX; }
	int getDiffY() { return diffY; }
	void setDiffX(int dX) { diffX = dX; }
	void setDiffY(int dY) { diffY = dY; }
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
	int getBorderX() { return borderX; }
	int getBorderY() { return borderY; }
	Point getPoint() { return Point{ x = this->x, y = this->y }; }
	int getWidth();
	int getHeight();
	bool isClosed() { return closed; }
	void setClosed() { closed = true; }
	virtual bool isCollisingWith(Matrix matr, int x, int y, int width, int height);
	virtual bool isCollisingWith(GameObject& obj);
	void cancelMoving();
	virtual void executeCollision(GameObject* obj);
	virtual Matrix getMatrix() = 0;
	virtual void preprocess();
	virtual void process() = 0;
};