#pragma once

#include <vector>
#include <chrono>
#include <memory>

#include "LevelGUI.h"
#include "Plane.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
#include "House.h"
#include "FileLoggerProxy.h"
#include "ScreenSingleton.h"
#include "enums/CraterSize.h"
#include "CollisionDetector.h"

class Command;
class IContext;
class Context;
class CollisionDetector;

class SBomber
{
public:

    explicit SBomber(int type_house);
    ~SBomber();

    inline bool GetExitFlag() const { return exitFlag; }

    void ProcessKBHit();
    void TimeStart();
    void TimeFinish();

    void DrawFrame();
    void MoveObjects();
    void CheckObjects();

    void run();

    //static methods
    static Plane* createPlane();
    static LevelGUI* createUI(const uint64_t passedTime,
                              const uint16_t fps,
                              const uint16_t bombsNumber,
                              const int16_t score);
    static Ground* createGround();
    static Tank* createTank(const double pos, const uint16_t width);
    House* createHouse(const double pos, const uint16_t width) const;

    static void CommandExecute(Command* command);
private:
    void updateFromCommand(Context* context);

    std::vector<DynamicObject*> vecDynamicObj;
    std::vector<GameObject*> vecStaticObj;

    bool exitFlag;
    bool oddIteration; // for Pattern Iterator, switching between Odd or Even Iteration

    uint64_t startTime, finishTime, passedTime;
    uint16_t bombsNumber, deltaTime, fps;
    int16_t score;

    int m_type_house; // for Pattern Builder.
    std::unique_ptr<CollisionDetector> m_CollisionD;
    std::unique_ptr<IVisitor> logVisitor;
};



