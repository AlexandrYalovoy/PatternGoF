#include "BombDecorator.h"
#include "TestFileLogger.h"

BombDecorator::BombDecorator(Bomb* pBomb) : mBomb(pBomb){
    TestFileLogger::getInstance().WriteToLog(std::string(__func__) +
                                             " Constructor of Decorator was invoked");
}

BombDecorator::~BombDecorator() {
    std::cout << "~BombDecorator()" << std::endl;
}

void BombDecorator::Move(uint16_t time) {
    time *= 2;
    this->mBomb->Move(time);
    TestFileLogger::getInstance().WriteToLog(std::string(__func__) +
                                             " Decorator->Move() was invoked");
}

void BombDecorator::Draw() const {
    ScreenSingleton::getInstance().SetColor(CC_LightMagenta);
    this->mBomb->Draw();
    TestFileLogger::getInstance().WriteToLog(std::string(__func__) +
                                             " Decorator->Draw() was invoked");
}
