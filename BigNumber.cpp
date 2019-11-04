//
//  BigNumber.cpp
//  PPDLab1
//
//  Created by Razvan Manea - (p) on 11/4/19.
//  Copyright © 2019 Razvan Manea - (p). All rights reserved.
//

#include "BigNumber.h"
#include <thread>

BigNumber BigNumber::MultiplyWithDigit(uint8_t digit) const
{
    if(digit > 9) throw std::out_of_range(std::to_string(digit) + " nu este cifra!");
    
    BigNumber ret(size + 1);
    
    uint8_t carry = 0;
    for(size_t i = 0; i < size; i++)
    {
        ret[i] = (digits[i] * digit + carry) % 10;
        carry = (digits[i] * digit + carry) / 10;
    }
    if (carry == 0) ret.size = size;
    else ret[size] = carry;
    
    return ret;
}

void BigNumber::MultiplyRangeWithDigit(uint8_t* arr, uint8_t digit, size_t start, size_t end)
{
    uint8_t carry = 0;
    for (size_t i = start; i < end; i++)
    {
        arr[i] = (arr[i] * digit + carry) % 10;
        carry = (arr[i] * digit + carry) / 10;
    }
    carries[end] = carry;
}

BigNumber BigNumber::MultiplyWithDigitParallel(uint8_t digit, int tc) const
{
    if(digit > 9) throw std::out_of_range(std::to_string(digit) + " nu este cifra!");
    
    size_t tlen = size / tc;                // length of a thread's working range
    int remainder = size % tc;              // remainder to be distributed
    BigNumber ret(size + 1);
    std::thread threads[tc];
    
    //Create threads
    size_t i, start = 0;
    size_t end = (remainder == 0) ? tlen : tlen + 1;
    for (i = 0; i < remainder; i++)
    {
        threads[i] = std::thread(MultiplyRangeWithDigit, ret.digits, digit, start, end);
        start += tlen + 1;
        end += tlen + 1;
    }
    for (; i < tc; i++)
    {
        threads[i] = std::thread(MultiplyRangeWithDigit, ret.digits, digit, start, end);
        start += tlen;
        end += tlen;
    }
    
    for (i = 0; i < tc; i++)
        threads[i].join();
    //TODO: Merge carries
    
    if (ret[] == 0) ret.size = size;
    else ret[size] = carry;
    
    return ret;
}

BigNumber BigNumber::MultiplySeq(const BigNumber& other) const
{
    bool comp = (size < other.size);
    size_t minlen = comp ? size : other.size;
    const BigNumber& bigger = comp ? other : *this;
    const BigNumber& smaller = comp ? *this : other;
    
    BigNumber ret;
    
    for(int i = 0; i < minlen; i++)
    {
        ret = ret.AddSeq(bigger.MultiplyWithDigit(smaller[i]));
    }
    return ret;
}

