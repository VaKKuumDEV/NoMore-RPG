#include "GameObject.h"
#include "PlayerObject.h"
#include "LivingGameObject.h"
#include "RabbitEnemy.h"
#include "BorderDecorObject.h"
#include "LabelObject.h"
#include "LittleHouseDecorObject.h"
#include <algorithm>
#include <tuple>
#include <iostream>
#include <Windows.h>
#include <string>
#include <list>
#include <vector>
#include <typeinfo>

#pragma once
class GameHandler {
public:
	static const int TPS = 20;
	enum PRESSED_KEYS {
		NONE,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		SPACE,
	};
	enum GameStatuses {
		NOT_INITED,
		PLAYING,
		FINISHED,
		STOPPED,
	};
	struct MatrixDiff {
		int x, y;
		char symbol;
	};
private:
	GameStatuses status = NOT_INITED;
	GameObject::Matrix lastGameMatrix;
	int screenPlayerOffsetX = 0, screenPlayerOffsetY = 0;
	int gameBorderTop, gameBorderRight;
	std::vector<GameObject*> enemies;
	std::vector<LabelObject*> tipMessages;
	int score = 0;
	GameObject::Matrix getGameMatrix(int screenWidth, int screenHeight);
	std::list<GameHandler::MatrixDiff> getMatrixesDiff(GameObject::Matrix lastMatrix, GameObject::Matrix nextMatrix);
	void ClearScreen();
	void setCursorPosition(int x, int y);
	bool isKeyPressed(PRESSED_KEYS key, std::vector<PRESSED_KEYS>& keys);
	void printMatrix(int screenWidth, int screenHeight);
public:
	GameHandler(int borderTop, int borderRight);
	void start();
	void stop();
	GameStatuses getStatus() { return status; }
	PlayerObject* getPlayer();
	void addEnemy(GameObject* enemy) { enemies.push_back(enemy); }
	int getTopBorder() { return gameBorderTop; }
	int getRightBorder() { return gameBorderRight; }
	void process(int screenWidth, int screenHeight, std::vector<PRESSED_KEYS> pressedKeys);
	void processTipMessages(int screenWidth, int screenHeight);
	std::string replace(const std::string& inputString, const std::string& src, const std::string& dst);
	bool canSpawn(GameObject* obj);
	bool isCompleted();
};