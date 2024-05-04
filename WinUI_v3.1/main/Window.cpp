#include "Window.h"

Window::Window(int w, int h)
{
    openGLWrapper = std::make_shared<OpenGL>();
    width = w;
    height = h;
}

void Window::createWindow(HINSTANCE hInstance, int cmdShow, std::function<void()> f)
{
    WindowsXamlManager winxamlmanager = WindowsXamlManager::InitializeForCurrentThread();

    openGLWrapper->GetWglFunctions();

    WNDCLASSEX windowClass = { };

    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = hInstance;
    windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.lpszClassName = L"opengl_window_class";
    windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    windowClass.hIconSm = LoadIcon(windowClass.hInstance, IDI_APPLICATION);

    if (RegisterClassEx(&windowClass) == NULL)
    {
        MessageBox(NULL, L"Windows registration failed!", L"Error", NULL);
    }
    
    m_hwnd = CreateWindow(
        L"opengl_window_class",
        L"Windows c++ Win32 Desktop App",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CLIPCHILDREN,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        NULL,
        NULL,
        hInstance,
        this
    );
    if (m_hwnd == NULL)
    {
        MessageBox(NULL, L"Call to CreateWindow failed!", L"Error", NULL);
    }

    dc = GetDC(m_hwnd);
    openGLWrapper->setPixelFormat(dc);
    openGLWrapper->CreateModernContext(dc);
    openGLWrapper->initGlew();

    glViewport(0, 0, width, height);

    f();

    ShowWindow(m_hwnd, cmdShow);
    UpdateWindow(m_hwnd);

    loop();
}

int Window::loop()
{
    MSG msg;
    bool salir = true;
    // Main message loop:
    while (salir)
    {
        if (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
            {
                salir = false;
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        glClearColor(0.392f, 0.584f, 0.929f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        SwapBuffers(dc);
    }

    return (int)msg.wParam;
}

LRESULT Window::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int posx = 0;
    int posy = 0;

    switch (uMsg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(m_hwnd, &ps);
        EndPaint(m_hwnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
