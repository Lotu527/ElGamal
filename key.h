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
    bool ReadPlaintext(const char* filename);//从文件读取明文内容
    bool ReadCiphertext(const char* filename);//从文件读完密文内容
    bool ReadPubKey(const char* filename);//从文件读取公钥
    bool ReadPrivKey(const char* filename);//从文件读取私钥
    bool ReadSign(const char* filename);//从文件读取签名
    bigNumber* encrypt();
    std::string decrypt();

    bigNumber* SignProduce();
    bool Check();
private:
    string priv_key;//私钥
    string pub_key;//公钥
    string plaintext;//明文
    string ciphertext;//密文
    string signtext;//签名
    bigNumber decrypt(bigNumber p,bigNumber x,bigNumber a,bigNumber b);//对密文a(C1)，b(C2)解密
    bigNumber *encrypt(bigNumber p,bigNumber g,bigNumber y,bigNumber m);//对明文m加密
};



#endif // KEY_H
