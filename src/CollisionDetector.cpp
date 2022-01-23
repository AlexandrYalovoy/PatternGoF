#include <memory>


#include "CollisionDetector.h"
#include "BombIterator.h"
#include "OddBombIterator.h"

CollisionDetector::CollisionDetector(const std::vector<GameObject*>& vecStaticObj,
                                     const std::vector<DynamicObject*>& vecDynamicObj, int16_t score,
                                     bool exitFlag) :
        m_vecStaticObj(vecStaticObj), m_vecDynamicObj(vecDynamicObj), m_score(score), m_exitFlag(exitFlag) {}




void CollisionDetector::CheckPlaneAndLevelGUI() {
    if (FindPlane()->GetX() > FindLevelGUI()->GetFinishX()) {
        m_exitFlag = true;
    }
}

void CollisionDetector::CheckBombsAndGround() {
    Ground *pGround = FindGround();
    const double y = pGround->GetY();
    std::vector<Bomb *> vecBombs = FindAllBombs();

    for (const auto& i : vecBombs) {
        if (i->GetY() >= y) {
            pGround->AddCrater(i->GetX());
            CheckDestroyableObjects(i);
            auto command = std::make_unique<DeleteDynamicObj>();
            //Using Command pattern
            command->setParam(i, m_vecDynamicObj);
            CommandExecute(command.get());
        }
    }
}

void CollisionDetector::CheckDestroyableObjects(Bomb* pBomb) {
    std::vector<DestroyableGroundObject *> vecDestroyableObjects =
            FindDestroyableGroundObjects();
    const double size = pBomb->GetWidth();
    const double size_2 = size / 2;
    for (size_t i = 0; i < vecDestroyableObjects.size(); i++) {
        const double x1 = pBomb->GetX() - size_2;
        const double x2 = x1 + size;
        if (vecDestroyableObjects[i]->isInside(x1, x2)) {
            m_score += vecDestroyableObjects[i]->GetScore();
            //Using Command pattern
            auto command = std::make_unique<DeleteStaticObj>();
            command->setParam(vecDestroyableObjects[i], m_vecStaticObj);
            CommandExecute(command.get());
        }
    }
}

void CollisionDetector::CommandExecute(Command *command) {
    command->execute();
}



Ground *CollisionDetector::FindGround() const {
    Ground *pGround;

    for (size_t i = 0; i < m_vecStaticObj.size(); i++) {
        pGround = dynamic_cast<Ground *>(m_vecStaticObj[i]);
        if (pGround != nullptr) {
            return pGround;
        }
    }

    return nullptr;
}

Plane *CollisionDetector::FindPlane() const {
    for (size_t i = 0; i < m_vecDynamicObj.size(); i++) {
        Plane *p = dynamic_cast<Plane *>(m_vecDynamicObj[i]);
        if (p != nullptr) {
            return p;
        }
    }

    return nullptr;
}

LevelGUI *CollisionDetector::FindLevelGUI() const {
    for (size_t i = 0; i < m_vecStaticObj.size(); i++) {
        LevelGUI *p = dynamic_cast<LevelGUI *>(m_vecStaticObj[i]);
        if (p != nullptr) {
            return p;
        }
    }

    return nullptr;
}

std::vector<DestroyableGroundObject *> CollisionDetector::FindDestroyableGroundObjects() const {
    std::vector<DestroyableGroundObject *> vec;
    Tank *pTank;
    House *pHouse;
    for (size_t i = 0; i < m_vecStaticObj.size(); i++) {
        pTank = dynamic_cast<Tank *>(m_vecStaticObj[i]);
        if (pTank != nullptr) {
            vec.push_back(pTank);
            continue;
        }

        pHouse = dynamic_cast<House *>(m_vecStaticObj[i]);
        if (pHouse != nullptr) {
            vec.push_back(pHouse);
            continue;
        }
    }

    return vec;
}

std::vector<Bomb *> CollisionDetector::FindAllBombs() const {
    std::vector<Bomb *> vecBombs;

    for (const auto& i : vecBombs) {
        Bomb *pBomb = i;
        if (pBomb != nullptr) {
            vecBombs.push_back(pBomb);
        }
    }

    return vecBombs;
}

