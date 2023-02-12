#include "GameObject.h"

GameObject::GameObject(int x, int y) {
	this->x = x;
	this->y = y;
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

bool GameObject::isCollisingWith(GameObject& obj) {
	int minX = std::min(getX(), obj.getX());
	int maxX = std::max(getX() + getWidth(), obj.getX() + obj.getWidth());
	int minY = std::min(getY(), obj.getY());
	int maxY = std::max(getY() + getHeight(), obj.getY() + obj.getHeight());

	int diffX = minX - maxX;
	int diffY = minY - maxY;

	Matrix collisedMatrix = std::vector<std::vector<char>>(diffY, std::vector<char>(diffX, ' '));
	Matrix thisMatrix = getMatrix();
	Matrix objMatrix = obj.getMatrix();

	for (int i = thisMatrix.size() - 1; i >= 0; i--) {
		for (int j = 0; j < thisMatrix[i].size(); j++) {
			if (thisMatrix[i][j] == ' ') continue;

			int otnX = getX() - minX + j;
			int otnY = getY() - minY + i;
			collisedMatrix[otnY][otnX] = thisMatrix[i][j];
		}
	}

	for (int i = objMatrix.size() - 1; i >= 0; i--) {
		for (int j = 0; j < objMatrix[i].size(); j++) {
			if (objMatrix[i][j] == ' ') continue;

			int otnX = obj.getX() - minX + j;
			int otnY = obj.getY() - minY + i;
			if (collisedMatrix[otnY][otnX] != ' ') return true;
		}
	}

	return false;
}