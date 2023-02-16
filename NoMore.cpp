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

void gameHandlerLoop();
pair<int, int> getConsoleSize();

int main()
{
    srand((unsigned)time(NULL));
    SetConsoleTitleW(L"NoMore - RPG");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX fontInfo;
    GetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);
    fontInfo.dwFontSize.X = 10;
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
        handler->process(sizes.first, sizes.second);

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