#ifndef SBOMBER_ADAPTERTANK_H
#define SBOMBER_ADAPTERTANK_H

#include <string>

#include "DestroyableGroundObject.h"
#include "Tank.h"

class AdapterTank : public DestroyableGroundObject {
public:
    explicit AdapterTank(std::string options);

    bool  isInside(double x1, double x2) const override;
    inline uint16_t GetScore() const override { return score; }
    void Draw() const override;

    inline void SetPos(double nx, double ny) override;
    inline void SetWidth(uint16_t widthN) override;

private:
    std::string mAdaptee;
    uint16_t score;
    Tank *mTank;

    double x, y;
    uint16_t width;
};


#endif //SBOMBER_ADAPTERTANK_H
