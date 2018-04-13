#ifndef TOOL_H
#define TOOL_H
#include "bignumber.h"
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>

using std::ifstream;
using std::ofstream;
//大数幂运算，求A的B次方，modulus是规定的范围，如果结果大于等于它会进行模运算
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
//大数幂运算，求A的B次方
bigNumber Pow(const bigNumber& A,const bigNumber& B){
    bigNumber a(A), b(B), result(1);

    while (b != 0)
    {
        result = result * a;
        b = b - 1;
    }
    return result;
}
//初始化随机种子
void initRandom()
{
    srand(time(NULL));
}

bool MillerRabinPass(bigNumber a,bigNumber s,bigNumber t,bigNumber n){
    bigNumber x = Pow(a,t,n);
    if(x==1)
        return true;
    bigNumber i = 1;
    i = i - 1;
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
    bigNumber s = 1;
    s = s - 1;
    bigNumber a;
    while(t%2==0){
        t=t/2;
        s=s+1;
    }
    for(int i=0;i<20;i++){
        a = 1;
        a = a-1;
        while (a==0) {
            a = GenerateRandomMax(n-4)+2;// 2<= a <= n-2
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
    initRandom();
    bigNumber P = GenerateRandomLen(bitlen);
    //素数测试,采用Miller_Rabin算法，它是目前主流的基于概率的素数测试算法
    while (MillerRabin(P)) {
        P = P + 1;
    }
    return P;
}
//求乘法群Z*_p 的一个本原元
bigNumber GenerateG(bigNumber p)
{
    bigNumber g = 2;
    bigNumber one = 1;
    while ((g*g)%p != one && (g*p)%p !=one) {
        g = GenerateRandomMax(p-1);
    }
    return g;
}
//把字符串存储到文件中
bool SaveFile(const char* filename,std::string str)
{
    ofstream Result_file(filename);
    if (Result_file.fail())
        return false;

    Result_file << str;

    Result_file.close();

    return true;
}
//从文件中读取字符串
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
//把字符串映射为一个数
bigNumber NumberFromChars(char* str,long len)
{
    bigNumber res;
    bigNumber b256 = 1;
    for (int i = 0; i < len; i++)
    {
        unsigned int fi = str[i];
        res = res + b256 * fi;
        b256 = b256 * 256;
    }
    return res;
}
//把字符串映射为一个数
bigNumber NumberFromBinString(std::string str){
    if(str.empty()){
        exit(1);
    }
    return NumberFromChars((char*)str.c_str(),str.length());
}

//把大数逆映射到文本，按二进制格式存入文件
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

//把大数转换为字符串
std::string GetNumber(bigNumber temp){
    bigNumber b256 = 256;
    bigNumber b0 = (long long int)0;
    std::string str= "";
    while (temp != b0)
    {
        bigNumber remainder;
        temp = temp._Division(temp, b256, remainder);
        unsigned char ost = remainder[0];
        str += ost;
    }
    return str;
}

//把字符串转换为大数
bigNumber StringToNumber(std::string str){
    return bigNumber(str.c_str());
}

//把字符串转换为无符号字符数组
unsigned char* GetUnsignChar(std::string str){
    long len = str.length();
    unsigned char* re = new unsigned char[len+1];
    for(long i=0;i<len;i++){
        re[i] = (unsigned char)str[i];
    }
    re[len]='\0';
    return re;
}
//把无符号数组转换为有符号数组
char* GetChar(unsigned char* str,int len){
    char* re = new char[len];
    for(int i=0;i<len;i++){
        re[i] = (char)str[i];
    }
    return re;
}
//费马小定理获取逆元
bigNumber Fermat(bigNumber a,bigNumber p){
    return Pow(a,p-1,p);
}


#endif // TOOL_H
