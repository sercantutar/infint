/*
 * InfInt - Arbitrary-Precision Integer Arithmetic Library
 * Copyright (C) 2013 Sercan Tutar
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; either version 2.1 of the License, or (at your option)
 * any later version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 *
 * USAGE:
 *   It is pretty straight forward to use the library. Just create an instance of
 *   InfInt class and start using it.
 *
 *   Useful methods:
 *      intSqrt:        integer square root operation
 *      digitAt:        returns digit at index
 *      numberOfDigits: returns number of digits
 *      size:           returns size in bytes
 *      toString:       converts it to a string
 *
 *   There are also conversion methods which allow conversion to primitive types:
 *   toInt, toLong, toLongLong, toUnsignedInt, toUnsignedLong, toUnsignedLongLong.
 *
 *   You may define INFINT_USE_EXCEPTIONS and library methods will start raising
 *   InfIntException in case of error instead of writing error messages using
 *   std::cerr.
 *
 *   See ReadMe.txt for more info.
 *
 *
 * Happy profiling!
 *
 */

#ifndef INFINT_H_
#define INFINT_H_

#include <iostream>
#include <deque>
#include <sstream>
#include <iomanip>

#include <limits.h>
#include <stdlib.h>

#ifdef WIN32
#define LONG_LONG_MIN LLONG_MIN
#define LONG_LONG_MAX LLONG_MAX
#define ULONG_LONG_MIN ULLONG_MIN
#define ULONG_LONG_MAX ULLONG_MAX
#endif

//#define INFINT_USE_EXCEPTIONS
//#define INFINT_USE_SHORT_BASE

#ifdef INFINT_USE_EXCEPTIONS
#include <exception>
#endif

//inline bool check_pos(int n)
//{
//	return n >= 0;
//}
//inline bool check_neg(int n)
//{
//	return n <= 0;
//}

#ifdef INFINT_USE_SHORT_BASE // uses 10^4 (short) as the base
typedef short ELEM_TYPE;
typedef int PRODUCT_TYPE;
static const ELEM_TYPE BASE = 10000;
static const ELEM_TYPE UPPER_BOUND = 9999;
static const ELEM_TYPE DIGIT_COUNT = 4;
static const int powersOfTen[] = { 1, 10, 100, 1000};
#else // uses 10^9 (int) as the base
typedef int ELEM_TYPE;
typedef long long PRODUCT_TYPE;
static const ELEM_TYPE BASE = 1000000000;
static const ELEM_TYPE UPPER_BOUND = 999999999;
static const ELEM_TYPE DIGIT_COUNT = 9;
static const int powersOfTen[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000 };
#endif

#ifdef INFINT_USE_EXCEPTIONS
class InfIntException: public std::exception
{
public:
    InfIntException(const std::string& txt) throw ();
    ~InfIntException() throw ();
    const char* what() const throw ();
private:
    std::string txt;
};

InfIntException::InfIntException(const std::string& txt) throw () :
std::exception(), txt(txt)
{
}

InfIntException::~InfIntException() throw ()
{
}

const char* InfIntException::what() const throw ()
{
    return txt.c_str();
}
#endif

class InfInt
{
    friend std::ostream& operator<<(std::ostream &s, const InfInt &n);
    friend std::istream& operator>>(std::istream &s, InfInt &val);
    
public:
    /* some constants */
    static const InfInt zero;
    static const InfInt one;
    static const InfInt two;
    
    /* constructors */
    InfInt();
    InfInt(const char* c);
    InfInt(const std::string& s);
    InfInt(int l);
    InfInt(long l);
    InfInt(long long l);
    InfInt(unsigned int l);
    InfInt(unsigned long l);
    InfInt(unsigned long long l);
    
    /* assignment operators */
    const InfInt& operator=(const char* c);
    const InfInt& operator=(const std::string& s);
    const InfInt& operator=(int l);
    const InfInt& operator=(long l);
    const InfInt& operator=(long long l);
    const InfInt& operator=(unsigned int l);
    const InfInt& operator=(unsigned long l);
    const InfInt& operator=(unsigned long long l);
    
    /* unary increment/decrement operators */
    const InfInt& operator++();
    const InfInt& operator--();
    InfInt operator++(int);
    InfInt operator--(int);
    
    /* operational assignments */
    const InfInt& operator+=(const InfInt& rhs);
    const InfInt& operator-=(const InfInt& rhs);
    const InfInt& operator*=(const InfInt& rhs);
    const InfInt& operator/=(const InfInt& rhs); // throw
    const InfInt& operator%=(const InfInt& rhs); // throw
    const InfInt& operator*=(ELEM_TYPE rhs);
    
    /* operations */
    InfInt operator-() const;
    InfInt operator+(const InfInt& rhs) const;
    InfInt operator-(const InfInt& rhs) const;
    InfInt operator*(const InfInt& rhs) const;
    InfInt operator/(const InfInt& rhs) const; // throw
    InfInt operator%(const InfInt& rhs) const; // throw
    InfInt operator*(ELEM_TYPE rhs) const;
    
    /* relational operations */
    bool operator==(const InfInt& rhs) const;
    bool operator!=(const InfInt& rhs) const;
    bool operator<(const InfInt& rhs) const;
    bool operator<=(const InfInt& rhs) const;
    bool operator>(const InfInt& rhs) const;
    bool operator>=(const InfInt& rhs) const;
    
    /* integer square root */
    InfInt intSqrt() const; // throw
    
    /* digit operations */
    char digitAt(size_t i) const; // throw
    size_t numberOfDigits() const;
    
    /* size in bytes */
    size_t size() const;
    
    /* string conversion */
    std::string toString() const;
    
    /* conversion to primitive types */
    int toInt() const; // throw
    long toLong() const; // throw
    long long toLongLong() const; // throw
    unsigned int toUnsignedInt() const; // throw
    unsigned long toUnsignedLong() const; // throw
    unsigned long long toUnsignedLongLong() const; // throw
    
private:
    static ELEM_TYPE dInR(const InfInt& R, const InfInt& D);
    static void multiplyByDigit(ELEM_TYPE factor, std::deque<ELEM_TYPE>& val);
    static void divide(PRODUCT_TYPE numer, ELEM_TYPE denom, PRODUCT_TYPE& quot, ELEM_TYPE& rem);
    static void ensureIndex(size_t s, std::deque<ELEM_TYPE>& val);
    
    void correct(bool justCheckLeadingZeros = false, bool hasValidSign = false);
    void fromString(const std::string& s);
    void optimizeSqrtSearchBounds(InfInt& lo, InfInt& hi) const;
    void truncateToBase();
    void equalizeSigns();
    bool allPositive();
    void removeLeadingZeros();
    
    std::deque<ELEM_TYPE> val; // number with base FACTOR
    bool pos; // true if number is positive
};

const InfInt InfInt::zero = 0;
const InfInt InfInt::one = 1;
const InfInt InfInt::two = 2;

inline InfInt::InfInt() : pos(true)
{
    val.push_back((ELEM_TYPE) 0);
}

inline InfInt::InfInt(const char* c)
{
    fromString(c);
}

inline InfInt::InfInt(const std::string& s)
{
    fromString(s);
}

inline InfInt::InfInt(int l) : pos(l >= 0)
{
    if (!pos)
    {
        l = -l;
    }
    do
    {
        div_t dt = div(l, BASE);
        val.push_back((ELEM_TYPE) dt.rem);
        l = dt.quot;
    } while (l > 0);
}

inline InfInt::InfInt(long l) : pos(l >= 0)
{
    if (!pos)
    {
        l = -l;
    }
    do
    {
        ldiv_t dt = ldiv(l, BASE);
        val.push_back((ELEM_TYPE) dt.rem);
        l = dt.quot;
    } while (l > 0);
}

inline InfInt::InfInt(long long l) : pos(l >= 0)
{
    if (!pos)
    {
        l = -l;
    }
    do
    {
#ifndef WIN32
        lldiv_t dt = lldiv(l, BASE);
        val.push_back((ELEM_TYPE) dt.rem);
        l = dt.quot;
#else
        val.push_back((ELEM_TYPE) (l % BASE));
        l = l / BASE;
#endif
    } while (l > 0);
}

inline InfInt::InfInt(unsigned int l) : pos(true)
{
    do
    {
        val.push_back((ELEM_TYPE) (l % BASE));
        l = l / BASE;
    } while (l > 0);
}

inline InfInt::InfInt(unsigned long l) : pos(true)
{
    do
    {
        val.push_back((ELEM_TYPE) (l % BASE));
        l = l / BASE;
    } while (l > 0);
}

inline InfInt::InfInt(unsigned long long l) : pos(true)
{
    do
    {
        val.push_back((ELEM_TYPE) (l % BASE));
        l = l / BASE;
    } while (l > 0);
}

inline const InfInt& InfInt::operator=(const char* c)
{
    fromString(c);
    return *this;
}

inline const InfInt& InfInt::operator=(const std::string& s)
{
    fromString(s);
    return *this;
}

inline const InfInt& InfInt::operator=(int l)
{
    pos = l >= 0;
    val.clear();
    if (!pos)
    {
        l = -l;
    }
    do
    {
        div_t dt = div(l, BASE);
        val.push_back((ELEM_TYPE) dt.rem);
        l = dt.quot;
    } while (l > 0);
    return *this;
}

inline const InfInt& InfInt::operator=(long l)
{
    pos = l >= 0;
    val.clear();
    if (!pos)
    {
        l = -l;
    }
    do
    {
        ldiv_t dt = ldiv(l, BASE);
        val.push_back((ELEM_TYPE) dt.rem);
        l = dt.quot;
    } while (l > 0);
    return *this;
}

inline const InfInt& InfInt::operator=(long long l)
{
    pos = l >= 0;
    val.clear();
    if (!pos)
    {
        l = -l;
    }
    do
    {
#ifndef WIN32
        lldiv_t dt = lldiv(l, BASE);
        val.push_back((ELEM_TYPE) dt.rem);
        l = dt.quot;
#else
        val.push_back((ELEM_TYPE) (l % BASE));
        l = l / BASE;
#endif
    } while (l > 0);
    return *this;
}

inline const InfInt& InfInt::operator=(unsigned int l)
{
    pos = true;
    val.clear();
    do
    {
        val.push_back((ELEM_TYPE) (l % BASE));
        l = l / BASE;
    } while (l > 0);
    return *this;
}

inline const InfInt& InfInt::operator=(unsigned long l)
{
    pos = true;
    val.clear();
    do
    {
        val.push_back((ELEM_TYPE) (l % BASE));
        l = l / BASE;
    } while (l > 0);
    return *this;
}

inline const InfInt& InfInt::operator=(unsigned long long l)
{
    pos = true;
    val.clear();
    do
    {
        val.push_back((ELEM_TYPE) (l % BASE));
        l = l / BASE;
    } while (l > 0);
    return *this;
}

inline const InfInt& InfInt::operator++()
{
    val[0] += (pos ? 1 : -1);
    this->correct(false, true);
    return *this;
}

inline const InfInt& InfInt::operator--()
{
    val[0] -= (pos ? 1 : -1);
    this->correct(false, true);
    return *this;
}

inline InfInt InfInt::operator++(int)
{
    InfInt result = *this;
    val[0] += (pos ? 1 : -1);
    this->correct(false, true);
    return result;
}

inline InfInt InfInt::operator--(int)
{
    InfInt result = *this;
    val[0] -= (pos ? 1 : -1);
    this->correct(false, true);
    return result;
}

inline const InfInt& InfInt::operator+=(const InfInt& rhs)
{
    for (size_t i = 0; i < val.size() || i < rhs.val.size(); ++i)
    {
        if (i >= val.size())
        {
            val.push_back(i < rhs.val.size() ? (rhs.pos ? rhs.val[i] : -rhs.val[i]) : 0);
        }
        else
        {
            val[i] = (pos ? val[i] : -val[i]) + (i < rhs.val.size() ? (rhs.pos ? rhs.val[i] : -rhs.val[i]) : 0);
        }
    }
    correct();
    return *this;
}

inline const InfInt& InfInt::operator-=(const InfInt& rhs)
{
    for (size_t i = 0; i < val.size() || i < rhs.val.size(); ++i)
    {
        if (i >= val.size())
        {
            val.push_back(i < rhs.val.size() ? (rhs.pos ? -rhs.val[i] : rhs.val[i]) : 0);
        }
        else
        {
            val[i] = (pos ? val[i] : -val[i]) - (i < rhs.val.size() ? (rhs.pos ? rhs.val[i] : -rhs.val[i]) : 0);
        }
    }
    correct();
    return *this;
}

inline const InfInt& InfInt::operator*=(const InfInt& rhs)
{
    // TODO: optimize (do not use operator*)
    *this = *this * rhs;
    return *this;
}

inline const InfInt& InfInt::operator/=(const InfInt& rhs)
{
    if (rhs == zero)
    {
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("division by zero");
#else
        std::cerr << "Division by zero!" << std::endl;
        return *this;
#endif
    }
    InfInt R, D = (rhs.pos ? rhs : -rhs), N = (pos ? *this : -*this);
    bool oldpos = pos;
    val.clear();
    for (int i = (int) N.val.size() - 1; i >= 0; --i)
    {
        R.val.push_front((ELEM_TYPE) 0);
        R.val[0] = N.val[i];
        R.correct(true);
        ELEM_TYPE cnt = dInR(R, D);
        R -= D * cnt;
        ensureIndex(i, val);
        val[i] += cnt;
    }
    correct();
    pos = (val.size() == 1 && val[0] == 0) ? true : (oldpos == rhs.pos);
    return *this;
}

inline const InfInt& InfInt::operator%=(const InfInt& rhs)
{
    if (rhs == zero)
    {
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("division by zero");
#else
        std::cerr << "Division by zero!" << std::endl;
        return zero;
#endif
    }
    InfInt D = (rhs.pos ? rhs : -rhs), N = (pos ? *this : -*this);
    bool oldpos = pos;
    val.clear();
    for (int i = (int) N.val.size() - 1; i >= 0; --i)
    {
        val.push_front((ELEM_TYPE) 0);
        val[0] = N.val[i];
        correct(true);
        *this -= D * dInR(*this, D);
    }
    correct();
    pos = (val.size() == 1 && val[0] == 0) ? true : oldpos;
    return *this;
}

inline const InfInt& InfInt::operator*=(ELEM_TYPE rhs)
{
    ELEM_TYPE factor = rhs < 0 ? -rhs : rhs;
    bool oldpos = pos;
    multiplyByDigit(factor, val);
    correct();
    pos = (val.size() == 1 && val[0] == 0) ? true : (oldpos == (rhs >= 0));
    return *this;
}

inline InfInt InfInt::operator-() const
{
    InfInt result = *this;
    result.pos = !pos;
    return result;
}

inline InfInt InfInt::operator+(const InfInt& rhs) const
{
    InfInt result;
    result.val.clear();
    for (size_t i = 0; i < val.size() || i < rhs.val.size(); ++i)
    {
        result.val.push_back((i < val.size() ? (pos ? val[i] : -val[i]) : 0) + (i < rhs.val.size() ? (rhs.pos ? rhs.val[i] : -rhs.val[i]) : 0));
    }
    result.correct();
    return result;
}

inline InfInt InfInt::operator-(const InfInt& rhs) const
{
    InfInt result;
    result.val.clear();
    for (size_t i = 0; i < val.size() || i < rhs.val.size(); ++i)
    {
        result.val.push_back((i < val.size() ? (pos ? val[i] : -val[i]) : 0) - (i < rhs.val.size() ? (rhs.pos ? rhs.val[i] : -rhs.val[i]) : 0));
    }
    result.correct();
    return result;
}

inline InfInt InfInt::operator*(const InfInt& rhs) const
{
    InfInt result;
    result.val.clear();
    PRODUCT_TYPE carry = 0;
    size_t digit = 0;
    for (;; ++digit)
    {
        ensureIndex(digit, result.val);
        divide(carry, BASE, carry, result.val[digit]);
        //result.val[digit] = (ELEM_TYPE) (carry % BASE);
        //carry /= BASE;
        bool found = false;
        for (size_t i = 0; i < val.size() && i <= digit; ++i)
        {
            size_t j = digit - i;
            if (j < rhs.val.size())
            {
                PRODUCT_TYPE pval = result.val[digit] + val[i] * (PRODUCT_TYPE) rhs.val[j];
                if (pval >= BASE || pval <= -BASE)
                {
                    PRODUCT_TYPE quot;
                    ELEM_TYPE rem;
                    divide(pval, BASE, quot, rem);
                    carry += quot;
                    pval = rem;
                    //carry += pval / BASE;
                    //pval %= BASE;
                }
                result.val[digit] = (ELEM_TYPE) pval;
                found = true;
            }
        }
        if (!found)
        {
            break;
        }
    }
    for (; carry > 0; ++digit)
    {
        ensureIndex(digit, result.val);
        divide(carry, BASE, carry, result.val[digit]);
        //result.val[digit] = (ELEM_TYPE) (carry % BASE);
        //carry /= BASE;
    }
    result.correct();
    result.pos = (result.val.size() == 1 && result.val[0] == 0) ? true : (pos == rhs.pos);
    return result;
}

inline InfInt InfInt::operator/(const InfInt& rhs) const
{
    if (rhs == zero)
    {
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("division by zero");
#else
        std::cerr << "Division by zero!" << std::endl;
        return zero;
#endif
    }
    InfInt Q, R, D = (rhs.pos ? rhs : -rhs), N = (pos ? *this : -*this);
    for (int i = (int) N.val.size() - 1; i >= 0; --i)
    {
        R.val.push_front((ELEM_TYPE) 0);
        R.val[0] = N.val[i];
        R.correct(true);
        ELEM_TYPE cnt = dInR(R, D);
        R -= D * cnt;
        ensureIndex(i, Q.val);
        Q.val[i] += cnt;
    }
    Q.correct();
    Q.pos = (Q.val.size() == 1 && Q.val[0] == 0) ? true : (pos == rhs.pos);
    return Q;
}

inline InfInt InfInt::operator%(const InfInt& rhs) const
{
    if (rhs == zero)
    {
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("division by zero");
#else
        std::cerr << "Division by zero!" << std::endl;
        return zero;
#endif
    }
    InfInt R, D = (rhs.pos ? rhs : -rhs), N = (pos ? *this : -*this);
    for (int i = (int) N.val.size() - 1; i >= 0; --i)
    {
        R.val.push_front((ELEM_TYPE) 0);
        R.val[0] = N.val[i];
        R.correct(true);
        R -= D * dInR(R, D);
    }
    R.correct();
    R.pos = (R.val.size() == 1 && R.val[0] == 0) ? true : pos;
    return R;
}

inline InfInt InfInt::operator*(ELEM_TYPE rhs) const
{
    InfInt result = *this;
    ELEM_TYPE factor = rhs < 0 ? -rhs : rhs;
    multiplyByDigit(factor, result.val);
    result.correct();
    result.pos = (result.val.size() == 1 && result.val[0] == 0) ? true : (pos == (rhs >= 0));
    return result;
}

/* relational operations */
inline bool InfInt::operator==(const InfInt& rhs) const
{
    if (pos != rhs.pos || val.size() != rhs.val.size())
    {
        return false;
    }
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        if (val[i] != rhs.val[i])
        {
            return false;
        }
    }
    return true;
}

inline bool InfInt::operator!=(const InfInt& rhs) const
{
    if (pos != rhs.pos || val.size() != rhs.val.size())
    {
        return true;
    }
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        if (val[i] != rhs.val[i])
        {
            return true;
        }
    }
    return false;
}

inline bool InfInt::operator<(const InfInt& rhs) const
{
    if (pos && !rhs.pos)
    {
        return false;
    }
    if (!pos && rhs.pos)
    {
        return true;
    }
    if (val.size() > rhs.val.size())
    {
        return pos ? false : true;
    }
    if (val.size() < rhs.val.size())
    {
        return pos ? true : false;
    }
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        if (val[i] < rhs.val[i])
        {
            return pos ? true : false;
        }
        if (val[i] > rhs.val[i])
        {
            return pos ? false : true;
        }
    }
    return false;
}

inline bool InfInt::operator<=(const InfInt& rhs) const
{
    if (pos && !rhs.pos)
    {
        return false;
    }
    if (!pos && rhs.pos)
    {
        return true;
    }
    if (val.size() > rhs.val.size())
    {
        return pos ? false : true;
    }
    if (val.size() < rhs.val.size())
    {
        return pos ? true : false;
    }
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        if (val[i] < rhs.val[i])
        {
            return pos ? true : false;
        }
        if (val[i] > rhs.val[i])
        {
            return pos ? false : true;
        }
    }
    return true;
}

inline bool InfInt::operator>(const InfInt& rhs) const
{
    if (pos && !rhs.pos)
    {
        return true;
    }
    if (!pos && rhs.pos)
    {
        return false;
    }
    if (val.size() > rhs.val.size())
    {
        return pos ? true : false;
    }
    if (val.size() < rhs.val.size())
    {
        return pos ? false : true;
    }
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        if (val[i] < rhs.val[i])
        {
            return pos ? false : true;
        }
        if (val[i] > rhs.val[i])
        {
            return pos ? true : false;
        }
    }
    return false;
}

inline bool InfInt::operator>=(const InfInt& rhs) const
{
    if (pos && !rhs.pos)
    {
        return true;
    }
    if (!pos && rhs.pos)
    {
        return false;
    }
    if (val.size() > rhs.val.size())
    {
        return pos ? true : false;
    }
    if (val.size() < rhs.val.size())
    {
        return pos ? false : true;
    }
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        if (val[i] < rhs.val[i])
        {
            return pos ? false : true;
        }
        if (val[i] > rhs.val[i])
        {
            return pos ? true : false;
        }
    }
    return true;
}

inline void InfInt::optimizeSqrtSearchBounds(InfInt& lo, InfInt& hi) const
{
    InfInt hdn = one;
    for (int i = (int) this->numberOfDigits() / 2; i >= 2; --i)
    {
        hdn *= 10;
    }
    if (lo < hdn)
    {
        lo = hdn;
    }
    hdn *= 100;
    if (hi > hdn)
    {
        hi = hdn;
    }
}

inline InfInt InfInt::intSqrt() const
{
    if (*this < zero)
    {
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("intSqrt called for negative integer");
#else
        std::cerr << "intSqrt called for negative integer: " << *this << std::endl;
        return zero;
#endif
    }
    InfInt hi = *this / two, lo = zero, mid, mid2;
    optimizeSqrtSearchBounds(lo, hi);
    do
    {
        mid = (hi + lo) / two; // 8 factor
        mid2 = mid * mid; // 1 factor
        if (mid2 == *this)
        {
            lo = mid;
            break;
        }
        else if (mid2 < *this)
        {
            lo = mid;
        }
        else
        {
            hi = mid;
        }
    } while (lo < hi - one && mid2 != *this);
    return lo;
}

inline char InfInt::digitAt(size_t i) const
{
    if (numberOfDigits() <= i)
    {
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("invalid digit index");
#else
        std::cerr << "Invalid digit index: " << i << std::endl;
        return -1;
#endif
    }
    return (val[i / DIGIT_COUNT] / powersOfTen[i % DIGIT_COUNT]) % 10;
}

inline size_t InfInt::numberOfDigits() const
{
    return (val.size() - 1) * DIGIT_COUNT
#ifdef INFINT_USE_SHORT_BASE
    + (val.back() > 999 ? 4 : (val.back() > 99 ? 3 : (val.back() > 9 ? 2 : 1)));
#else
    + (val.back() > 99999999 ? 9 : (val.back() > 9999999 ? 8 : (val.back() > 999999 ? 7 : (val.back() > 99999 ? 6 :
                                                                                           (val.back() > 9999 ? 5 : (val.back() > 999 ? 4 : (val.back() > 99 ? 3 : (val.back() > 9 ? 2 : 1))))))));
#endif
}

inline std::string InfInt::toString() const
{
    std::ostringstream oss;
    oss << *this;
    return oss.str();
}

inline size_t InfInt::size() const
{
    return val.size() * sizeof(ELEM_TYPE) + sizeof(bool);
}

inline int InfInt::toInt() const
{
    if (*this > INT_MAX || *this < INT_MIN)
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("out of bounds");
#else
    std::cerr << "Out of INT bounds: " << *this << std::endl;
#endif
    int result = 0;
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        result = result * BASE + val[i];
    }
    return pos ? result : -result;
}

inline long InfInt::toLong() const
{
    if (*this > LONG_MAX || *this < LONG_MIN)
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("out of bounds");
#else
    std::cerr << "Out of LONG bounds: " << *this << std::endl;
#endif
    long result = 0;
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        result = result * BASE + val[i];
    }
    return pos ? result : -result;
}

inline long long InfInt::toLongLong() const
{
    if (*this > LONG_LONG_MAX || *this < LONG_LONG_MIN)
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("out of bounds");
#else
    std::cerr << "Out of LLONG bounds: " << *this << std::endl;
#endif
    long long result = 0;
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        result = result * BASE + val[i];
    }
    return pos ? result : -result;
}

inline unsigned int InfInt::toUnsignedInt() const
{
    if (!pos || *this > UINT_MAX)
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("out of bounds");
#else
    std::cerr << "Out of UINT bounds: " << *this << std::endl;
#endif
    unsigned int result = 0;
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        result = result * BASE + val[i];
    }
    return result;
}

inline unsigned long InfInt::toUnsignedLong() const
{
    if (!pos || *this > ULONG_MAX)
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("out of bounds");
#else
    std::cerr << "Out of ULONG bounds: " << *this << std::endl;
#endif
    unsigned long result = 0;
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        result = result * BASE + val[i];
    }
    return result;
}

inline unsigned long long InfInt::toUnsignedLongLong() const
{
    if (!pos || *this > ULONG_LONG_MAX)
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("out of bounds");
#else
    std::cerr << "Out of ULLONG bounds: " << *this << std::endl;
#endif
    unsigned long long result = 0;
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        result = result * BASE + val[i];
    }
    return result;
}

inline void InfInt::truncateToBase()
{
    for (size_t i = 0; i < val.size(); ++i) // truncate each
    {
        if (val[i] >= BASE || val[i] <= -BASE)
        {
            div_t dt = div(val[i], BASE);
            val[i] = dt.rem;
            if (i + 1 >= val.size())
            {
                val.push_back(dt.quot);
            }
            else
            {
                val[i + 1] += dt.quot;
            }
        }
    }
}

inline void InfInt::equalizeSigns()
{
    for (int i = (int) ((val.size())) - 1; i >= 0; --i) // make all signs equal
    {
        if (val[i] < 0)
        { // current number is negative
            int k = 0, index = i + k + 1;
            for (; (size_t)(index) < val.size() && val[index] == 0; ++k, ++index); // count adjacent zeros on left
            if ((size_t)(index) < val.size() && val[index] > 0)
            { // number on the left is positive
                val[index] -= 1;
                val[i] += BASE;
                for (; k > 0; --k)
                {
                    val[i + k] = UPPER_BOUND;
                }
            }
            else
            {
                k = 0, index = i - k - 1;
                for (; index >= 0 && val[index] == 0; ++k, ++index); // count adjacent zeros on right
                if (index >= 0 && val[index] > 0)
                { // number on the right is positive
                    val[i] += 1;
                    val[index] -= BASE;
                    for (; k > 0; --k)
                    {
                        val[i - k] = -UPPER_BOUND;
                    }
                }
            }
        }
    }
}

inline bool InfInt::allPositive()
{
    for (size_t i = 0; i < val.size(); ++i)
    {
        if (val[i] < 0)
        {
            return false;
        }
    }
    
    return true;
}

inline void InfInt::removeLeadingZeros()
{
    for (int i = (int) (val.size()) - 1; i > 0; --i) // remove leading 0's
    {
        if (val[i] != 0)
        {
            return;
        }
        else
        {
            val.erase(val.begin() + i);
        }
    }
}

inline void InfInt::correct(bool justCheckLeadingZeros, bool hasValidSign)
{
    if (!justCheckLeadingZeros)
    {
        truncateToBase();
        
        equalizeSigns();
        
        if (allPositive())
        {
            pos = ((val.size() == 1 && val[0] == 0) || !hasValidSign) ? true : pos;
        }
        else
        {
            pos = hasValidSign ? !pos : false;
            for (size_t i = 0; i < val.size(); ++i)
            {
                val[i] = abs(val[i]);
            }
        }
    }
    
    removeLeadingZeros();
}

inline void InfInt::fromString(const std::string& s)
{
    pos = true;
    val.clear();
    int i = (int) s.size() - DIGIT_COUNT;
    for (; i >= 0; i -= DIGIT_COUNT)
    {
        val.push_back(atoi(s.substr(i, DIGIT_COUNT).c_str()));
    }
    if (i > -DIGIT_COUNT)
    {
        std::string ss = s.substr(0, i + DIGIT_COUNT);
        if (ss.size() == 1 && ss[0] == '-')
        {
            pos = false;
        }
        else
        {
            val.push_back(atoi(ss.c_str()));
        }
    }
    if (val.back() < 0)
    {
        val.back() = -val.back();
        pos = false;
    }
    correct(true);
}

inline ELEM_TYPE InfInt::dInR(const InfInt& R, const InfInt& D)
{
    ELEM_TYPE min = 0, max = UPPER_BOUND;
    while (max - min > 0)
    {
        ELEM_TYPE avg = max + min;
        div_t dt = div(avg, 2);
        avg = dt.rem ? (dt.quot + 1) : dt.quot;
        InfInt prod = D * avg;
        if (R == prod)
        {
            return avg;
        }
        else if (R > prod)
        {
            min = avg;
        }
        else
        {
            max = avg - 1;
        }
    }
    return min;
}

inline void InfInt::multiplyByDigit(ELEM_TYPE factor, std::deque<ELEM_TYPE>& val)
{
    ELEM_TYPE carry = 0;
    for (size_t i = 0; i < val.size(); ++i)
    {
        PRODUCT_TYPE pval = val[i] * (PRODUCT_TYPE) factor + carry;
        if (pval >= BASE || pval <= -BASE)
        {
            PRODUCT_TYPE quot;
            ELEM_TYPE rem;
            divide(pval, BASE, quot, rem);
            carry = (ELEM_TYPE) quot;
            pval = rem;
            //carry = (ELEM_TYPE) (pval / BASE);
            //pval %= BASE;
        }
        else
        {
            carry = 0;
        }
        ensureIndex(i, val);
        val[i] = (ELEM_TYPE) pval;
    }
    if (carry > 0)
    {
        val.push_back(carry);
    }
}

inline void InfInt::divide(PRODUCT_TYPE numer, ELEM_TYPE denom, PRODUCT_TYPE& quot, ELEM_TYPE& rem)
{
#ifdef INFINT_USE_SHORT_BASE
    div_t dt = div(numer, denom);
    rem = (ELEM_TYPE) dt.rem;
    quot = dt.quot;
#else
#ifndef WIN32
    lldiv_t dt = lldiv(numer, denom);
    rem = (ELEM_TYPE) dt.rem;
    quot = dt.quot;
#else
    rem = (ELEM_TYPE) (numer % denom);
    quot = numer / denom;
#endif
#endif
}

inline void InfInt::ensureIndex(size_t s, std::deque<ELEM_TYPE>& val)
{
    while (val.size() <= s)
    {
        val.push_back(0);
    }
}

/**************************************************************/
/******************** NON-MEMBER OPERATORS ********************/
/**************************************************************/

inline std::istream& operator>>(std::istream &s, InfInt &n)
{
    std::string str;
    s >> str;
    n.fromString(str);
    return s;
}

inline std::ostream& operator<<(std::ostream &s, const InfInt &n)
{
    if (!n.pos)
    {
        s << '-';
        }
        bool first = true;
        for (int i = (int) n.val.size() - 1; i >= 0; --i)
        {
            if (first)
            {
                s << n.val[i];
                first = false;
            }
            else
            {
                s << std::setfill('0') << std::setw(DIGIT_COUNT) << n.val[i];
            }
        }
        return s;
        }
        
#endif
