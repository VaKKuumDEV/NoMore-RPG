#include "PlayerObject.h"

PlayerObject::PlayerObject(int x, int y, int borderX, int borderY) : LivingGameObject(x, y, borderX, borderY, 10, 10, 7, PLAYER) {

}

GameObject::Matrix PlayerObject::getMatrix() {
	GameObject::Matrix matr = std::vector<std::vector<char>>(2, std::vector<char>(2, '#'));

	if (getAction() == STAING_FIRST) {
		matr = {
			{ ' ', '#', '#', ' ' },
			{ ' ', '#', '#', ' ' },
			{ '#', '#', '#', '#' },
			{ '#', '#', '#', '#' },
			{ '#', '#', '#', '#' },
			{ '#', '#', '#', '#' },
			{ ' ', '#', '#', ' ' },
			{ ' ', '#', '#', ' ' },
			{ ' ', '#', '#', ' ' },
			{ ' ', '#', '#', ' ' },
		};
	}
	else if (getAction() == STAING_SECOND) {
		matr = {
			{ ' ', ' ', ' ', ' ' },
			{ ' ', '#', '#', ' ' },
			{ ' ', '#', '#', ' ' },
			{ '#', '#', '#', '#' },
			{ '#', '#', '#', '#' },
			{ '#', '#', '#', '#' },
			{ '#', '#', '#', '#' },
			{ ' ', '#', '#', ' ' },
			{ ' ', ' ', '#', '#' },
			{ ' ', '#', '#', ' ' },
		};
	}
	else if (getAction() == WALKING_FIRST) {
		matr = {
			{ ' ', '#', '#', ' ', ' '},
			{ ' ', '#', '#', ' ', ' '},
			{ '#', '#', '#', '#', ' '},
			{ '#', '#', '#', '#', ' '},
			{ '#', '#', '#', '#', '#'},
			{ '#', '#', '#', ' ', ' '},
			{ ' ', '#', '#', ' ', ' '},
			{ '#', ' ', '#', ' ', ' '},
			{ '#', ' ', '#', ' ', ' '},
			{ '#', ' ', ' ', '#', ' '},
		};
	}
	else if (getAction() == WALKING_SECOND) {
		matr = {
			{ ' ', '#', '#', ' ' },
			{ ' ', '#', '#', ' ' },
			{ '#', '#', '#', '#' },
			{ '#', '#', '#', '#' },
			{ '#', '#', '#', '#' },
			{ '#', '#', '#', '#' },
			{ ' ', '#', '#', ' ' },
			{ ' ', '#', ' ', '#' },
			{ ' ', '#', ' ', '#' },
			{ '#', ' ', ' ', '#' },
		};
	}
	else if (getAction() == DAMAGING) {
		matr = {
			{ ' ', '#', '#', ' ', ' ', ' ' },
			{ ' ', '#', '#', ' ', ' ', ' ' },
			{ '#', '#', '#', '#', ' ', ' ' },
			{ '#', '#', '#', '#', '#', '#' },
			{ ' ', '#', '#', ' ', ' ', ' ' },
			{ ' ', '#', '#', ' ', ' ', ' ' },
			{ ' ', ' ', '#', '#', ' ', ' ' },
			{ ' ', '#', '#', ' ', ' ', ' ' },
			{ ' ', '#', '#', ' ', ' ', ' ' },
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

int PlayerObject::executeDamage(LivingGameObject* obj) {
	LivingGameObject::executeDamage(obj);

	int damage = obj->applyDamage(DAMAGE);
	return damage;
}

void PlayerObject::executeCollision(GameObject* obj) {
	LivingGameObject::executeCollision(obj);
}

void PlayerObject::process() {
	if (getDiffX() != 0 || getDiffY() != 0) setWalkingAnimation();

	if (getDiffX() < 0) setOrientation(true);
	else if (getDiffX() > 0) setOrientation(false);

	LivingGameObject::process();
}

void PlayerObject::preprocess() {
	addX(getDiffX());
	addY(getDiffY());
}