#include "key.h"
#include "tool.h"
#include<iostream>
#include<QDebug>
Key::Key()
{

}

Key::Key(int bitlen)
{
    initRandom();
    bigNumber p = GeneratePrime(bitlen);
    bigNumber g = GenerateRandomMax(p);
    bigNumber x = GenerateRandomMax(p);
    bigNumber y = Pow(g,x,p);
    //公钥
    std::string str1 = p.GetString();
    str1.append("\n");
    str1.append(g.GetString());
    str1.append("\n");
    str1.append(y.GetString());
    this->pub_key=str1;
    //私钥
    std::string str2 = p.GetString();
    str2.append("\n");
    str2.append(x.GetString());
    this->priv_key=str2;

}

std::string Key::getPriv()
{
    return this->priv_key;
}

std::string Key::getPub()
{
    return this->pub_key;
}


bigNumber Key::decrypt(bigNumber p, bigNumber x, bigNumber a, bigNumber b)
{
    bigNumber m = (b * Pow(a,p-1-x,p))%p;
    return m;
}

bigNumber *Key::encrypt(bigNumber p, bigNumber g, bigNumber y, bigNumber m)
{
    if(m>=p){
        std::cout<<"message is too large!\n";
        exit(1);
    }
    bigNumber* arr = new bigNumber[2];
    bigNumber k = GenerateRandomMax(p-2) + 1;
    arr[0] = Pow(g,k,p);
    arr[1] = Pow(y,k,p);
    arr[1] = (arr[1] * m) % p;
    return arr;
}
