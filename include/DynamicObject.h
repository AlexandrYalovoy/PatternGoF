#pragma once

#include <cstdint>
#include <tuple>

#include "GameObject.h"
#include "IVisitor.h"

class DynamicObject : public GameObject 
{
public:

    DynamicObject() : speed(0.0), xDirction(0.0), yDirection(0) { }

    virtual void Move(uint16_t time) { x += xDirction * speed * time * 0.001; y += yDirection * speed * time * 0.001; };
    virtual void Accept(IVisitor* pVisitor) = 0; // For Pattern Visitor
    //Getters and Setters
    inline void SetSpeed(double sp) { speed = sp; }
    inline void SetDirection(double dx, double dy) { xDirction = dx; yDirection = dy; }
    [[nodiscard]] double GetSpeed() const {return speed;}
    [[nodiscard]] std::tuple<double, double> GetDirection() const {
        return std::tie(xDirction, yDirection);
    }
protected:

    double speed;
    double xDirction, yDirection;

};