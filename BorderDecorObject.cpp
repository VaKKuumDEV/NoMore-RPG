#include "BorderDecorObject.h"

BorderDecorObject::BorderDecorObject(int borderX, int borderY) : DecorGameObject(0, 0, borderX, borderY, true) {

}

void BorderDecorObject::process()
{

}

void BorderDecorObject::preprocess()
{

}

GameObject::Matrix BorderDecorObject::getMatrix()
{
	GameObject::Matrix matrix = std::vector<std::vector<char>>(getBorderY(), std::vector<char>(getBorderX(), ' '));
	for (int i = 0; i < matrix.size(); i++) {
		if (i == 0 || i == (matrix.size() - 1)) {
			for (int j = 0; j < matrix[i].size(); j++) matrix[i][j] = '#';
		}
		else {
			matrix[i][0] = '#';
			matrix[i][matrix[i].size() - 1] = '#';
		}
	}

	return matrix;
}