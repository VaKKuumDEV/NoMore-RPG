#include "GameObject.h"
#include "PlayerObject.h"
#include "EnemyObject.h"
#include "RabbitEnemy.h"
#include <tuple>
#include <iostream>
#include <Windows.h>
#include <string>
#include <list>
#include <vector>

#pragma once
class GameHandler {
public:
	enum PRESSED_KEYS {
		NONE,
		UP,
		DOWN,
		LEFT,
		RIGHT,
	};
	enum GameStatuses {
		NOT_INITED,
		PLAYING,
		STOPPED,
	};
	struct MatrixDiff {
		int x, y;
		char symbol;
	};
private:
	GameStatuses status = NOT_INITED;
	GameObject::Matrix lastGameMatrix;
	PlayerObject* player = NULL;
	int screenPlayerOffsetX = 0, screenPlayerOffsetY = 0;
	int gameBorderTop, gameBorderRight;
	std::vector<EnemyObject> enemies;
	GameObject::Matrix getGameMatrix(int screenWidth, int screenHeight);
	std::list<GameHandler::MatrixDiff> getMatrixesDiff(GameObject::Matrix lastMatrix, GameObject::Matrix nextMatrix);
	void ClearScreen();
	void setCursorPosition(int x, int y);
	void printMatrix(int screenWidth, int screenHeight);
public:
	GameHandler(int borderTop, int borderRight);
	void start();
	void stop();
	GameStatuses getStatus() { return status; }
	int getTopBorder() { return gameBorderTop; }
	int getRightBorder() { return gameBorderRight; }
	void process(int screenWidth, int screenHeight, PRESSED_KEYS key);
};