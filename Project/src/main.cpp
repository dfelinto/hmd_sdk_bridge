#include "Bridge.h"
#include "Oculus.h"
#include "../Include/Bridge_C_API.h"

#include <iostream>

extern "C"
{
	int functionTest(int input);
}

int functionTest(int input)
{
	std::cout << "functionTest: " << input << std::endl;
	return input * 2;
}

int main()
{
	return 0;
}