#include "PlayerObject.h"

PlayerObject::PlayerObject(int x, int y, int borderX, int borderY) : LivingGameObject(x, y, borderX, borderY, 10, 10) {

}

GameObject::Matrix PlayerObject::getMatrix() {
	GameObject::Matrix matr = std::vector<std::vector<char>>(2, std::vector<char>(2, '#'));

	if (currentAction == STAING_FIRST) {
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
	else if (currentAction == STAING_SECOND) {
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
	else if (currentAction == WALKING_FIRST) {
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
	else if (currentAction == WALKING_SECOND) {
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

	if (currentOrientation == LEFT) {
		//������� ��������
	}

	return matr;
}

void PlayerObject::process() {
	if (skippingTicks > 0) skippingTicks--;
	else {
		if (currentAction == STAING_FIRST) {
			currentAction = STAING_SECOND;
			skippingTicks = ACTION_SKIP;
		}
		else if (currentAction == STAING_SECOND) {
			currentAction = STAING_FIRST;
			skippingTicks = ACTION_SKIP;
		}
		else if (currentAction == WALKING_FIRST) {
			currentAction = STAING_FIRST;
			skippingTicks = ACTION_SKIP;
		}
		else if (currentAction == WALKING_SECOND) {
			currentAction = STAING_FIRST;
			skippingTicks = ACTION_SKIP;
		}
	}
}

void PlayerObject::setWalkingAnimation() {
	if (currentAction == WALKING_FIRST && skippingTicks <= 0) {
		currentAction = WALKING_SECOND;
		skippingTicks = ACTION_SKIP;
	}
	else if (currentAction == WALKING_SECOND && skippingTicks <= 0) {
		currentAction = WALKING_FIRST;
		skippingTicks = ACTION_SKIP;
	}
	else if (currentAction == STAING_FIRST || currentAction == STAING_SECOND) {
		currentAction = WALKING_FIRST;
		skippingTicks = ACTION_SKIP;
	}
}