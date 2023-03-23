#include "RabbitEnemy.h"

RabbitEnemy::RabbitEnemy(int x, int y, int borderX, int borderY) : LivingGameObject(x, y, borderX, borderY, 10, 10, 3, FRIENDLY)
{

}

GameObject::Matrix RabbitEnemy::getMatrix()
{
	GameObject::Matrix matr = std::vector<std::vector<char>>(2, std::vector<char>(2, '#'));

	if (getAction() == STAING_FIRST) {
		matr = {
			{ ' ', '#', ' ' },
			{ ' ', '#', ' ' },
			{ ' ', '#', '#' },
			{ ' ', '#', '#' },
			{ '#', '#', ' ' },
			{ '#', '#', '#' },
			{ '#', '#', '#' },
		};
	}
	else if (getAction() == STAING_SECOND) {
		matr = {
			{ ' ', '#', ' ' },
			{ ' ', '#', ' ' },
			{ ' ', '#', '#' },
			{ ' ', '#', '#' },
			{ '#', '#', '#' },
			{ '#', '#', '#' },
			{ '#', ' ', '#' },
		};
	}
	else if (getAction() == WALKING_FIRST) {
		matr = {
			{ '#', ' ', ' ' },
			{ ' ', '#', ' ' },
			{ ' ', '#', '#' },
			{ ' ', '#', '#' },
			{ '#', '#', ' ' },
			{ '#', ' ', '#' },
			{ '#', ' ', '#' },
		};
	}
	else if (getAction() == WALKING_SECOND) {
		matr = {
			{ ' ', '#', ' ' },
			{ ' ', '#', ' ' },
			{ ' ', '#', '#' },
			{ ' ', '#', '#' },
			{ '#', '#', ' ' },
			{ '#', ' ', '#' },
			{ ' ', '#', '#' },
		};
	}

	if (getOrientation() == LEFT) {
		for (int i = 0; i < matr.size(); i++) {
			std::vector<char> newMatrLine = std::vector<char>(matr[i].size());
			for (int j = 0; j < newMatrLine.size(); j++) newMatrLine[j] = matr[i][matr[i].size() - j - 1];
			matr[i] = newMatrLine;
		}
	}

	return matr;
}

void RabbitEnemy::process()
{
	LivingGameObject::process();
}
