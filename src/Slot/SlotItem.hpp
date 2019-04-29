#pragma once
#include <string>
#include <memory>

class SlotItem
{
public:
    virtual ~SlotItem(){}
    virtual std::unique_ptr<SlotItem> copy() const = 0;
    virtual bool equal(const SlotItem &) const = 0;
    virtual std::string toString() const = 0;
};