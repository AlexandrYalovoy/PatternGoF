#include "IVisitor.h"
#include "TestFileLogger.h"
#include "Bomb.h"
#include "Plane.h"

void LogVisitor::visit(Bomb* pBomb) const {
    auto bomb_direction = pBomb->GetDirection();
    TestFileLogger::getInstance().WriteToLog(std::string(__func__) +
                                             " Bomb speed= " + std::to_string(pBomb->GetSpeed()) + " Bomb direction= " +
                                             std::to_string(std::get<0>(bomb_direction)) + " " +
                                             std::to_string(std::get<1>(bomb_direction)));
}

void LogVisitor::visit(Plane* pPlane) const {
    auto plane_direction = pPlane->GetDirection();
    TestFileLogger::getInstance().WriteToLog(std::string(__func__) +
                                             " Plane speed= " + std::to_string(pPlane->GetSpeed()) + " Plane direction= " +
                                             std::to_string(std::get<0>(plane_direction)) + " " +
                                             std::to_string(std::get<1>(plane_direction)));
}
