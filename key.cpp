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

Key::Key(const char *pub, const char *priv)
{
    this->pub_key = pub;
    this->priv_key = priv;
}

std::string Key::getPriv()
{
    return this->priv_key;
}

std::string Key::getPub()
{
    return this->pub_key;
}

std::string Key::getPlain()
{
    return this->plaintext;
}

std::string Key::getCipher()
{
    return this->ciphertext;
}

bool Key::save(string dir)
{
    //保存公钥和私钥
    string pub_file = dir + "/" + "key.pub";
    string priv_file = dir + "/" + "key.priv";
    if(SaveFile(pub_file.c_str(),this->getPub())
            && SaveFile(priv_file.c_str(),this->getPriv()))
        return true;
    return false;
}

bool Key::ReadPlaintext(const char *filename)
{
    this->plaintext = ReadFromFile(filename);
    if(!plaintext.empty())return true;
    return false;
}

bool Key::ReadCiphertext(const char *filename)
{
    this->ciphertext = ReadFromFile(filename);
    if(!ciphertext.empty())return true;
    return false;
}

bool Key::ReadPubKey(const char *filename)
{
    this->pub_key = ReadFromFile(filename);
    if(pub_key.empty())return false;
    return true;
}

bool Key::ReadPrivKey(const char *filename)
{
    this->priv_key = ReadFromFile(filename);
    if(priv_key.empty())return false;
    return true;
}


//对密文解密
//p,选取的素数
//x,私钥k
//a,密文c1
//b,密文c2
bigNumber Key::decrypt(bigNumber p, bigNumber x, bigNumber a, bigNumber b)
{
    bigNumber m = (b * Pow(a,p-1-x,p))%p;
    return m;
}
//对明文M加密
//p，选取的素数
//g，模p的一个本原
//y，公钥
bigNumber *Key::encrypt(bigNumber p, bigNumber g, bigNumber y, bigNumber m)
{
    if(m>=p){
        std::cout<<"message is too large!\n";
        exit(1);
    }
    bigNumber* arr = new bigNumber[2];
    bigNumber k = GenerateRandomMax(p-2) + 1;
    arr[0] = Pow(g,k,p);
    arr[1] = Pow(y,k) * m % p;
    return arr;
}

bigNumber *Key::encrypt()
{
    if(this->getPlain().empty() || this->getPub().empty()){
        return nullptr;
    }

    bigNumber m = NumberFromBinString(this->getPlain());
    int arr[4];
    arr[0]=0;
    arr[3]=this->pub_key.length();
    for(int i=0,j=1;i < this->pub_key.length() && j<3;i++){
        if(this->pub_key[i] == '\n')
            arr[j++]=i+1;
    }
    bigNumber p = StringToNumber(this->pub_key.substr(arr[0],arr[1]-1));
    bigNumber g = StringToNumber(this->pub_key.substr(arr[1],arr[2]-arr[1]-1));
    bigNumber y = StringToNumber(this->pub_key.substr(arr[2],arr[3]-arr[2]));
    return encrypt(p,g,y,m);
}

bigNumber Key::decrypt()
{
    int tag = this->ciphertext.find('\n');
    bigNumber C1=this->ciphertext.substr(0,tag).c_str();
    bigNumber C2=this->ciphertext.substr(tag+1,this->ciphertext.length()-tag).c_str();
    tag = this->priv_key.find('\n');
    bigNumber p(this->priv_key.substr(0,tag).c_str());
    bigNumber x(this->priv_key.substr(tag+1,this->priv_key.length()-tag).c_str());

    return decrypt(p,x,C1,C2);
}
