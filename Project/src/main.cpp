#include "Bridge.h"
#include "Oculus.h"

#include "../Include/Bridge_C_API.h"

#include <iostream>

int functionTest(int input)
{
	std::cout << "functionTest: " << input << std::endl;
	return input * 2;
}

int main()
{
	return 0;
}

#undef EXPORT_DLL