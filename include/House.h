#pragma once

#include "DestroyableGroundObject.h"

#include <cstdint>
#include <array>

class House : public DestroyableGroundObject {
	static const int rows = 7;
	static const int columns = 14;
	using array = std::array<std::array<char, rows>, columns>;
public:
  bool isInside(double x1, double x2) const override;

  inline uint16_t GetScore() const override {
    return score;
  }

  void Draw() const override;

private:
  const uint16_t score = 40;
  char look[rows][columns];
  friend class HouseBuilderA;
};


