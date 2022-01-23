#include "Bomb.h"
#include <iostream>
#include "ScreenSingleton.h"
#include "TestFileLogger.h"

void Bomb::Draw() const {
//  ScreenSingleton::getInstance().SetColor(CC_LightMagenta);
  ScreenSingleton::getInstance().GotoXY(x, y);
  std::cout << "*";
}

Bomb::~Bomb() {
    std::cout << "~Bomb()" << std::endl;
}

void Bomb::Accept(IVisitor* v) {
    v->visit(this);
}
