#ifndef TOOL_H
#define TOOL_H
#include "bignumber.h"

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

#endif // TOOL_H
