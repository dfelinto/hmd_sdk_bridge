#include "../Include/Bridge_C_API.h"

#include <iostream>

int functionTest(int input)
{
	std::cout << "functionTest: " << input << std::endl;
	return input * 2;
}