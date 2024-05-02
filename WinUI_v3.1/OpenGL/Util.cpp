#include "Util.h"

#ifndef NDEBUG
void APIENTRY util::DebugCallback(
    GLenum source, GLenum type, GLuint id, GLenum severity,
    GLsizei length, const GLchar* message, const void* user)
{
    OutputDebugStringA(message);
    OutputDebugStringA("\n");
    if (severity == GL_DEBUG_SEVERITY_HIGH || severity == GL_DEBUG_SEVERITY_MEDIUM)
    {
        if (IsDebuggerPresent())
        {
            Assert(!"OpenGL error - check the callstack in debugger");
        }
        MessageBoxA(NULL, "OpenGL API usage error! Use debugger to examine call stack!", "Error", MB_ICONEXCLAMATION);
    }
}

#endif