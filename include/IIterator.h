#ifndef SBOMBER_IITERATOR_H
#define SBOMBER_IITERATOR_H

#include "DynamicObject.h"

class IIterator {
public:
    virtual void First() = 0;
    virtual Bomb* Next() = 0;
    [[nodiscard]] virtual bool isDone() const = 0;
    [[nodiscard]] virtual Bomb* CurrentObj() = 0;
    virtual ~IIterator() = default;
};


#endif //SBOMBER_IITERATOR_H
