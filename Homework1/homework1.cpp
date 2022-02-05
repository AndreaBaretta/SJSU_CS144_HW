#include <iostream>
using namespace std;

class Rational {
private:
    int numerator;
    int denominator;
public:
    Rational(int numerator, int denominator) : numerator(numerator), denominator(denominator) {}
    Rational() : numerator(0), denominator(1) {}
    Rational(const Rational& r) : numerator(r.getNumerator()), denominator(r.getDenominator()) {}

    int getNumerator() const {
        return numerator;
    }

    void setNumerator(int numerator) {
        this->numerator = numerator;
    }

    int getDenominator() const {
        return denominator;
    }

    bool setDenominator(int denominator) {
        if (denominator == 0) {
            return false;
        } else {
            this->denominator = denominator;
            return true;
        }
    }

    void Print() const {
        std::cout << numerator << "/" << denominator << std::endl;
    }

    void Reduce() {
        if (numerator <= 1) { return; }
        for (int i = 2; i <= numerator; ++i) {
            if (numerator % i == 0 && denominator % i == 0) {
                numerator /= i;
                denominator /= i;
                Reduce();
                return;
            }
        }
    }

    Rational& operator+=(const Rational& rhs) {
        numerator = numerator*rhs.getDenominator() + rhs.getNumerator()*denominator;
        denominator *= rhs.getDenominator();
        return *this;
    }
};

Rational operator*(const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.getNumerator()*rhs.getNumerator(), lhs.getDenominator()*rhs.getDenominator());
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    int numerator = lhs.getNumerator()*rhs.getDenominator() + rhs.getNumerator()*lhs.getDenominator();
    int denominator = lhs.getDenominator() * rhs.getDenominator();
    return Rational(numerator, denominator);
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    Rational l = Rational(lhs);
    Rational r = Rational(rhs);
    l.Reduce();
    r.Reduce();
    if (l.getNumerator() == r.getNumerator() && l.getDenominator() == r.getDenominator()) {
        return true;
    } else {
        return false;
    }
}

int main() {
    Rational r1;
    Rational r2(12,36);
    r1.Print();
    r2.Print();
    r1.Reduce();
    r2.Reduce();
    
    r1.Print();
    r2.Print();
    Rational r3(1,2);
    Rational r4(2,3);
    r4 += r3;
    r4.Print();
    Rational r5(3,8);
    Rational r6(2,5);
    Rational r7;
    r7 = r5 + r6;
    r7.Print();
    
    r7.Reduce();
    r7.Print();
    Rational r8;
    r8 = r5 * r6;
    r8.Print();
    r8.Reduce();
    r8.Print();
    
    Rational r9(36, 12);
    Rational r10(12, 4);
    if (r9 == r10) {
        cout << "equal" << endl;
    } else {
        cout << "not equal" << endl;
    }
    return 0;
}
/*
Results
0/1
12/36
0/1
1/3
7/6
31/40
31/40
6/40
3/20
equal
*/