#pragma once
#define Assert(cond) do { if (!(cond)) __debugbreak(); } while (0)
#define STR2(x) #x
#define STR(x) STR2(x)

#include <Windows.h>
#include <glew.h>

struct util {
    static void APIENTRY DebugCallback(
        GLenum source, GLenum type, GLuint id, GLenum severity,
        GLsizei length, const GLchar* message, const void* user);
};


