#include "GameHandler.h"

GameHandler::GameHandler(int borderTop, int borderRight) {
	gameBorderTop = borderTop;
	gameBorderRight = borderRight;
}

void GameHandler::start() {
	player = new PlayerObject(3, 2, gameBorderRight, gameBorderTop);

	status = PLAYING;
}

void GameHandler::stop() {
	delete player;

	status = STOPPED;
}

GameObject::Matrix GameHandler::getGameMatrix(int screenWidth, int screenHeight) {
	GameObject::Matrix gameMatrix = std::vector<std::vector<char>>(screenHeight, std::vector<char>(screenWidth, ' '));
	
	if (status == PLAYING) {
		int otnY = player->getY() - screenPlayerOffsetY;
		int otnX = player->getX() - screenPlayerOffsetX;

		if (player->getX() >= screenPlayerOffsetX && player->getY() >= screenPlayerOffsetY) {
			GameObject::Matrix playerMatrix = player->getMatrix();
			for (int i = 0; i < playerMatrix.size(); i++) {
				int locY = otnY + i;
				std::vector<char> lineChars = gameMatrix[locY];
				for (int j = 0; j < playerMatrix[i].size(); j++) {
					int locX = otnX + j;

					if (locX >= screenWidth || locX < 0) continue;
					if (locY >= screenHeight || locY < 0) continue;
					lineChars[locX] = playerMatrix[i][j];
				}

				gameMatrix[locY] = lineChars;
			}
		}
	}

	return gameMatrix;
}

std::list<GameHandler::MatrixDiff> GameHandler::getMatrixesDiff(GameObject::Matrix lastMatrix, GameObject::Matrix nextMatrix) {
	std::list<GameHandler::MatrixDiff> diff = std::list<GameHandler::MatrixDiff>();
	for (int y = nextMatrix.size() - 1; y >= 0; y--) {
		for (int x = 0; x < nextMatrix[y].size(); x++) {
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
				GameHandler::MatrixDiff t{ x, y, nextChar };
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

void GameHandler::process(int screenWidth, int screenHeight, PRESSED_KEYS key) {
	if (status == PLAYING) {
		if (key == UP) player->addY(-1);
		else if (key == DOWN) player->addY(1);
		else if (key == LEFT) player->addX(-1);
		else if (key == RIGHT) player->addX(1);

		if (key != NONE) player->setWalkingAnimation();

		if (key == LEFT) player->setOrientation(true);
		else if (key == RIGHT) player->setOrientation(false);

		player->process();

		/*int otnY = player->getY() + player->getHeight() - screenPlayerOffsetY;
		if (otnY > screenHeight) screenPlayerOffsetY++;
		else if (otnY < 0) screenPlayerOffsetY--;*/
	}

	printMatrix(screenWidth, screenHeight);
}