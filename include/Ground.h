#pragma once

#include "GameObject.h"
#include "Crater.h"
#include <vector>


class Ground : public GameObject {
public:
  Ground() = default;
  void Draw() const override;

  void AddCrater(double xn);

private:
  bool isInsideAnyCrater(double x) const;

  std::vector<Crater> vecCrates;
};
