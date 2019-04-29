#pragma once
#include "SlotItem.hpp"

#include <memory>
#include <iostream>

class SlotPack
{
public:
    std::unique_ptr<SlotItem> ptr;
    size_t cnt;

    SlotPack():ptr(nullptr),cnt(0){}
    SlotPack(std::unique_ptr<SlotItem> p,size_t c):ptr(std::move(p)),cnt(c)
    {
        if(!ptr)cnt = 0;
    }
    SlotPack(SlotPack &&o):
        ptr(std::exchange(o.ptr,nullptr)),
        cnt(std::exchange(o.cnt,0)){}
    
    void swap(SlotPack &o)
    {
        std::swap(ptr,o.ptr);
        std::swap(cnt,o.cnt);
    }

    SlotPack & operator = (SlotPack pack)
    {
        swap(pack);
        return *this;
    }
};

std::ostream & operator << (std::ostream &s,const SlotPack &p)
{
    return s<<(p.ptr?p.ptr->toString():"")<<" "<<p.cnt;
}