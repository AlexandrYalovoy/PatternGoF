#ifndef SBOMBER_IVISITOR_H
#define SBOMBER_IVISITOR_H

#include <memory>

class Bomb;
class Plane;

class IVisitor {
public:
    virtual ~IVisitor() = default;

    virtual void visit(Bomb* pBomb) const = 0;
    virtual void visit(Plane* pPlane) const = 0;
};


class LogVisitor : public IVisitor {
public:
    void visit(Bomb* pBomb) const override;
    void visit(Plane* pPlane) const override;
};

#endif //SBOMBER_IVISITOR_H
