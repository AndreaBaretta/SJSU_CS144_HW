#include "hw3.biguint.hpp"

#include <cmath>
#include <iostream>

// HOMEWORK 2 METHODS

BigUInt::BigUInt() : length(1), data(new unsigned char[1]{0}) {}

BigUInt::BigUInt(unsigned int n) {
    if (n == 0) {
        length = 1;
    } else {
        length = static_cast<int>(std::floor(std::log10(n))) + 1;
    }
    data = new unsigned char[length];

    for (unsigned int i = 0; i < length; ++i) {
        data[i] = n % 10;
        n /= 10;
    }
}

BigUInt::~BigUInt() {
    delete[] data;
}

void BigUInt::Print() {
    for (unsigned int i = 1; i <= length; ++i) {
        std::cout << static_cast<unsigned int>(data[length - i]);
    }
    std::cout << std::endl;
}

void BigUInt::TimesTenPow(unsigned int p) {
    if (length == 1 && data[0] == 0) {
        return;
    }
    unsigned char* new_data = new unsigned char[length + p];
    for (unsigned int i = 0; i < p; ++i) {
        new_data[i] = 0;
    }
    for (unsigned int i = 0; i < length; ++i) {
        new_data[i + p] = data[i];
    }
    delete[] data;
    data = new_data;
    length += p;
}

BigUInt& BigUInt::operator+=(const BigUInt& rhs) {
    const unsigned int max = std::max(length, rhs.length);
    const unsigned int min = std::min(length, rhs.length);

    unsigned char* const sum = new unsigned char[max + 1];
    bool carry = 0;
    unsigned int i = 0;
    for (; i < min; ++i) {
        const unsigned char add = data[i] + rhs.data[i] + carry;
        if (add > 9) {
            sum[i] = add % 10;
            carry = 1;
        } else {
            sum[i] = add;
            carry = 0;
        }
    }
    if (length > rhs.length) {
        for (; i < max; ++i) {
            const unsigned char add = data[i] + carry;
            if (add > 9) {
                sum[i] = add % 10;
                carry = 1;
            } else {
                sum[i] = add;
                carry = 0;
            }
        }
    } else {
        for (; i < max; ++i) {
            const unsigned char add = rhs.data[i] + carry;
            if (add > 9) {
                sum[i] = add % 10;
                carry = 1;
            } else {
                sum[i] = add;
                carry = 0;
            }
        }
    }
    sum[max] = carry;

    if (sum[max] == 0) {
        unsigned char* const smaller = new unsigned char[max];
        for (unsigned int j = 0; j < max; ++j) {
            smaller[j] = sum[j];
        }
        delete[] sum;
        delete[] data;
        data = smaller;
        length = max;
    } else {
        delete[] data;
        data = sum;
        length = max + 1;
    }

    return *this;
}

ostream& operator<<(ostream& os, const BigUInt& b) {
    for (unsigned int i = 1; i <= b.length; ++i) {
        os << static_cast<unsigned int>(b.data[b.length - i]);
    }
    return os;
}

// HOMEWORK 3 METHODS

// (a) (2 points) Write copy constructor such that this->data is
// pointing to different location as b.data.
BigUInt::BigUInt(const BigUInt& b) : length(b.length), data(new unsigned char[b.length]) {
    for (size_t i = 0; i < length; ++i) {
        data[i] = b.data[i];
    }
}

// (b) (2 points) Write assignment operator such that this->data is
// pointing to different location as b.data.
BigUInt& BigUInt::operator=(const BigUInt& b) {
    length = b.length;
    delete[] data;
    data = new unsigned char[length];
    for (size_t i = 0; i < length; ++i) {
        data[i] = b.data[i];
    }
    return *this;
}

// (c) (3 points) Write the += operator such that new value is equal
// to old value + i.
BigUInt& BigUInt::operator+=(unsigned int i) {
    return (*this) += BigUInt(i);
}

// (d) (2 points) Implement SetDigit. This function sets the digit at
// position i. It is set to d. Check that the input i is valid.
// Check also that the input d is valid. If either input is invalid,
// this function returns without doing anything.
void BigUInt::SetDigit(int i, int d) {
    if (i < 0 || i >= length) {
        return;
    }
    if (d < 0 || d > 0) {
        return;
    }
    data[i] = d;
}

// (e) (3 points) Return a string representing this unsigned integer.
// For example, if the integer is 4892, then return a string "4892".
string BigUInt::ToString() {
    string str = string();
    for (size_t i = 1; i <= length; ++i) {
        str += to_string((unsigned int)data[length - i]);
    }
    return str;
}

// (f) (4 points) Non-member friend function. Returns true of the value of
// lhs is greater than rhs, returns false otherwise.
bool operator>(const BigUInt& lhs, const BigUInt& rhs) {
    if (lhs.length > rhs.length) {
        return true;
    } else if (lhs.length < rhs.length) {
        return false;
    } else {
        for (size_t i = lhs.length; i > 0; --i) {
            if (lhs.data[i - 1] != rhs.data[i - 1]) return lhs.data[i - 1] > rhs.data[i - 1];
        }
        return false;
    }
}

// (g) (4 points) Write a non-member function + that takes a BigUInt and an
// unsigned int, and returns that BigUInt that represents their sum.
BigUInt operator+(const BigUInt& b, unsigned int i) {
    BigUInt b_copy(b);
    return BigUInt(b_copy += i);
}