#include "SBomber.h"
#include "Command.h"
#include "BombIterator.h"
#include "AdapterTank.h"
#include "Director.h"


#if defined(_WIN32) || defined(WIN32)

//#include <conio.h>
//
#else

#include <iostream>
#include <fstream>
#include <memory>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>


int _kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (!initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

#endif

Plane *SBomber::createPlane() {
    auto *p = new Plane;
    p->SetDirection(1, 0.1);
    p->SetSpeed(4);
    p->SetPos(5, 10);
    return p;
}

LevelGUI *
SBomber::createUI(const uint64_t passedTime, const uint16_t fps, const uint16_t bombsNumber, const int16_t score) {
    auto *pGUI = new LevelGUI;
    pGUI->SetParam(passedTime, fps, bombsNumber, score);
    const uint16_t maxX = ScreenSingleton::getInstance().GetMaxX();
    const uint16_t maxY = ScreenSingleton::getInstance().GetMaxY();
    const uint16_t offset = 3;
    const uint16_t width = maxX - 7;
    pGUI->SetPos(offset, offset);
    pGUI->SetWidth(width);
    pGUI->SetHeight(maxY - 4);
    pGUI->SetFinishX(offset + width - 4);
    return pGUI;
}

Ground *SBomber::createGround() {
    auto *pGr = new Ground;
    const uint16_t maxX = ScreenSingleton::getInstance().GetMaxX();
    const uint16_t maxY = ScreenSingleton::getInstance().GetMaxY();
    const uint16_t offset = 3;
    const uint16_t width = maxX - 7;
    const uint16_t groundY = maxY - 5;
    pGr->SetPos(offset + 1, groundY);
    pGr->SetWidth(width - 2);
    return pGr;
}

Tank *SBomber::createTank(const double pos, const uint16_t width) {
    const uint16_t maxY = ScreenSingleton::getInstance().GetMaxY();
    const uint16_t groundY = maxY - 5;

    auto *pTank = new Tank;
    pTank->SetWidth(width);
    pTank->SetPos(pos, groundY - 1);
    return pTank;
}

House *SBomber::createHouse(const double pos, const uint16_t width) const {
    const uint16_t maxY = ScreenSingleton::getInstance().GetMaxY();
    const uint16_t groundY = maxY - 5;

    //Builder Pattern
    House* pHouse = nullptr;
    if (m_type_house == 1) {
        Director dir{};
        HouseBuilder* standardHouse = new HouseBuilderA;
        pHouse = dir.createStandardHouse(standardHouse);
        pHouse->SetWidth(width);
        pHouse->SetPos(pos, groundY - 1);
    }
    else if (m_type_house == 2) {
        Director dir{};
        HouseBuilder* minimalHouse = new HouseBuilderA;
        pHouse = dir.createMinimalHouse(minimalHouse);
        pHouse->SetWidth(width);
        pHouse->SetPos(pos, groundY - 1);
    }


    return pHouse;
}

SBomber::SBomber(int type_house)
        : exitFlag(false), startTime(0), finishTime(0), deltaTime(0), passedTime(0),
          fps(0), bombsNumber(10), score(0), oddIteration(false), m_type_house(type_house) {
    FileLoggerProxy::getInstance().WriteToLog(std::string(__func__)
                                              + " was invoked");

    vecDynamicObj.push_back(createPlane());
    vecStaticObj.push_back(createUI(passedTime, fps, bombsNumber, score));
    vecStaticObj.push_back(createGround());
    vecStaticObj.push_back(createTank(30, 13));
    vecStaticObj.push_back(createTank(50, 13));
    vecStaticObj.push_back(createHouse(80, 13));

    m_CollisionD = std::make_unique<CollisionDetector>(vecStaticObj, vecDynamicObj, score, exitFlag);
}

SBomber::~SBomber() {
    for (size_t i = 0; i < vecDynamicObj.size(); i++) {
        if (vecDynamicObj[i] != nullptr) {
            delete vecDynamicObj[i];
        }
    }

    for (size_t i = 0; i < vecStaticObj.size(); i++) {
        if (vecStaticObj[i] != nullptr) {
            delete vecStaticObj[i];
        }
    }
    std::cout << "~SBomber()" << std::endl;
}

void SBomber::MoveObjects() {
    FileLoggerProxy::getInstance().WriteToLog(std::string(__func__)
                                              + " was invoked");
    logVisitor = std::make_unique<LogVisitor>();
    for (size_t i = 0; i < vecDynamicObj.size(); i++) {
        if (vecDynamicObj[i] != nullptr) {
            vecDynamicObj[i]->Move(deltaTime);
            vecDynamicObj[i]->Accept(logVisitor.get());
        }
    }
};

void SBomber::CheckObjects() {
    FileLoggerProxy::getInstance().WriteToLog(std::string(__func__)
                                              + " was invoked");
    m_CollisionD->CheckPlaneAndLevelGUI();
    m_CollisionD->CheckBombsAndGround();
};


void SBomber::ProcessKBHit() {
    int c = getchar();

    if (c == 224) {
        c = getchar();
    }

    FileLoggerProxy::getInstance().WriteToLog(std::string(__func__)
                                              + " was invoked. key = ", c);

    //Creating Command
    auto context = std::make_unique<Context>();
    auto command = std::make_unique<CommandDropBomb>();

    Plane *plane = m_CollisionD->FindPlane();
    context->setParam(plane, vecDynamicObj, bombsNumber, 2,
                      SMALL_CRATER_SIZE, score);
    command->setParam(context.get());

    switch (c) {

        case 27: // esc
            exitFlag = true;
            break;

        case 72: // up
            m_CollisionD->FindPlane()->ChangePlaneY(-0.25);
            break;

        case 80: // down
            m_CollisionD->FindPlane()->ChangePlaneY(0.25);
            break;

        case 'b':
            CommandExecute(command.get());
            updateFromCommand(context.get());
            break;

        case 'B':
            CommandExecute(command.get());
            updateFromCommand(context.get());
            break;

        default:
            break;
    }
}

void SBomber::DrawFrame() {
    FileLoggerProxy::getInstance().WriteToLog(std::string(__func__)
                                              + " was invoked");
    for (size_t i = 0; i < vecDynamicObj.size(); i++) {
        if (vecDynamicObj[i] != nullptr) {
            vecDynamicObj[i]->Draw();
        }
    }

    for (size_t i = 0; i < vecStaticObj.size(); i++) {
        if (vecStaticObj[i] != nullptr) {
            vecStaticObj[i]->Draw();
        }
    }

    ScreenSingleton::getInstance().GotoXY(0, 0);
    fps++;

    m_CollisionD->FindLevelGUI()->SetParam(passedTime, fps, bombsNumber, score);
}

void SBomber::TimeStart() {
    FileLoggerProxy::getInstance().WriteToLog(std::string(__func__)
                                              + " was invoked");
    startTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

void SBomber::TimeFinish() {
    finishTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    deltaTime = uint16_t(finishTime - startTime);
    passedTime += deltaTime;

    FileLoggerProxy::getInstance().WriteToLog(std::string(__func__)
                                              + " deltaTime = ", (int) deltaTime);
}


void SBomber::run() {
    do {
        TimeStart();
        GetCurDateTimeSingleton::getInstance().Start();

        if (_kbhit()) {
            ProcessKBHit();
        }

        ScreenSingleton::getInstance().ClrScr();

        DrawFrame();
        MoveObjects();
        CheckObjects();

        TimeFinish();

        GetCurDateTimeSingleton::getInstance().SaveTime();

    } while (!GetExitFlag());

    std::cout << "  Result of logging \t";
    std::cout << GetCurDateTimeSingleton::getInstance().Calculating();
    std::cout << "\n";

}

void SBomber::CommandExecute(Command *command) {
    command->execute();
}

void SBomber::updateFromCommand(Context *context) {
    bombsNumber = context->mBombCount;
    vecDynamicObj = context->mVecDynamicObject;
    score = context->mScore;
}


