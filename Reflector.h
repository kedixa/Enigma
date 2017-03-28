/*
 * Copyright 2017 kedixa
 * kedixa@outlook.com
 *
 * License Apache 2.0
 *
 */

#ifndef KEDIXA_REFLECTOR_H
#define KEDIXA_REFLECTOR_H

#include <vector>
#include <string>
#include <stdexcept>
#include <cctype>
#include <algorithm>
#include <random>
#include <chrono>
using std::vector;
using std::string;
class Reflector
{
private:
    vector<int> v;

    // construct a random Reflector
    void random() noexcept
    {
        vector<int> tmp;
        tmp.resize(26);
        for(size_t i = 0; i < 26; ++i)
            tmp[i] = i;
        
        // shuffle the vector using seed
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(tmp.begin(), tmp.end(), std::default_random_engine(seed));
        v.resize(26);
        for(size_t i = 0; i < 26; i+=2)
        {
            v[tmp[i]] = tmp[i+1];
            v[tmp[i+1]] = tmp[i];
        }
    }
public:
    Reflector()
    {
        this->random();
    }
    Reflector(const string &s)
    {
        // check whether s is legal
        if(s.length() != 26)
            throw std::runtime_error("Reflector: string length must be 26.");
        string tmp = s;
        for(auto &c : tmp)
            c = toupper(c);
        sort(tmp.begin(), tmp.end());
        for(size_t i = 0; i < 26; ++i)
        {
            if(tmp[i] != 'A' + i)
                throw std::runtime_error("Reflector: string must be a permutation of A...Z.");
        }
        // using s to construct a Reflector
        v.resize(26);
        for(size_t i = 0; i < 26; ++i)
            v[i] = toupper(s[i]) - 'A';
    }
    Reflector(const Reflector &r)
    {
        this->v = r.v;
    }
    Reflector& operator= (const Reflector &r) noexcept
    {
        if(this != &r)
        {
            this->v = r.v;
        }
        return *this;
    }
    int mapping(int in) const
    {
        if(in < 0 || in > 25)
            throw std::runtime_error("Reflector::mapping: in must in [0, 25].");
        return v[in];
    }
    std::string to_string() const noexcept
    {
        std::string s;
        s.reserve(26);
        for(size_t i = 0; i < 26; ++i)
            s.push_back('A' + v[i]);
        return s;
    }
};
#endif // KEDIXA_REFLECTOR_H
