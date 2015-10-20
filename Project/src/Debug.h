#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <iostream>

#include <GL/CAPI_GLE.h>
#include "OVR_CAPI_GL.h"

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
#if 0
		Ideally we want to:
			* create a framebuffer
			* bind the color_texture to it
			* bind the framebuffer
			* draw something

			But for now I am happy if we
#endif
		GLuint fbo[2];

		printf("%s : %d\n", __FILE__, __LINE__);
		glGenFramebuffers(1, fbo); /* it crashes here at the moment */
		printf("%s : %d\n", __FILE__, __LINE__);

#if 1
		GLuint texName[2];
		glGenTextures(1, texName);
		printf("%s : %d\n", __FILE__, __LINE__);
		glActiveTexture(GL_TEXTURE0);
		printf("%s : %d\n", __FILE__, __LINE__);
		glBindTexture(GL_TEXTURE_2D, texName[0]);
		printf("%s : %d\n", __FILE__, __LINE__);
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, 128, 128, 0);
		printf("%s : %d\n", __FILE__, __LINE__);
		glBindTexture(GL_TEXTURE_2D, 0);
		printf("%s : %d\n", __FILE__, __LINE__);
#endif
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