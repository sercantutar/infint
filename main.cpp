#include "InfInt.h"

#include <assert.h>

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
	std::cout << "SIZES: " << myint1.size() << " " << myint2.size() << std::endl;
	//myint2.toInt(); myint2.tol(); myint2.toll();
	//myint2.toui(); myint2.toUnsignedLong(); myint2.toUnsignedLongLong();
	for (int i = 0; i < 100; ++i)
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
			InfInt rootPlusOne = root + InfInt::one;
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
{//PROFILED_SCOPE
	testInfInteger();
	//std::cout << fib(100000) << std::endl;
	//std::cout << fact(10000) << std::endl;

	//atexit(Profiler::print);
	return 0;
}
