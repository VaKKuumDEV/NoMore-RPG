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
GameHandler::PRESSED_KEYS pressed = GameHandler::PRESSED_KEYS::NONE;

void gameHandlerLoop();
pair<int, int> getConsoleSize();
bool IsPress(char symbol);
void keyControl();

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
        keyControl();

        sizes = getConsoleSize();
        handler->process(sizes.first, sizes.second, pressed);

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

void keyControl() {
    if (IsPress('w') || IsPress('W')) pressed = GameHandler::PRESSED_KEYS::UP;
    else if (IsPress('s') || IsPress('S')) pressed = GameHandler::PRESSED_KEYS::DOWN;
    else if (IsPress('a') || IsPress('A')) pressed = GameHandler::PRESSED_KEYS::LEFT;
    else if (IsPress('d') || IsPress('D')) pressed = GameHandler::PRESSED_KEYS::RIGHT;
    else pressed = GameHandler::PRESSED_KEYS::NONE;
}