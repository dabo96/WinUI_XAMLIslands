#include "OpenGL.h"

OpenGL::OpenGL()
{
    wglChoosePixelFormatARB = NULL;
    wglCreateContextAttribsARB = NULL;
    wglSwapIntervalEXT = NULL;
}

void OpenGL::FatalError(const char* message)
{
    MessageBoxA(NULL, message, "Error", MB_ICONEXCLAMATION);
    ExitProcess(0);
}

int OpenGL::StringsAreEqual(const char* src, const char* dst, size_t dstlen)
{
    while (*src && dstlen-- && *dst)
    {
        if (*src++ != *dst++)
        {
            return 0;
        }
    }

    return (dstlen && *src == *dst) || (!dstlen && *src == 0);
}

void OpenGL::GetWglFunctions()
{
    // to get WGL functions we need valid GL context, so create dummy window for dummy GL context
    HWND dummy = CreateWindowExW(
        0, L"STATIC", L"DummyWindow", WS_OVERLAPPED,
        0, 0, 0, 0,
        NULL, NULL, NULL, NULL);
    Assert(dummy && "Failed to create dummy window");

    HDC dc = GetDC(dummy);
    Assert(dc && "Failed to get device context for dummy window");

    PIXELFORMATDESCRIPTOR desc =
    {
        desc.nSize = sizeof(desc),
        desc.nVersion = 1,
        desc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        desc.iPixelType = PFD_TYPE_RGBA,
        desc.cColorBits = 32,
        desc.cAlphaBits = 8,
        desc.cDepthBits = 32,
        desc.iLayerType = PFD_MAIN_PLANE,

    };

    int format = ChoosePixelFormat(dc, &desc);
    if (!format)
    {
        FatalError("Cannot choose OpenGL pixel format for dummy window!");
    }

    int ok = DescribePixelFormat(dc, format, sizeof(desc), &desc);
    Assert(ok && "Failed to describe OpenGL pixel format");

    // reason to create dummy window is that SetPixelFormat can be called only once for the window
    if (!SetPixelFormat(dc, format, &desc))
    {
        FatalError("Cannot set OpenGL pixel format for dummy window!");
    }

    HGLRC rc = wglCreateContext(dc);
    Assert(rc && "Failed to create OpenGL context for dummy window");

    ok = wglMakeCurrent(dc, rc);
    Assert(ok && "Failed to make current OpenGL context for dummy window");

    PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB =
        (PFNWGLGETEXTENSIONSSTRINGARBPROC)wglGetProcAddress("wglGetExtensionsStringARB");
    if (!wglGetExtensionsStringARB)
    {
        FatalError("OpenGL does not support WGL_ARB_extensions_string extension!");
    }

    const char* ext = wglGetExtensionsStringARB(dc);
    Assert(ext && "Failed to get OpenGL WGL extension string");

    const char* start = ext;
    for (;;)
    {
        while (*ext != 0 && *ext != ' ')
        {
            ext++;
        }

        size_t length = ext - start;
        if (StringsAreEqual("WGL_ARB_pixel_format", start, length))
        {
            wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
        }
        else if (StringsAreEqual("WGL_ARB_create_context", start, length))
        {
            wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
        }
        else if (StringsAreEqual("WGL_EXT_swap_control", start, length))
        {
            wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
        }

        if (*ext == 0)
        {
            break;
        }

        ext++;
        start = ext;
    }

    if (!wglChoosePixelFormatARB || !wglCreateContextAttribsARB || !wglSwapIntervalEXT)
    {
        FatalError("OpenGL does not support required WGL extensions for modern context!");
    }

    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(rc);
    ReleaseDC(dummy, dc);
    DestroyWindow(dummy);
}

void OpenGL::setPixelFormat(HDC dc)
{
    int attrib[] =
    {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
        WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
        WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB,     24,
        WGL_DEPTH_BITS_ARB,     24,
        WGL_STENCIL_BITS_ARB,   8,

        // uncomment for sRGB framebuffer, from WGL_ARB_framebuffer_sRGB extension
        // https://www.khronos.org/registry/OpenGL/extensions/ARB/ARB_framebuffer_sRGB.txt
        WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB, GL_TRUE,

        // uncomment for multisampeld framebuffer, from WGL_ARB_multisample extension
        // https://www.khronos.org/registry/OpenGL/extensions/ARB/ARB_multisample.txt
        WGL_SAMPLE_BUFFERS_ARB, 1,
        WGL_SAMPLES_ARB,        4, // 4x MSAA

        0,
    };

    int format;
    UINT formats;
    if (!wglChoosePixelFormatARB(dc, attrib, NULL, 1, &format, &formats) || formats == 0)
    {
        FatalError("OpenGL does not support required pixel format!");
    }

    PIXELFORMATDESCRIPTOR desc = { desc.nSize = sizeof(desc) };
    int ok = DescribePixelFormat(dc, format, sizeof(desc), &desc);
    Assert(ok && "Failed to describe OpenGL pixel format");

    if (!SetPixelFormat(dc, format, &desc))
    {
        FatalError("Cannot set OpenGL selected pixel format!");
    }
}

void OpenGL::CreateModernContext(HDC dc)
{
    int attrib[] =
    {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 5,
        WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
#ifndef NDEBUG
        // ask for debug context for non "Release" builds
        // this is so we can enable debug callback
        WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
#endif
            0,
    };

    HGLRC rc = wglCreateContextAttribsARB(dc, NULL, attrib);
    if (!rc)
    {
        FatalError("Cannot create modern OpenGL context! OpenGL version 4.5 not supported?");
    }

    BOOL ok = wglMakeCurrent(dc, rc);
    Assert(ok && "Failed to make current OpenGL context");

    // load OpenGL functions
#define X(type, name) name = (type)wglGetProcAddress(#name); Assert(name);
    GL_FUNCTIONS(X)
#undef X

#ifndef NDEBUG
        // enable debug callback
        glDebugMessageCallback(util::DebugCallback, NULL);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
#endif
}

void OpenGL::initGlew()
{
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        OpenGL::FatalError("Error al inicializar GLEW");
    }
}
