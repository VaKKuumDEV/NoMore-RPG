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

void RabbitEnemy::calculateMotion() {
	if (lastDamager != NULL) {
		if (!lastDamager->isClosed() && lastDamager->isLive()) {
			int diffX = lastDamager->getCenterX() - getCenterX();
			int diffY = lastDamager->getCenterY() - getCenterY();
			double distance = sqrt(diffX * diffX + diffY * diffY);
			double koef = sqrt(4.0 * distance * distance - diffX * diffX) / (double)abs(diffX);
			diffX *= koef;
			diffY *= koef;

			motionPoint = GameObject::Point{ getCenterX() + diffX, getCenterY() + diffY };
		}
		lastDamager = NULL;
	}
	else {
		int randX = -6 + rand() % 13;
		int randY = -6 + rand() % 13;
		motionPoint = GameObject::Point{ getCenterX() + randX, getCenterY() + randY };
	}

	if (motionPoint.x <= 0) motionPoint.x = 1;
	if (motionPoint.x >= getBorderX()) motionPoint.x = getBorderX() - 1;
	if (motionPoint.y <= 0) motionPoint.y = 1;
	if (motionPoint.y >= getBorderY()) motionPoint.y = getBorderY() - 1;
}

int RabbitEnemy::applyDamage(int damagePoints, LivingGameObject* damager) {
	int damage = LivingGameObject::applyDamage(damagePoints, damager);
	if (damage > 0) lastDamager = damager;

	return damage;
}

void RabbitEnemy::process()
{
	LivingGameObject::process();
}

void RabbitEnemy::preprocess() {
	LivingGameObject::preprocess();

	if (walkingTicks > 0) walkingTicks--;
	if (walkingCalculatingTicks > 0) walkingCalculatingTicks--;

	if ((motionPoint.x < 0 && motionPoint.y < 0) || walkingCalculatingTicks <= 0 || lastDamager != NULL) {
		calculateMotion();
		walkingCalculatingTicks = 60;
	}

	if (walkingTicks <= 0 && motionPoint.x >= 0 && motionPoint.y >= 0) {
		double distance = getDistance(motionPoint.x, motionPoint.y);
		if (distance > 1.0) {
			int diffX = getX() - motionPoint.x;
			int diffY = getY() - motionPoint.y;

			int randX = diffX == 0 ? 0 : (1 + rand() % 2);
			int randY = diffY == 0 ? 0 : 1;

			setDiffX((diffX == 0 ? 0 : (abs(diffX) / diffX)) * std::min(abs(diffX), randX));
			setDiffY((diffY == 0 ? 0 : (abs(diffY) / diffY)) * std::min(abs(diffY), randY));

			addX(getDiffX());
			addY(getDiffY());
		}

		walkingTicks = 5;
	}
}
void RabbitEnemy::executeCollision(GameObject* obj) {
	LivingGameObject::executeCollision(obj);
}
