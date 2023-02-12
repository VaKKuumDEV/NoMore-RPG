#include "PlayerObject.h"

PlayerObject::PlayerObject(int x, int y) : LivingGameObject(x, y, 10, 10) {

}

GameObject::Matrix PlayerObject::getMatrix() {
	if (currentAction == STAING_FIRST) {
		return {
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
		return {
			{ ' ', '#', '#', ' ' },
			{ ' ', '#', '#', ' ' },
			{ '#', '#', '#', '#' },
			{ '#', '#', '#', '#' },
			{ '#', '#', '#', '#' },
			{ '#', '#', '#', '#' },
			{ ' ', '#', '#', ' ' },
			{ ' ', ' ', '#', '#' },
			{ ' ', ' ', '#', '#' },
			{ ' ', '#', '#', ' ' },
		};
	}

	return std::vector<std::vector<char>>(2, std::vector<char>(2, '#'));
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
	}
}