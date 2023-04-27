#include <iostream>
#include <random>
#include <ctime>
#include <thread>
#include <Windows.h>

#include "GameObject.h"
#include "DecorGameObject.h"
#include "LivingGameObject.h"
#include "PlayerObject.h"
#include "GameHandler.h"

using namespace std;

const int TPS = 20;
pair<int, int> sizes;
GameHandler* handler = NULL;

bool IsPress(char symbol);
vector<GameHandler::PRESSED_KEYS> keyControl();
void gameHandlerLoop();
pair<int, int> getConsoleSize();

int main()
{
    srand((unsigned)time(NULL));
    SetConsoleTitleW(L"NoMore - RPG");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX fontInfo;
    //GetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);
    fontInfo.cbSize = sizeof fontInfo;
    fontInfo.nFont = 0;
    fontInfo.dwFontSize.X = 0;
    fontInfo.dwFontSize.Y = 15;
    fontInfo.FontFamily = FF_DONTCARE;
    fontInfo.FontWeight = FW_NORMAL;
    SetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);

    cout << "Hello World!\n";

    handler = new GameHandler(500, 200);
    handler->start();

    thread gameThread = thread(gameHandlerLoop);
    gameThread.join();
}

void gameHandlerLoop() {
    while (handler->getStatus() == GameHandler::PLAYING) {
        sizes = getConsoleSize();
        handler->process(sizes.first, sizes.second, keyControl());

        chrono::milliseconds timespan((int)(1000 / TPS));
        this_thread::sleep_for(timespan);
    }
}

pair<int, int> getConsoleSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    return pair<int, int>(columns, rows);
}

bool IsPress(char symbol)
{
    return (GetKeyState(symbol) & 0x8000);
}

vector<GameHandler::PRESSED_KEYS> keyControl() {
    vector<GameHandler::PRESSED_KEYS> pressedKeys;
    if (IsPress('w') || IsPress('W')) pressedKeys.push_back(GameHandler::PRESSED_KEYS::UP);
    if (IsPress('s') || IsPress('S')) pressedKeys.push_back(GameHandler::PRESSED_KEYS::DOWN);
    if (IsPress('a') || IsPress('A')) pressedKeys.push_back(GameHandler::PRESSED_KEYS::LEFT);
    if (IsPress('d') || IsPress('D')) pressedKeys.push_back(GameHandler::PRESSED_KEYS::RIGHT);
    
    return pressedKeys;
}