#include <iostream>
#include <vector>
#include <string>
#include "Enigma.h"
using namespace std;

int main()
{
    vector<Rotor> vr;
    for(int i = 0; i < 3; ++i)
        vr.push_back(Rotor());
    Plugboard pb({{'A', 'B'}, {'X', 'Y'}});
    //Plugboard pb;
    Reflector ref;
    Enigma eng(pb, vr, ref);
    eng.set_rotors({'A', 'T', 'G'});
    string code = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string encode;
    encode = eng.encode(code);
    cout << "After encode, '" << code << "' becomes '" << encode << "'.\n";

    // Make another Enigma machine using the same Plugboard, Rotor and Reflector,
    // these information need to be passed to the decoder in other ways.
    vector<Rotor> vr2;
    for(int i = 0; i < 3; ++i)
        vr2.push_back(Rotor(vr[i].to_string()));
    Plugboard pb2({{'A', 'B'}, {'X', 'Y'}});
    Reflector ref2(ref.to_string());
    Enigma eng2(pb2, vr2, ref2);
    // set the rotors state before decode
    eng2.set_rotors({'A', 'T', 'G'});
    string decode = eng2.decode(encode);
    cout << "After decode, '" << encode << "' becomes '" << decode << "'.\n";
    return 0;
}
