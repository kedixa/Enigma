/*
 * Copyright 2017 kedixa
 * kedixa@outlook.com
 *
 * License Apache 2.0
 *
 */
#ifndef KEDIXA_ENIGMA_H
#define KEDIXA_ENIGMA_H

#include "Plugboard.h"
#include "Rotor.h"
#include "Reflector.h"
#include <vector>
using std::vector;
using std::string;
class Enigma
{
private:
    Plugboard pb;
    vector<Rotor> vr;
    Reflector ref;
    int _encode(int in) noexcept
    {
        in = pb.mapping(in);
        for(auto it = vr.cbegin(); it != vr.cend(); ++it)
            in = it->forward_mapping(in);
        in = ref.mapping(in);
        for(auto it = vr.crbegin(); it != vr.crend(); ++it)
            in = it->backward_mapping(in);
        in = pb.mapping(in);

        // after encode one character, rotate the Rotors
        if(vr.size() > 0)
        {
            vr[0].step();
            for(size_t i = 1; i < vr.size(); ++i)
            {
                if(vr[i-1].is_circle())
                    vr[i].step();
                else break;
            }
        }
        return in;
    }
public:
    Enigma(Plugboard pb, vector<Rotor> vr, Reflector ref)
    {
        this->pb = pb;
        this->vr = vr;
        this->ref = ref;
    }
    Enigma& operator=(const Enigma&) =delete;

    // set the initial state of the rotors
    void set_rotors(vector<char> vc) noexcept
    {
        size_t mi = std::min(vc.size(), vr.size());
        for(size_t i = 0; i < mi; ++i)
        {
            if(isalpha(vc[i]))
                vr[i].set_rotor(toupper(vc[i]) - 'A');
        }
    }
    void reset_rotors() noexcept
    {
        for(auto &r : vr)
            r.reset();
    }
    string encode(const string &s) noexcept
    {
        string result;
        result.reserve(s.length());
        for(size_t i = 0; i < s.length(); ++i)
        {
            char c;
            if(islower(s[i])) c = this->_encode(s[i] - 'a') + 'a';
            else if(isupper(s[i])) c = this->_encode(s[i] - 'A') + 'A';
            else c = s[i];
            result.push_back(c);
        }
        return result;
    }
    string decode(const string &s) noexcept
    {
        return encode(s);
    }
};

#endif // KEDIXA_ENIGMA_H
