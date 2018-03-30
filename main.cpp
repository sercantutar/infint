//#define USE_PROFINY
#include "InfInt.h"

//#define PROFINY_CALL_GRAPH_PROFILER
//#include "..\profiny\Profiny.h"

#include <assert.h>
//#include <limits.h>
//#include <iostream>

InfInt fib(InfInt n)
{
    InfInt pp = 0, p = 1;
    for (InfInt i=2; i<n; ++i)
    {
        InfInt op = p;
        p += pp;
        pp = op;
    }
    return p + pp;
}

InfInt fact(InfInt n)
{
    InfInt result = 1;
    for (InfInt i=2; i<=n; ++i)
    {
        result *= i;
    }
    return result;
}

void testInfInteger()
{
    InfInt myint1 = "15432154865413186646848435184100510168404641560358";
    InfInt myint2 = 156341300544608LL;
    //std::cout << "SIZES: " << myint1.size() << " " << myint2.size() << std::endl;
    {
        assert(InfInt(INT_MIN) == INT_MIN);
        assert(InfInt(INT_MAX) == INT_MAX);
        assert(InfInt(INT_MIN).toInt() == INT_MIN);
        assert(InfInt(INT_MAX).toInt() == INT_MAX);

        assert(InfInt(LONG_MIN) == LONG_MIN);
        assert(InfInt(LONG_MAX) == LONG_MAX);
        assert(InfInt(LONG_MIN).toLong() == LONG_MIN);
        assert(InfInt(LONG_MAX).toLong() == LONG_MAX);

        assert(InfInt(LONG_LONG_MIN) == LONG_LONG_MIN);
        assert(InfInt(LONG_LONG_MAX) == LONG_LONG_MAX);
        assert(InfInt(LONG_LONG_MIN).toLongLong() == LONG_LONG_MIN);
        assert(InfInt(LONG_LONG_MAX).toLongLong() == LONG_LONG_MAX);

        assert(InfInt(0U) == 0U);
        assert(InfInt(UINT_MAX) == UINT_MAX);
        assert(InfInt(0U).toUnsignedInt() == 0U);
        assert(InfInt(UINT_MAX).toUnsignedInt() == UINT_MAX);

        assert(InfInt(0UL) == 0UL);
        assert(InfInt(ULONG_MAX) == ULONG_MAX);
        assert(InfInt(0UL).toUnsignedLong() == 0UL);
        assert(InfInt(ULONG_MAX).toUnsignedLong() == ULONG_MAX);

        assert(InfInt(0ULL) == 0ULL);
        assert(InfInt(ULONG_LONG_MAX) == ULONG_LONG_MAX);
        assert(InfInt(0ULL).toUnsignedLongLong() == 0ULL);
        assert(InfInt(ULONG_LONG_MAX).toUnsignedLongLong() == ULONG_LONG_MAX);
    }
    for (int i = 0; i < 5000; ++i)
    {
        InfInt i1, i2;
        {
            i1 = myint1++;
            assert(i1-- == myint1-1);
            assert(myint1-3 == --i1);
            assert(i1 == myint1-3);
        }
        {
            i2 = myint2--;
            assert(i2++ == myint2+1);
            assert(myint2+3 == ++i2);
            assert(i2 == myint2+3);
        }
        {
            assert(InfInt(155)/InfInt(-37) == 155/(-37));
            assert(InfInt(155)%InfInt(-37) == 155%(-37));
            assert(InfInt(-155)/InfInt(-37) == (-155)/(-37));
            assert(InfInt(-155)%InfInt(-37) == (-155)%(-37));
            assert(InfInt(-155)/InfInt(37) == (-155)/37);
            assert(InfInt(-155)%InfInt(37) == (-155)%37);
        }
        {
            InfInt root = myint1.intSqrt();
            InfInt rootPlusOne = root + 1;
            assert(root*root <= myint1 && myint1 <= rootPlusOne*rootPlusOne);
            assert((myint1*myint1).intSqrt() == myint1);
            assert((myint1/myint2) * myint2 + (myint1%myint2) == myint1);
        }
        {
            i1 = myint1;
            i1 += myint2;
            assert(i1 == myint1 + myint2);
        }
        {
            i1 = myint1;
            i1 -= myint2;
            assert(i1 == myint1 - myint2);
        }
        {
            i1 = myint1;
            i1 /= myint2;
            assert(i1 == myint1 / myint2);
        }
        {
            i1 = myint1;
            i1 *= myint2;
            assert(i1 == myint1 * myint2);
        }
        {
            i1 = myint1;
            i1 %= myint2;
            assert(i1 == myint1 % myint2);
        }
    }

    assert(InfInt(1).intSqrt() == 1);
    assert(InfInt(2).intSqrt() == 1);
    assert(InfInt(3).intSqrt() == 1);
    assert(InfInt(4).intSqrt() == 2);
    assert(InfInt(5).intSqrt() == 2);
    assert(InfInt(6).intSqrt() == 2);
    assert(InfInt(7).intSqrt() == 2);
    assert(InfInt(8).intSqrt() == 2);
    assert(InfInt(9).intSqrt() == 3);
}

int main(int argc, const char * argv[])
{
    //PROFINY_SCOPE
    //testInfInteger();
    //fib(200000);
    //fact(40000);
    //std::cout << fib(100000) << std::endl;
    //std::cout << fact(10000) << std::endl;

    InfInt a = -1;
    assert(a++ == -1); assert(a++ == 0); assert(a == 1);
    assert(a-- == 1); assert(a-- == 0); assert(a == -1);
    assert(++a == 0); assert(++a == 1); assert(a == 1);
    assert(--a == 0); assert(--a == -1); assert(a == -1);

    a = UPPER_BOUND;
    assert(a++ == UPPER_BOUND); assert(a == UPPER_BOUND + 1);
    assert(a-- == UPPER_BOUND + 1); assert(a == UPPER_BOUND);
    assert(++a == UPPER_BOUND + 1); assert(a == UPPER_BOUND + 1);
    assert(--a == UPPER_BOUND); assert(a == UPPER_BOUND);

    a = -UPPER_BOUND;
    assert(a++ == -UPPER_BOUND); assert(a == -UPPER_BOUND + 1);
    assert(a-- == -UPPER_BOUND + 1); assert(a == -UPPER_BOUND);
    assert(++a == -UPPER_BOUND + 1); assert(a == -UPPER_BOUND + 1);
    assert(--a == -UPPER_BOUND); assert(a == -UPPER_BOUND);

    a = UPPER_BOUND;
    assert((a += UPPER_BOUND) == 2 * UPPER_BOUND); assert(a == 2 * UPPER_BOUND);
    assert((a += -UPPER_BOUND) == UPPER_BOUND); assert(a == UPPER_BOUND);
    assert((a -= UPPER_BOUND) == 0); assert(a == 0);
    assert((a -= -UPPER_BOUND) == UPPER_BOUND); assert(a == UPPER_BOUND);

    a = -UPPER_BOUND;
    assert((a -= UPPER_BOUND) == 2 * -UPPER_BOUND); assert(a == 2 * -UPPER_BOUND);
    assert((a -= -UPPER_BOUND) == -UPPER_BOUND); assert(a == -UPPER_BOUND);
    assert((a += UPPER_BOUND) == 0); assert(a == 0);
    assert((a += -UPPER_BOUND) == -UPPER_BOUND); assert(a == -UPPER_BOUND);

    a = UPPER_BOUND;
    assert((a = a + UPPER_BOUND) == 2 * UPPER_BOUND); assert(a == 2 * UPPER_BOUND);
    assert((a = a + -UPPER_BOUND) == UPPER_BOUND); assert(a == UPPER_BOUND);
    assert((a = a - UPPER_BOUND) == 0); assert(a == 0);
    assert((a = a - -UPPER_BOUND) == UPPER_BOUND); assert(a == UPPER_BOUND);

    a = -UPPER_BOUND;
    assert((a = a - UPPER_BOUND) == 2 * -UPPER_BOUND); assert(a == 2 * -UPPER_BOUND);
    assert((a = a - -UPPER_BOUND) == -UPPER_BOUND); assert(a == -UPPER_BOUND);
    assert((a = a + UPPER_BOUND) == 0); assert(a == 0);
    assert((a = a + -UPPER_BOUND) == -UPPER_BOUND); assert(a == -UPPER_BOUND);

    a = UPPER_BOUND;
    assert((a *= UPPER_BOUND) == UPPER_BOUND * (long long) UPPER_BOUND); assert(a == UPPER_BOUND * (long long) UPPER_BOUND);
    assert((a /= UPPER_BOUND) == UPPER_BOUND); assert(a == UPPER_BOUND);
    assert((a *= -UPPER_BOUND) == -UPPER_BOUND * (long long) UPPER_BOUND); assert(a == -UPPER_BOUND * (long long) UPPER_BOUND);
    assert((a /= -UPPER_BOUND) == UPPER_BOUND); assert(a == UPPER_BOUND);

    a = UPPER_BOUND;
    assert((a = a * UPPER_BOUND) == UPPER_BOUND * (long long) UPPER_BOUND); assert(a == UPPER_BOUND * (long long) UPPER_BOUND);
    assert((a = a / UPPER_BOUND) == UPPER_BOUND); assert(a == UPPER_BOUND);
    assert((a = a * -UPPER_BOUND) == -UPPER_BOUND * (long long) UPPER_BOUND); assert(a == -UPPER_BOUND * (long long) UPPER_BOUND);
    assert((a = a / -UPPER_BOUND) == UPPER_BOUND); assert(a == UPPER_BOUND);


    return 0;
}
