#pragma once
#include <cstdint>
#include "enums/ConsoleColors.h"

class IScreen {
public:
  virtual ~IScreen()  = default;
  virtual void ClrScr() = 0;
  virtual void GotoXY(double x, double y) = 0;
  virtual uint16_t GetMaxX() = 0;
  virtual uint16_t GetMaxY() = 0;
  virtual void SetColor(ConsoleColor color) = 0;
};

class ScreenSingleton : public IScreen {
public:
  static IScreen& getInstance();

  virtual void ClrScr() override;
  virtual void GotoXY(double x, double y) override;
  virtual uint16_t GetMaxX() override;
  virtual uint16_t GetMaxY() override;
  virtual void SetColor(ConsoleColor color) override;

private:
  friend IScreen& getInternalInstance();

  ScreenSingleton() = default;
  ~ScreenSingleton() = default;
  ScreenSingleton(const ScreenSingleton& root) = delete;
  ScreenSingleton& operator=(const ScreenSingleton&) = delete;
  ScreenSingleton(ScreenSingleton&& root) = delete;
  ScreenSingleton& operator=(ScreenSingleton&&) = delete;
};

