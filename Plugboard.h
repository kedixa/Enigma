/*
 * Copyright 2017 kedixa
 * kedixa@outlook.com
 *
 * License Apache 2.0
 *
 */
#ifndef KEDIXA_PLUGBOARD_H
#define KEDIXA_PLUGBOARD_H

#include <vector>
#include <unordered_map>
using std::vector;
using std::pair;
using std::unordered_map;
class Plugboard
{
private:
    unordered_map<int, int> umap;
public:
    Plugboard() {}
    // using some pairs of char to construct Plugboard
    Plugboard(const vector<pair<char,char>> vpcc)
    {
        for(const auto &pcc : vpcc)
        {
            if(pcc.first == pcc.second) continue;
            if(!isalpha(pcc.first) || !isalpha(pcc.second)) continue;
            int x = toupper(pcc.first) - 'A', y = toupper(pcc.second) - 'A';
            if(umap.find(x) == umap.end())
            {
                umap[x] = y;
                umap[y] = x;
            }
        }
    }
    Plugboard(const Plugboard &p)
    {
        this->umap = p.umap;
    }
    Plugboard& operator= (const Plugboard &p) noexcept
    {
        if(this != &p)
        {
            this->umap = p.umap;
        }
        return *this;
    }
    int mapping(int in) const
    {
        if(in < 0 || in > 25)
            throw std::runtime_error("Plugboard::mapping: in must in [0, 25].");
        auto it = umap.find(in);
        if(it == umap.end()) return in;
        else return it->second;
    }
};

#endif // KEDIXA_PLUGBOARD_H
