#pragma once

#include "SlotLimit.hpp"

class Slot
{
    SlotPack pack;
    std::shared_ptr<SlotLimit> limit;
public:
    Slot():pack(),limit(){}
    Slot(Slot &&v):
        pack(std::exchange(v.pack,{})),
        limit(std::exchange(v.limit,nullptr)){}

    std::shared_ptr<SlotLimit> set_limit(std::shared_ptr<SlotLimit> new_limit)
    {
        return std::exchange(limit,new_limit);
    }
    std::shared_ptr<const SlotLimit> get_limit() const
    {
        return limit;
    }

    size_t get_max(const SlotItem &i) const
    {
        return limit?limit->get_max(i):-1;
    }

    const SlotPack & get() const
    {
        return pack;
    }

    SlotPack replace(SlotPack o)
    {
        if(o.ptr && get_max(*o.ptr) >= o.cnt)
            return std::exchange(pack,std::move(o));
        return o;
    }
    
    SlotPack add(SlotPack o)
    {
        if(!o.ptr)return o;

        if(!pack.ptr || (pack.ptr->equal(*o.ptr)))
        {
            size_t m = get_max(*o.ptr);
            m = std::min(o.cnt,m - pack.cnt);
            if(!pack.ptr)pack.ptr = o.ptr->copy();
            pack.cnt += m;
            o.cnt -= m;
            if(o.cnt == 0)o.ptr = nullptr;
            return o;
        }
        return o;
    }

    void replace(Slot &o)
    {
        o.pack = replace(std::move(o.pack));
    }
    void add(Slot &o)
    {
        o.pack = add(std::move(o.pack));
    }

    SlotPack extract()
    {
        return std::move(pack);
    }
};