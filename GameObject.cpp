#include "GameObject.h"

GameObject::GameObject(int x, int y, int borderX, int borderY) {
	this->x = x;
	this->y = y;
	this->borderX = borderX;
	this->borderY = borderY;
}

int GameObject::getWidth() {
	Matrix matr = getMatrix();
	int maxWidth = matr[0].size();
	return maxWidth;
}

int GameObject::getHeight() {
	Matrix matr = getMatrix();
	int maxHeight = matr.size();
	return maxHeight;
}

bool GameObject::isCollisingWith(Matrix matr, int x, int y, int width, int height) {
	int minX = std::min(getX(), x);
	int maxX = std::max(getX() + getWidth(), x + width);
	int minY = std::min(getY(), y);
	int maxY = std::max(getY() + getHeight(), y + height);

	int diffX = maxX - minX;
	int diffY = maxY - minY;

	Matrix collisedMatrix = std::vector<std::vector<char>>(diffY, std::vector<char>(diffX, ' '));
	Matrix thisMatrix = getMatrix();

	int thisOtnY = getY() - minY;
	int thisOtnX = getX() - minX;
	for (int i = thisMatrix.size() - 1; i >= 0; i--) {
		int otnY = thisOtnY + i;
		for (int j = 0; j < thisMatrix[i].size(); j++) {
			if (thisMatrix[i][j] == ' ') continue;

			int otnX = thisOtnX + j;
			collisedMatrix[otnY][otnX] = thisMatrix[i][j];
		}
	}

	int collisionLines = 0;
	int enemyOtnY = y - minY;
	int enemyOtnX = x - minX;
	for (int i = matr.size() - 1; i >= 0; i--) {
		int otnY = enemyOtnY + i;
		bool hasCollisionInLine = false;
		for (int j = 0; j < matr[i].size(); j++) {
			if (matr[i][j] == ' ') continue;

			int otnX = enemyOtnX + j;
			if (collisedMatrix[otnY][otnX] != ' ') {
				hasCollisionInLine = true;
			}
		}

		if (hasCollisionInLine) collisionLines++;
	}

	return collisionLines > 0;
}

bool GameObject::isCollisingWith(GameObject& obj) {
	return isCollisingWith(obj.getMatrix(), obj.getX(), obj.getY(), obj.getWidth(), obj.getHeight());
}

void GameObject::executeCollision(GameObject* obj) {

}

void GameObject::preprocess()
{

}

void GameObject::cancelMoving() {
	x -= diffX;
	y -= diffY;

	diffX = 0;
	diffY = 0;
}