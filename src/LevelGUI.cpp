#include "LevelGUI.h"
#include <iostream>
#include <cstring>
#include "MyTools.h"
#include "ScreenSingleton.h"

void LevelGUI::Draw() const
{
    ScreenSingleton::getInstance().SetColor(CC_White);

    ScreenSingleton::getInstance().GotoXY(x, y);
    char* buf = new (std::nothrow) char[width + 1];
    if (buf == nullptr)
    {
        return;
    }
    memset(buf, '+', width);
    buf[width] = '\0';
    std::cout << buf;
    ScreenSingleton::getInstance().GotoXY(x, y + height);
    std::cout << buf;
    delete [] buf;
    buf = nullptr;
    
    for (size_t i = size_t(y); i < height + y; i++)
    {
        ScreenSingleton::getInstance().GotoXY(x, (double)i);
        std::cout << "+";
        ScreenSingleton::getInstance().GotoXY(x + width - 1, (double)i);
        std::cout << "+";
    }

    ScreenSingleton::getInstance().GotoXY(3, 1);
    std::cout << "FramePerSecond: " << static_cast<int>(fps / (passedTime / 1000.0));
    ScreenSingleton::getInstance().GotoXY(25, 1);
    std::cout << "PassedTime: " << static_cast<int>(passedTime / 1000.0) << " sec";
    ScreenSingleton::getInstance().GotoXY(46, 1);
    std::cout << "BombsNum: " << bombsNumber;
    ScreenSingleton::getInstance().GotoXY(62, 1);
    std::cout << "Score: " << score;
}

void  LevelGUI::SetParam(uint64_t passedTimeNew, uint64_t fpsNew, uint16_t bombsNumberNew, int16_t scoreNew)
{
    passedTime = passedTimeNew;
    fps = fpsNew;
    bombsNumber = bombsNumberNew;
    score = scoreNew;
}
