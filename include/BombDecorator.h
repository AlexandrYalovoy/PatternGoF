#pragma once

#include "SBomber.h"

class BombDecorator : public DynamicObject {
public:
    explicit BombDecorator(Bomb* pBomb);
    ~BombDecorator() override;
    void Move(uint16_t time) override;
    void Draw() const override;
private:
    Bomb* mBomb{};
};

