#pragma once
#include "SlotPack.hpp"

class SlotLimit
{
public:
    virtual size_t get_max(const SlotItem &) const = 0;
    virtual ~SlotLimit(){}
};