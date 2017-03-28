/*
 * Copyright 2017 kedixa
 * kedixa@outlook.com
 *
 * License Apache 2.0
 *
 */
#ifndef KEDIXA_ROTOR_H
#define KEDIXA_ROTOR_H

#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <chrono>
#include <random>
using std::vector;
using std::string;
class Rotor
{
private:
    vector<int> va, vb;  // mapping
    int current_pos;     // current position of the Rotor

    // calculate reverse mapping
    void calvb() noexcept
    {
        // assume va was construct correctly
        vb.resize(26);
        for(size_t i = 0; i < 26; ++i)
            vb[va[i]] = i;
    }
    // construct a random Rotor
    void random() noexcept
    {
        va.resize(26);
        for(size_t i = 0; i < 26; ++i)
            va[i] = i;
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(va.begin(), va.end(), std::default_random_engine(seed));
        this->calvb();
    }
public:
    Rotor()
    {
        this->random();
        current_pos = 0;
    }
    // construct Rotor using s
    Rotor(const string &s)
    {
        // check whether s is legal
        if(s.length() != 26)
            throw std::runtime_error("Rotor: string length must be 26.");
        string tmp = s;
        for(auto &c : tmp)
            c = toupper(c);
        sort(tmp.begin(), tmp.end());
        for(size_t i = 0; i < 26; ++i)
        {
            if(tmp[i] != 'A' + i)
                throw std::runtime_error("Rotor: string must be a permutation of A...Z.");
        }
        // using s to represent positive side of Rotor
        va.resize(26);
        for(size_t i = 0; i < 26; ++i)
            va[i] = toupper(s[i]) - 'A';
        this->calvb();
        current_pos = 0;
    }
    Rotor(const Rotor &r)
    {
        this->va = r.va;
        this->vb = r.vb;
        this->current_pos = r.current_pos;
    }
    Rotor& operator= (const Rotor &r) noexcept
    {
        if(this != &r)
        {
            this->va = r.va;
            this->vb = r.vb;
            this->current_pos = r.current_pos;
        }
        return *this;
    }
    int forward_mapping(int in) const
    {
        if(in < 0 || in > 25)
            throw std::runtime_error("Rotor::forward_mapping: in must in [0, 25].");
        return va[in];
    }
    int backward_mapping(int in) const
    {
        if(in < 0 || in > 25)
            throw std::runtime_error("Rotor::backward_mapping: in must in [0, 25].");
        return vb[in];
    }
    void reset() noexcept
    {
        current_pos = 0;
    }
    void set_rotor(int in)
    {
        current_pos = std::find(va.begin(), va.end(), in) - va.begin();
    }
    void step() noexcept
    {
        current_pos = (current_pos + 1) % 26;
    }
    bool is_circle() const noexcept
    {
        return current_pos == 0;
    }
    std::string to_string() const noexcept
    {
        std::string s;
        s.reserve(26);
        for(size_t i = 0; i < 26; ++i)
            s.push_back('A' + va[i]);
        return s;
    }
};

#endif // KEDIXA_ROTOR_H
