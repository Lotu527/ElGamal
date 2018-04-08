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
    string getSign();
    bool save(string dir);
    bool ReadPlaintext(const char* filename);
    bool ReadCiphertext(const char* filename);
    bool ReadPubKey(const char* filename);
    bool ReadPrivKey(const char* filename);
    bool ReadSign(const char* filename);
    bigNumber* encrypt();
    std::string decrypt();

    bigNumber* SignProduce();
    bool Check();
private:
    string priv_key;
    string pub_key;
    string plaintext;
    string ciphertext;
    string signtext;
    bigNumber decrypt(bigNumber p,bigNumber x,bigNumber a,bigNumber b);
    bigNumber *encrypt(bigNumber p,bigNumber g,bigNumber y,bigNumber m);
};



#endif // KEY_H
