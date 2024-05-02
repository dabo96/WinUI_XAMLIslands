#pragma once
#include "OpenglFunctions.h"
#include "Util.h"
#include "glcorearb.h"  // download from https://www.khronos.org/registry/OpenGL/api/GL/glcorearb.h
#include "wglew.h"     // download from https://www.khronos.org/registry/OpenGL/api/GL/wglext.h
#include <intrin.h>

class OpenGL
{
public:
	OpenGL();

	static void FatalError(const char* message);
	int StringsAreEqual(const char* src, const char* dst, size_t dstlen);
	//
	void GetWglFunctions();
	void setPixelFormat(HDC dc);
	void CreateModernContext(HDC dc);
	void initGlew();


	PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
	PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;
};

