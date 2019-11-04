//
//  BigNumber.h
//  PPDLab1
//
//  Created by Razvan Manea on 11/4/19.
//  Copyright © 2019 Razvan Manea. All rights reserved.
//
#ifndef BigNumber_h
#define BigNumber_h

#include <stddef.h>
#include <stdexcept>
#include <string>
#define MAX_SIZE 50

uint8_t carries[MAX_SIZE + 1] = {0};

struct BigNumber
{
    uint8_t digits[MAX_SIZE];
    size_t size;
    
    BigNumber()
    {
        size = 0;
    }
    BigNumber(size_t size)
    {
        if (size > MAX_SIZE) throw std::overflow_error("Size too big!");
        this->size = size;
    }
    BigNumber(uint8_t arr[], size_t size)
    {
        if (size > MAX_SIZE) throw std::overflow_error("Size too big!");
        memcpy(digits, arr, size * sizeof(arr[0]));
        this->size = size;
    }
    
    uint8_t& operator[](size_t index)
    {
        return digits[index];
    }
    const uint8_t& operator[](size_t index) const
    {
        return digits[index];
    }
    
    BigNumber MultiplyWithDigit(uint8_t digit) const;
    BigNumber MultiplyWithDigitParallel(uint8_t digit, int tc) const;
    BigNumber MultiplySeq(const BigNumber& other) const;
    
private:
    static void MultiplyRangeWithDigit(uint8_t* arr, uint8_t digit, size_t start, size_t end);
};


#endif /* BigNumber_h */
