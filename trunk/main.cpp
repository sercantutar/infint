#include "InfInt.h"

#include <assert.h>

InfInt fib(InfInt n)
{
	InfInt pp = 0, p = 1;
	for (InfInt i=3; i<n; ++i)
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
}

int main(int argc, const char * argv[])
{
	testInfInteger();
	std::cout << fib(10000) << std::endl << std::endl;
	std::cout << fact(1000) << std::endl;
	return 0;
}
