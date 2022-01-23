#include "SBomber.h"
#include "TestFileLogger.h"
#include "Director.h"


int main(int argc, char** argv) {
//  FileLoggerProxy::getInstance().OpenLogFile("log.txt");
  TestFileLogger::getInstance().OpenLogFile("test_log.txt");


	std::cout << "Choose house type: \n" << "1: Standard house.\n" << "2: Minimal house.\n";
	int c = 1;
//	std::cin >> c;

  SBomber game(c);
  game.run();

//  FileLoggerProxy::getInstance().CloseLogFile();
  TestFileLogger::getInstance().CloseLogFile();


  return 0;
}
