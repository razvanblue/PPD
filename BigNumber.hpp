//
//  BigNumber.hpp
//  PPDLab1
//
//  Created by Razvan Manea on 11/4/19.
//  Copyright © 2019 Razvan Manea. All rights reserved.
//
#ifndef BigNumber_hpp
#define BigNumber_hpp

#define MAX_SIZE 50

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
    
    BigNumber MultiplyWithDigit(uint8_t digit)
    {
        if(digit > 9) throw std::out_of_range(std::to_string(digit) + " nu este cifra!");
        
        BigNumber ret(size + 1);
        
        uint8_t carry = 0;
        for(int i = 0; i < size; i++)
        {
            ret[i] = (digits[i] * digit + carry) % 10;
            carry = (digits[i] * digit + carry) / 10;
        }
        if (carry == 0) ret.size = size;
        else ret[size] = carry;
        
        return ret;
    }
    
    BigNumber MultiplySeq(const BigNumber& other)
    {
        
    }
};


#endif /* BigNumber_hpp */
