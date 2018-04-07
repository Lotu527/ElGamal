#ifndef TOOL_H
#define TOOL_H
#include "bignumber.h"
#include <fstream>
#include <iostream>
#include <string>
using std::ifstream;
using std::ofstream;
bigNumber Pow(const bigNumber& A, const bigNumber& B, bigNumber& modulus)
{
    if (modulus <= (long long int) 0)
        return A ^ B;

    bigNumber a(A % modulus), b(B), result(1);

    while (b != 0)
    {
        if (b.Odd())
            result = (result * a) % modulus;
        a = (a * a) % modulus;
        b = b / 2;
    }

    return result;
}
bigNumber Pow(const bigNumber& A,const bigNumber& B){
    bigNumber a(A), b(B), result(1);

    while (b != 0)
    {
        result = result * a;
        b = b - 1;
    }
    return result;
}

void initRandom()
{
    srand(time(NULL));
}

bool MillerRabinPass(bigNumber a,bigNumber s,bigNumber t,bigNumber n){
    bigNumber x = Pow(a,t,n);
    if(x==1)
        return true;
    bigNumber i = (int)(0);
    while (i < s - 1) {
        x = (x*x)%n;
        if(x == n-1)
            return true;
        i = i + 1;
    }
    return x == n-1;
}

bool MillerRabin(bigNumber n){
    bigNumber t = n - 1;
    bigNumber s = (int)(0);
    bigNumber a;
    while(t%2==0){
        t=t/2;
        s=s+1;
    }
    for(int i=0;i<20;i++){
        a=*new bigNumber(int(0));
        while (a==0) {
            a = GenerateRandomMax(n-4)+2;
        }
        if(MillerRabinPass(a,s,t,n)){
            return false;
        }
    }
    return true;
}

bigNumber GeneratePrime(int bitlen)
{
    //初始化时间种子
    bigNumber P = GenerateRandomLen(bitlen);
    //素数测试,采用Miller_Rabin算法，它是目前主流的基于概率的素数测试算法
    while (MillerRabin(P)) {
        P = P + 1;
    }
    return P;
}

bool SaveFile(const char* filename,std::string str)
{
    ofstream Result_file(filename);
    if (Result_file.fail())
        return false;

    Result_file << str;

    Result_file.close();

    return true;
}

char* ReadFromFile(const char* filename)
{
    ifstream Text_file(filename);
    if (Text_file.fail())
        return nullptr;

    Text_file.seekg(0, std::ios::end);
    int SizeOfFile = Text_file.tellg();
    Text_file.seekg(0, std::ios::beg);

    char* string = new char[SizeOfFile+1];
    Text_file.read(string,SizeOfFile);
    string[SizeOfFile]='\0';
    Text_file.close();
    return string;
}

bigNumber NumberFromBinString(std::string str){
    if(str.empty()){
        exit(1);
    }
    int SizeOfFile = str.length();

    bigNumber res;
    bigNumber b256 = 1;
    for (int i = 0; i < SizeOfFile; i++)
    {
        unsigned int fi = str[i];
        res = res + b256 * fi;
        b256 = b256 * 256;
    }
    return res;
}

bool SaveNumberInBinFile(const char* filename,bigNumber temp)
{
    ofstream Result_file(filename, std::ios::binary);
    if (Result_file.fail())
        return false;
    bigNumber b256 = 256;
    bigNumber b0 = (long long int)0;
    while (temp != b0)
    {
        bigNumber remainder;
        temp = temp._Division(temp, b256, remainder);
        unsigned char ost = remainder[0];
        Result_file.write((char*)&ost, 1);
    }

    Result_file.close();
    return true;
}

bigNumber StringToNumber(std::string str){
    return bigNumber(str.c_str());
}




#endif // TOOL_H
