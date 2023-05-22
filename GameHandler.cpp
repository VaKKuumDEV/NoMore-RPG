#include "GameHandler.h"

GameHandler::GameHandler(int borderTop, int borderRight) {
	gameBorderTop = borderTop;
	gameBorderRight = borderRight;
}

void GameHandler::start() {
	PlayerObject* player = new PlayerObject(3, 2, gameBorderRight, gameBorderTop);
	enemies.push_back(player);

	for (int i = 0; i < 1; i++) {
		int rabX = 10 + rand() % (gameBorderRight - 20);
		int rabY = 10 + rand() % (gameBorderTop - 20);
		RabbitEnemy* rab = new RabbitEnemy(rabX, rabY, gameBorderRight, gameBorderTop);

		bool isLeft = 1 + rand() % 2 == 1 ? true : false;
		rab->setOrientation(isLeft);

		enemies.push_back(rab);
	}

	LittleHouseDecorObject* house = new LittleHouseDecorObject(10, 15, gameBorderRight, gameBorderTop);
	enemies.push_back(house);

	BorderDecorObject* border = new BorderDecorObject(gameBorderRight, gameBorderTop);
	enemies.push_back(border);

	status = PLAYING;
}

void GameHandler::stop() {
	for (auto& enemy : enemies) {
		delete enemy;
	}
	enemies.clear();

	status = STOPPED;
}

GameObject::Matrix GameHandler::getGameMatrix(int screenWidth, int screenHeight) {
	GameObject::Matrix gameMatrix = std::vector<std::vector<char>>(screenHeight, std::vector<char>(screenWidth, ' '));
	
	if (status == PLAYING) {
		for (auto& enemy : enemies) {
			if (enemy->isClosed()) continue;
			int enemyOtnX = enemy->getX() - screenPlayerOffsetX;
			GameObject::Matrix enemyMatrix = enemy->getMatrix();
			size_t enemyHeight = enemyMatrix.size();
			int enemyOtnY = enemy->getY() + enemyHeight - screenPlayerOffsetY;

			for (int i = 0; i < enemyHeight; i++) {
				int locY = screenHeight - enemyOtnY + i;
				if (locY >= screenHeight || locY < 0) continue;

				std::vector<char> lineChars = gameMatrix[locY];
				size_t enemyWidth = enemyMatrix[i].size();
				for (int j = 0; j < enemyWidth; j++) {
					int locX = enemyOtnX + j;
					char symbol = enemyMatrix[i][j];

					if (locX >= screenWidth || locX < 0) continue;
					if (symbol == ' ') continue;

					lineChars[locX] = symbol;
				}

				gameMatrix[locY] = lineChars;
			}
		}
	}

	return gameMatrix;
}

std::list<GameHandler::MatrixDiff> GameHandler::getMatrixesDiff(GameObject::Matrix lastMatrix, GameObject::Matrix nextMatrix) {
	std::list<GameHandler::MatrixDiff> diff = std::list<GameHandler::MatrixDiff>();
	size_t nextHeight = nextMatrix.size();
	for (size_t y = 0; y < nextHeight; y++) {
		size_t nextWidth = nextMatrix[y].size();
		for (size_t x = 0; x < nextWidth; x++) {
			bool forcing = false;
			char nextChar = nextMatrix[y][x];
			if (y < lastMatrix.size()) {
				if (x < lastMatrix[y].size()) {
					char prevChar = lastMatrix[y][x];
					if (prevChar != nextChar) forcing = true;
				}
				else forcing = true;
			}
			else forcing = true;

			if (forcing) {
				GameHandler::MatrixDiff t{ (int)x, (int)y, nextChar};
				diff.push_back(t);
			}
		}
	}

	return diff;
}

void GameHandler::ClearScreen() {
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR)' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

void GameHandler::setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void GameHandler::printMatrix(int screenWidth, int screenHeight) {
	GameObject::Matrix currentMatrix = getGameMatrix(screenWidth, screenHeight);
	if (lastGameMatrix.size() == 0) {
		lastGameMatrix = currentMatrix;
		ClearScreen();

		for (int i = 0; i < currentMatrix.size(); i++) {
			std::vector<char> matrixLine = std::vector<char>(currentMatrix[i].size());
			bool isEmptyLine = true;
			for (int j = 0; j < currentMatrix[i].size(); j++) {
				matrixLine[j] = currentMatrix[i][j];
				if (matrixLine[j] != ' ') isEmptyLine = false;
				}

			if (isEmptyLine) std::cout << std::endl;
			else std::cout << std::string(matrixLine.begin(), matrixLine.end()) << std::endl;
		}
	}
	else
	{
		std::list<GameHandler::MatrixDiff> diff = getMatrixesDiff(lastGameMatrix, currentMatrix);
		if (diff.size() > 0) {
			for (auto& t : diff) {
				setCursorPosition(t.x, t.y);
				std::cout << t.symbol;
			}
		}

		lastGameMatrix = currentMatrix;
	}
}

void GameHandler::process(int screenWidth, int screenHeight, std::vector<PRESSED_KEYS> pressedKeys) {
	if (status == PLAYING) {
		for (auto enemy : enemies) {
			auto castedToBorderObject = dynamic_cast<BorderDecorObject*>(enemy);
			if (castedToBorderObject != NULL) castedToBorderObject->setScreen(GameObject::Point{ screenWidth, screenHeight }, GameObject::Point{ screenPlayerOffsetX, screenPlayerOffsetY });
		}

		auto pl = getPlayer();
		if (pl != NULL) {
			if (isKeyPressed(UP, pressedKeys)) pl->setDiffY(1);
			else if (isKeyPressed(DOWN, pressedKeys)) pl->setDiffY(-1);

			if (isKeyPressed(LEFT, pressedKeys)) pl->setDiffX(-2);
			else if (isKeyPressed(RIGHT, pressedKeys)) pl->setDiffX(2);

			if (isKeyPressed(SPACE, pressedKeys)) {
				pl->setDamagingAnimation();
				std::vector<LabelObject*> damageParticles;
				for (auto enemy : enemies) {
					if (enemy == NULL || enemy == pl) continue;
					auto castedToLivingObject = dynamic_cast<LivingGameObject*>(enemy);
					if (castedToLivingObject != NULL && pl->isInVisionPole(castedToLivingObject->getX(), castedToLivingObject->getY(), castedToLivingObject->getWidth(), castedToLivingObject->getHeight()) && castedToLivingObject->getDamageCooldown() <= 0) {
						int damage = pl->executeDamage(castedToLivingObject);

						if (damage > 0) {
							int labelX = castedToLivingObject->getX() + rand() % (castedToLivingObject->getWidth() + 3);
							int labelY = castedToLivingObject->getY() + rand() % (castedToLivingObject->getHeight() + 3);

							LabelObject* damageLabel = new LabelObject("-" + std::to_string(damage), true, TPS, labelX, labelY, getRightBorder(), getTopBorder());
							damageParticles.push_back(damageLabel);
							break;
						}
					}
				}

				for (auto particle : damageParticles) addEnemy(particle);
			}

			int otnY = (pl->getY() + pl->getDiffY()) + pl->getHeight() - screenPlayerOffsetY + 1;
			if (otnY > screenHeight && screenPlayerOffsetY < getTopBorder()) screenPlayerOffsetY += 1;
			else if (otnY <= pl->getHeight() && screenPlayerOffsetY > 0) screenPlayerOffsetY -= 1;

			int otnX = (pl->getX() + pl->getDiffX()) - screenPlayerOffsetX;
			if (otnX > (screenWidth - pl->getWidth()) && screenPlayerOffsetX < getRightBorder()) screenPlayerOffsetX += pl->getWidth();
			else if (otnX <= 0 && screenPlayerOffsetX > 0) screenPlayerOffsetX -= pl->getWidth();
		}

		for (auto enemy : enemies) {
			enemy->preprocess();
			for (auto enemy2 : enemies) {
				if (enemy == NULL || enemy == enemy2) continue;
				if (enemy->isCollisingWith(*enemy2)) enemy->executeCollision(enemy2);
			}

			enemy->process();
			enemy->setDiffX(0);
			enemy->setDiffY(0);
		}

		std::vector<GameObject*> newEnemies;
		for (int enemyIndex = 0; enemyIndex < enemies.size(); enemyIndex++) {
			if (enemies[enemyIndex]->isClosed()) delete enemies[enemyIndex];
			else newEnemies.push_back(enemies[enemyIndex]);
		}

		enemies.clear();
		for (int i = 0; i < newEnemies.size(); i++) enemies.push_back(newEnemies[i]);
	}

	printMatrix(screenWidth, screenHeight);
}

PlayerObject* GameHandler::getPlayer() {
	for (auto enemy : enemies) {
		auto t = dynamic_cast<PlayerObject*>(enemy);
		if (t != NULL) return t;
	}
	return NULL;
}

bool GameHandler::isKeyPressed(PRESSED_KEYS key, std::vector<PRESSED_KEYS>& keys) {
	for (auto pressedKey : keys) {
		if (key == pressedKey) return true;
	}

	return false;
}