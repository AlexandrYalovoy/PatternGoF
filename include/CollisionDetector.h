#pragma once

#include "Command.h"

class Command;

class CollisionDetector {
public:
    CollisionDetector(const std::vector<GameObject*>& vecStaticObj,
                      const std::vector<DynamicObject*>& vecDynamicObj,
                      int16_t score, bool exitFlag);

    void CheckPlaneAndLevelGUI();
    void CheckBombsAndGround();
    void  CheckDestroyableObjects(Bomb* pBomb);
    static void CommandExecute(Command* command);

    Ground * FindGround() const;
    Plane * FindPlane() const;
    LevelGUI * FindLevelGUI() const;
    [[nodiscard]] std::vector<DestroyableGroundObject*> FindDestroyableGroundObjects() const;
    std::vector<Bomb*> FindAllBombs() const;
private:
    int16_t m_score;
    bool m_exitFlag;
    std::vector<GameObject*> m_vecStaticObj;
    std::vector<DynamicObject*> m_vecDynamicObj;
};