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
    Key(const char* pub,const char* priv);
    ~Key();

    string getPriv();
    string getPub();
    string getPlain();
    string getCipher();
    bool save(string dir);
    bool ReadPlaintext(const char* filename);
    bool ReadCiphertext(const char* filename);
    bool ReadPubKey(const char* filename);
    bool ReadPrivKey(const char* filename);
    bigNumber* encrypt();
    bigNumber decrypt();
private:
    string priv_key;
    string pub_key;
    string plaintext;
    string ciphertext;
    bigNumber decrypt(bigNumber p,bigNumber x,bigNumber a,bigNumber b);
    bigNumber *encrypt(bigNumber p,bigNumber g,bigNumber y,bigNumber m);
};



#endif // KEY_H
