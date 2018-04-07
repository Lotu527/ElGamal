#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#include <iostream>

#define BASE 1000000000
#define DIV_ON_ZERO 1

class bigNumber
{
public:
    bigNumber();
    bigNumber(const char* String);
    bigNumber(const bigNumber& RightHandValue);
    bigNumber(long long int RightHandValue);
    ~bigNumber();

    char* GetString();
    char* __str__();
    char* __repr__();
    bool GetNumberFromFile(const char* FileName);
    bool SaveNumberToFile(const char* FileName);
    bool GetNumberFromBinFile(const char* FileName);
    bool SaveNumberInBinFile(const char* FileName);

    bool Odd();
    bigNumber operator=(const bigNumber& RightHandValue);

    bigNumber operator+(const bigNumber& right) const;
    bigNumber operator-() const;
    bigNumber operator-(const bigNumber& right) const;
    bigNumber operator*(const bigNumber& right) const;
    bigNumber operator/(const bigNumber& right) const;
    bigNumber operator%(const bigNumber& right) const;
    bigNumber operator^(const bigNumber& right) const;


    bool operator>(const bigNumber& B);
    bool operator>=(const bigNumber& B);
    bool operator<(const bigNumber& B);
    bool operator<=(const bigNumber& B);
    bool operator==(const bigNumber& B);
    bool operator!=(const bigNumber& B);

    bigNumber operator+(const int& right) const;
    bigNumber operator-(const int& right) const;
    bigNumber operator*(const int& right) const;
    bigNumber operator/(const int& right) const;
    bigNumber operator%(const int& right) const;

    bool operator>(const int& B);
    bool operator>=(const int& B);
    bool operator<(const int& B);
    bool operator<=(const int& B);
    bool operator==(const int& B);
    bool operator!=(const int& B);


    friend std::ostream& operator<<(std::ostream &out, bigNumber A);
    friend std::istream& operator>>(std::istream &is, bigNumber &A);

    bigNumber _Sum_and_Sub(const bigNumber& left, const bigNumber& right) const;
    bigNumber _Multiplication(const bigNumber A, const bigNumber B) const;
    bigNumber _Division(const bigNumber& A, const bigNumber& B, bigNumber &remainder) const;
    unsigned int & operator[](int i);
    unsigned int operator[](int i) const;

private:
    //Т.к оператор new имеет ограничение на максимальный размер массива 0x7fffffff байт поэтому тип у _size - int
    int _size;
    unsigned int* _digits;
    int _sign;


    void _SetSize(int size);
    void _Copy(const bigNumber &rhv);
    void _DelNeedlessZeros();
    long long int _Compare(const bigNumber& B);
    void _ShiftLeft(int s);

    friend bigNumber GenerateRandomLen(int bitLen);
    friend bigNumber GenerateRandomMax(bigNumber max);
};

bigNumber GenerateRandomLen(int bitLen);

bigNumber GenerateRandomMax(bigNumber max);

//bigNumber Pow(const bigNumber& A, const bigNumber& B, bigNumber& modulus);

//void initRandom();

//bool MillerRabinPass(bigNumber a,bigNumber s,bigNumber t,bigNumber n);

//bool MillerRabin(bigNumber n);

//bigNumber GeneratePrime(int bitlen);

#endif // BIGNUMBER_H

