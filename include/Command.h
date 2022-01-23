#ifndef SBOMBER_COMMAND_H
#define SBOMBER_COMMAND_H

#include "SBomber.h"
#include "TestFileLogger.h"
#include "BombDecorator.h"

//Command pattern

class IContext {
public:
    IContext();
    virtual ~IContext();
    virtual void setParam(const Plane* plane,
                          std::vector<DynamicObject*>& vecDynamicObject,
                          const uint16_t& bomber,
                          const double& speed,
                          const uint16_t& widthCrater,
                          const int16_t& score) = 0;
public:
    const Plane* mPlane;
    std::vector<DynamicObject*> mVecDynamicObject;
    uint16_t mBombCount;
    double mSpeed;
    uint16_t mWidthCrater;
    int16_t mScore;
};

class Context : public IContext {
public:
    ~Context() override;

    void setParam(const Plane *plane,
                  std::vector<DynamicObject*>& vecDynamicObject,
                  const uint16_t& bomber,
                  const double& speed,
                  const uint16_t& widthCrater,
                  const int16_t& score) override;
};

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};

class CommandDropBomb : public Command {
public:
    ~CommandDropBomb() override = default;
    void setParam(IContext* context);

    void execute() override;

private:
    IContext* mContext;
};

class DeleteStaticObj : public Command {
public:
     DeleteStaticObj();
    ~DeleteStaticObj() override = default;

    void setParam(GameObject* pObj, const std::vector<GameObject*>& vecStaticObj);
    void execute() override;
    //Getters and Setters
    [[nodiscard]] const std::vector<GameObject*>& getStaticVectorObject() const;
private:
    std::vector<GameObject*> mStaticVector;
    GameObject* mStaticObject;
};

class DeleteDynamicObj : public Command {
public:
    explicit DeleteDynamicObj();
    ~DeleteDynamicObj() override = default;

    void setParam(DynamicObject* obj, const std::vector<DynamicObject*>& vec);
    void execute() override;

    //Getters and Setters
    [[nodiscard]] const std::vector<DynamicObject*>& getDynamicVectorObject() const;
private:
    std::vector<DynamicObject*> mDynamicVector;
    DynamicObject* mDynamicObj;
};

#endif //SBOMBER_COMMAND_H
