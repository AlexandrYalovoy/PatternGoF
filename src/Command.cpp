#include "Command.h"

IContext::IContext() : mPlane(nullptr),
                        mBombCount(0),
                        mSpeed(0),
                        mWidthCrater(0),
                        mScore(0) {
/*TestFileLogger::getInstance().WriteToLog(std::string(
        __func__) + " IContext() was invoked");*/
}

IContext::~IContext() {
    std::cout << "~IContext()" << '\n';
}

Context::~Context() {
    /*TestFileLogger::getInstance().WriteToLog(std::string(__func__) +
                                  "Destructor was invoked");*/
}

void Context::setParam(const Plane *plane, std::vector<DynamicObject *> &vecDynamicObject, const uint16_t &bomber,
                       const double &speed, const uint16_t &widthCrater, const int16_t &score) {

    this->mPlane = plane;
    mVecDynamicObject = vecDynamicObject;
    mBombCount = bomber;
    mSpeed = speed;
    mWidthCrater = widthCrater;
    mScore = score;
    /*TestFileLogger::getInstance().WriteToLog(std::string(
            __func__) + " Context::setParam() was invoked");*/
}

void CommandDropBomb::setParam(IContext *context) {
    this->mContext = context;
    /*TestFileLogger::getInstance().WriteToLog(std::string(
            __func__) + " CommandDropBomb::setParam() was invoked");*/
}

void CommandDropBomb::execute() {
    if (mContext->mBombCount > 0) {
        FileLoggerProxy::getInstance().WriteToLog(std::string(__func__)
                                                  + " was invoked");
        /*TestFileLogger::getInstance().WriteToLog(std::string(
                __func__) + " CommandDropBomb::execute() was invoked");*/
        double x = mContext->mPlane->GetX() + 4;
        double y = mContext->mPlane->GetY() + 2;
        /*TestFileLogger::getInstance().WriteToLog(std::string(
                __func__) +
                                                 " Score = " + std::to_string(mContext->mScore) +
                                                 " Bombs number = " + std::to_string(mContext->mBombCount));*/

        auto* pBomb = new Bomb;
        pBomb->SetDirection(0.3, 1);
        pBomb->SetSpeed(mContext->mSpeed);
        pBomb->SetPos(x, y); pBomb->SetWidth(mContext->mWidthCrater);
//        auto decorator = new BombDecorator(pBomb);

        mContext->mVecDynamicObject.push_back(pBomb);
        mContext->mBombCount--;
        mContext->mScore -= Bomb::BombCost;
        /*TestFileLogger::getInstance().WriteToLog(std::string(__func__)
                                                 + " Score = " + std::to_string(mContext->mScore) +
                                                 " Bombs number = " + std::to_string(mContext->mBombCount));*/
    }
}

DeleteStaticObj::DeleteStaticObj() : mStaticObject(nullptr) {}

void DeleteStaticObj::setParam(GameObject *pObj, const std::vector<GameObject *> &vecStaticObj) {
    this->mStaticObject = pObj;
    this->mStaticVector = vecStaticObj;
}

void DeleteStaticObj::execute() {
    auto it = mStaticVector.begin();
    for (; it != mStaticVector.end(); it++) {
        if (*it == mStaticObject) {
            mStaticVector.erase(it);
            break;
        }
    }
}

DeleteDynamicObj::DeleteDynamicObj() : mDynamicObj(nullptr) {}

void DeleteDynamicObj::setParam(DynamicObject *obj, const std::vector<DynamicObject *> &vec) {
    this->mDynamicObj = obj;
    this->mDynamicVector = vec;
}

void DeleteDynamicObj::execute() {
    auto it = mDynamicVector.begin();
    for (; it != mDynamicVector.end(); it++) {
        if (*it == mDynamicObj) {
            mDynamicVector.erase(it);
            break;
        }
    }
}

const std::vector<DynamicObject *> &DeleteDynamicObj::getDynamicVectorObject() const {
    return mDynamicVector;
}

const std::vector<GameObject *> &DeleteStaticObj::getStaticVectorObject() const {
    return mStaticVector;
}













