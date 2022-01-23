#pragma once

#include "DynamicObject.h"
#include "IVisitor.h"

class Plane : public DynamicObject {
public:

    void Draw() const override;

    inline void ChangePlaneY(double dy) { yDirection += dy; }

    void Accept(IVisitor* pVisitor) override;
private:

};

