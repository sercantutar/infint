--- Introduction ---

InfInt is simply a lightweight large integer library which consists of a header file. So, all you have to do is to include the header file provided and start using huge integers in your applications.

--- Details ---

It is pretty straight forward to use the library. Just create an instance of InfInt class and start using it:

    InfInt myint1 = "15432154865413186646848435184100510168404641560358";
    InfInt myint2 = 156341300544608LL;

    myint1 *= --myint2 - 3;
    std::cout << myint1 << std::endl;

Useful methods:

    intSqrt: integer square root operation
    digitAt: returns digit at index
    numberOfDigits: returns number of digits
    size: returns size in bytes
    toString: converts it to a string

There are also conversion methods which allow conversion to primitive types:

    toInt, toLong, toLongLong, toUnsignedInt, toUnsignedLong, toUnsignedLongLong.

You may define INFINT_USE_EXCEPTIONS and library methods will start raising InfIntException? in case of error instead of writing error messages using std::cerr.
