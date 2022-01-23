#pragma once

#include "GameObject.h"

class Crater : public GameObject {
public:
  bool isInside(double xn) const;

  virtual void Draw() const override;
};
