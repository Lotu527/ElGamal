#ifndef KEY_H
#define KEY_H

#include <string>
#include "bignumber.h"
using std::string;
class Key
{
public:
    Key();
    Key(int bitlen);
    ~Key();

    string getPriv();
    string getPub();

private:
    string priv_key;
    string pub_key;
    bigNumber decrypt(bigNumber p,bigNumber x,bigNumber a,bigNumber b);
    bigNumber *encrypt(bigNumber p,bigNumber g,bigNumber y,bigNumber m);
};



#endif // KEY_H
