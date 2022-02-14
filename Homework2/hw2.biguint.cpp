#include "hw2.biguint.hpp"

#include <iostream>
#include <cmath>
using namespace std;
BigUInt::BigUInt() : length(1), data(new unsigned char[1]{0}) {}
// 2. (5 points) Initializes the BigUInt to n.
// Allocate data to an array the number of digits.
BigUInt::BigUInt(unsigned int n)
{
    if (n == 0)
    {
        length = 1;
    }
    else
    {
        length = static_cast<int>(std::floor(std::log10(n))) + 1;
    }
    data = new unsigned char[length];

    for (unsigned int i = 0; i < length; ++i)
    {
        data[i] = n % 10;
        n /= 10;
    }
}
// 3. (1 point) Frees space in data.
BigUInt::~BigUInt()
{
    delete[] data;
}
// 4. (1 point) Print the number represented by this BigUInt.
void BigUInt::Print()
{
    for (unsigned int i = 1; i <= length; ++i)
    {
        std::cout << static_cast<unsigned int>(data[length - i]);
    }
    std::cout << std::endl;
}
// 5. (4 points) Set this BigUInt to original value times 10^p.
// Allocate space as neccessary.
void BigUInt::TimesTenPow(unsigned int p)
{
    if (length == 1 && data[0] == 0)
    {
        return;
    }
    unsigned char *new_data = new unsigned char[length + p];
    for (unsigned int i = 0; i < p; ++i)
    {
        new_data[i] = 0;
    }
    for (unsigned int i = 0; i < length; ++i)
    {
        new_data[i + p] = data[i];
    }
    delete[] data;
    data = new_data;
    length += p;
}
// 6. (6 points) Set this BigUInt to original value plus rhs.
// Allocate space as necessary.
BigUInt &BigUInt::operator+=(const BigUInt &rhs)
{
    const unsigned int max = std::max(length, rhs.length);
    const unsigned int min = std::min(length, rhs.length);

    unsigned char *const sum = new unsigned char[max + 1];
    bool carry = 0;
    unsigned int i = 0;
    for (; i < min; ++i)
    {
        const unsigned char add = data[i] + rhs.data[i] + carry;
        if (add > 9)
        {
            sum[i] = add % 10;
            carry = 1;
        }
        else
        {
            sum[i] = add;
            carry = 0;
        }
    }
    // const bool lhs_greater = length > rhs.length;
    if (length > rhs.length)
    {
        for (; i < max; ++i)
        {
            const unsigned char add = data[i] + carry;
            if (add > 9)
            {
                sum[i] = add % 10;
                carry = 1;
            }
            else
            {
                sum[i] = add;
                carry = 0;
            }
        }
    }
    else
    {
        for (; i < max; ++i)
        {
            const unsigned char add = rhs.data[i] + carry;
            if (add > 9)
            {
                sum[i] = add % 10;
                carry = 1;
            }
            else
            {
                sum[i] = add;
                carry = 0;
            }
        }
    }
    sum[max] = carry;

    if (sum[max] == 0)
    {
        unsigned char *const smaller = new unsigned char[max];
        for (unsigned int j = 0; j < max; ++j)
        {
            smaller[j] = sum[j];
        }
        delete[] sum;
        delete[] data;
        data = smaller;
        length = max;
    }
    else
    {
        delete[] data;
        data = sum;
        length = max + 1;
    }

    return *this;
}

ostream &operator<<(ostream &os, const BigUInt &b)
{
    for (unsigned int i = 1; i <= b.length; ++i)
    {
        os << static_cast<unsigned int>(b.data[b.length - i]);
    }
    return os;
}