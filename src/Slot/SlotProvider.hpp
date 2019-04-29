#pragma once

#include "SlotItem.hpp"
#include <functional>
#include <string>
#include <algorithm>
#include <map>

class SlotProvider
{
public:
    using filter_fn = std::function<bool(const Slot&)>;
    using sort_fn = std::function<bool(const Slot&,const Slot&)>;
    using group_fn = std::function<std::string(const Slot&)>;

    SlotProvider & set_sort(sort_fn cmp)
    {
        sort = cmp;
        return *this;
    }
    SlotProvider & set_filter(filter_fn pred)
    {
        filter = pred;
        return *this;
    }
    SlotProvider & set_group(group_fn group_)
    {
        group = group_;
        return *this;
    }

    std::map<std::string,std::vector<Slot*>> gmp(auto b,auto e)
    {
        std::map<std::string,std::vector<Slot*>> mp;
        std::vector<Slot*> vec;
        auto F = filter?filter:[](const auto &){return true;};
        for(auto c = b;c!=e;++c)
            if(F(*c))vec.push_back(&*c);
        
        if(sort)std::sort(vec.begin(),vec.end(),[*this](const auto &l,const auto &r){return sort(*l,*r);});
        auto G = group?group:[](const auto &){return "";};
        for(auto &v:vec)mp[G(*v)].push_back(v);
        return mp;
    }
private:
    filter_fn filter;
    sort_fn sort;
    group_fn group;
};

