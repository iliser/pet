#pragma once

#include "SlotItem.hpp"

#include <memory>

template<class T>
class Resource:public SlotItem
{
public:
    virtual ~Resource(){}
    virtual std::unique_ptr<SlotItem> copy() const final
    {
        return std::make_unique<T>();
    }
    virtual bool equal(const SlotItem &o) const final
    {
        return dynamic_cast<const T *>(&o);
    }
    
    static std::unique_ptr<T> make() {return std::make_unique<T>();}
};