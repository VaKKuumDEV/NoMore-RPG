#include "BorderDecorObject.h"

BorderDecorObject::BorderDecorObject(int borderX, int borderY) : DecorGameObject(0, 0, borderX, borderY, false) {

}

void BorderDecorObject::process()
{

}

void BorderDecorObject::preprocess()
{

}

GameObject::Matrix BorderDecorObject::getMatrix()
{
	GameObject::Matrix matrix = std::vector<std::vector<char>>(getScreen().y, std::vector<char>(getScreen().x, ' '));
	for (int i = 0; i < matrix.size(); i++) {
		if ((i == 0 && getOffset().y == 0) || (i == (matrix.size() - 1) && getOffset().y + getScreen().y == getBorderY())) {
			std::vector<char> line = matrix[matrix.size() - 1 - i];
			for (int j = 0; j < line.size(); j++) line[j] = '#';
			matrix[matrix.size() - 1 - i] = line;
		}

		if (getOffset().x == 0) matrix[i][0] = '#';
		if (getOffset().x + getScreen().x == getBorderX()) matrix[i][matrix[i].size() - 1] = '#';
	}

	return matrix;
}