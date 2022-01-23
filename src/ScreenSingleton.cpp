#include "ScreenSingleton.h"

#include <stdint.h>
#include <time.h>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include "MyTools.h"

#if defined(_WIN32) || defined(WIN32)
#include <conio.h>
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#endif

//
//
//

IScreen& getInternalInstance() {
  static ScreenSingleton theInstance;
  return theInstance;
}

//
//
//

class ScreenSingletonProxy : public IScreen {
public:
  virtual void ClrScr() override {
    MyTools::WriteToLog("ClrScr invoke begin");
    getInternalInstance().ClrScr();
    MyTools::WriteToLog("ClrScr invoke end");
  }
  virtual void GotoXY(double x, double y) override {

    MyTools::WriteToLog("GotoXY invoke begin");
    getInternalInstance().GotoXY(x, y);
    MyTools::WriteToLog("GotoXY invoke end");
  }
  virtual uint16_t GetMaxX() override {
    return getInternalInstance().GetMaxX();
  }

  virtual uint16_t GetMaxY() override {
    return getInternalInstance().GetMaxY();
  }
  virtual void SetColor(ConsoleColor color) override {
    return getInternalInstance().SetColor(color);
  }

  static IScreen& getInstance() {
    static ScreenSingletonProxy theInstance;
    return theInstance;
  }

private:
  ScreenSingletonProxy() {
  }

  ~ScreenSingletonProxy() {
  }

  ScreenSingletonProxy(const ScreenSingletonProxy& root) = delete;
  ScreenSingletonProxy& operator=(const ScreenSingletonProxy&) = delete;
  ScreenSingletonProxy(ScreenSingletonProxy&& root) = delete;
  ScreenSingletonProxy& operator=(ScreenSingletonProxy&&) = delete;
};

//
//
//

#if defined(_WIN32) || defined(WIN32)

void ScreenSingleton::ClrScr() {
  system("cls");
}

void ScreenSingleton::GotoXY(double x, double y) {
  const COORD cc = {short(x), short(y)};
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cc);
}

uint16_t ScreenSingleton::GetMaxX() {
  HANDLE hWndConsole;
  if (hWndConsole = GetStdHandle(-12)) {
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo)) {
      return consoleInfo.srWindow.Right;
      int height = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
    }
  }

  return 0;
}

uint16_t ScreenSingleton::GetMaxY() {
  HANDLE hWndConsole;
  if (hWndConsole = GetStdHandle(-12)) {
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo)) {
      return consoleInfo.srWindow.Bottom;
    }
  }

  return 0;
}

void ScreenSingleton::SetColor(ConsoleColor color) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, color);
}

#else

void ScreenSingleton::ClrScr() {
  system("clear");
}

void ScreenSingleton::GotoXY(double x, double y) {
  printf("\033[%d;%dH", (int)y + 1, (int)x + 1);
}

uint16_t ScreenSingleton::GetMaxX() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w.ws_col;
}

uint16_t ScreenSingleton::GetMaxY() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w.ws_row;
}

int convertColorToCode(const ConsoleColor color) {
  switch (color) {
    case CC_Black: {
      return 30;
    } break;
    case CC_Blue: {
      return 34;
    } break;
    case CC_Green: {
      return 32;
    } break;
    case CC_Cyan: {
      return 36;
    } break;
    case CC_Red: {
      return 31;
    } break;
    case CC_Magenta: {
      return 35;
    } break;

    case CC_LightBlue: {
      return 94;
    } break;
    case CC_LightGreen: {
      return 92;
    } break;
    case CC_LightCyan: {
      return 96;
    } break;
    case CC_LightRed: {
      return 91;
    } break;
    case CC_LightMagenta: {
      return 95;
    } break;
    case CC_Yellow: {
      return 93;
    } break;
    case CC_White: {
      return 97;
    } break;
    default: {
      throw std::runtime_error("not handled");
    }
  }
}

void ScreenSingleton::SetColor(ConsoleColor color) {
  std::cout << "\033[" << convertColorToCode(color) << "m";
}

#endif

IScreen& ScreenSingleton::getInstance() {
  return ScreenSingletonProxy::getInstance();
}
