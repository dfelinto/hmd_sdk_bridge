#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <iostream>

class Debug
{
public:
	Debug(int number) {
		std::cout << "Debug(" << number << ")" << std::endl;
		this->m_number = number;
	};
	~Debug() {
		std::cout << "~Debug()" << std::endl;
	};

	void matrixNonStatic(float *r_float) {
		r_float[0] = 1.0;
		r_float[1] = 2.0;
		r_float[2] = 3.0;
		r_float[3] = 4.0;
	};

	static void matrix(float *r_float) {
		r_float[0] = 1.0;
		r_float[1] = 2.0;
		r_float[2] = 3.0;
		r_float[3] = 4.0;
	};

	static void draw(const unsigned int color_texture)
	{
		/* TODO draw something in the texture*/
		printf("debug::draw(%d)\n", color_texture);
	};

	static int multiplicationFactor() { return m_factor; };

	int multiplicationResult()
	{
		return Debug::m_factor * this->m_number; 
	};

private:
	static int m_factor;
	int m_number;
};

int Debug::m_factor = 2;

#endif /* __DEBUG_H__ */