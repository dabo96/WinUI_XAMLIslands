#include "Window.h"

Window::Window(int w, int h)
{
    openGLWrapper = std::make_shared<OpenGL>();
    width = w;
    height = h;
    //desktopSource = std::make_shared<DesktopWindowXamlSource>();
    //ab1 = std::make_shared<Windows::UI::Xaml::Media::AcrylicBrush>();
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

    //DesktopWindowXamlSource desktopSource;
    ////DesktopWindowXamlSource desktopSource1;

    //auto interop = desktopSource.as<IDesktopWindowXamlSourceNative>();

    //check_hresult(interop->AttachToWindow(m_hwnd));

    //hWndXamlIsland = nullptr;

    //interop->get_WindowHandle(&hWndXamlIsland);

    //SetWindowPos(hWndXamlIsland, 0, 0, 0, 500, 800, SWP_SHOWWINDOW);

    /*auto window = createXamlIslands();

    hWndXamlIsland = nullptr;    
    
    SetWindowPos(hWndXamlIsland, 0, 0, 0, 500, 800, SWP_SHOWWINDOW);*/

    /*auto interop1 = desktopSource1.as<IDesktopWindowXamlSourceNative>();

    check_hresult(interop1->AttachToWindow(m_hwnd));

    HWND hWndXamlIsland1 = nullptr;

    interop1->get_WindowHandle(&hWndXamlIsland1);

    SetWindowPos(hWndXamlIsland1, 0, 800, 100, 500, 800, SWP_SHOWWINDOW);*/

    /*Windows::UI::Xaml::Media::AcrylicBrush ab = Windows::UI::Xaml::Media::AcrylicBrush::AcrylicBrush();
    ab.BackgroundSource(Windows::UI::Xaml::Media::AcrylicBackgroundSource::HostBackdrop);
    ab.TintColor(Windows::UI::Colors::Black());
    ab.FallbackColor(Windows::UI::Colors::DarkGray());
    ab.TintOpacity(0.6);

    Windows::UI::Xaml::Controls::StackPanel xamlContainer1;
    xamlContainer1.Background(ab);

    ab1->BackgroundSource(Windows::UI::Xaml::Media::AcrylicBackgroundSource::HostBackdrop);
    ab1->TintColor(Windows::UI::Colors::White());
    ab1->FallbackColor(Windows::UI::Colors::Black());
    ab1->TintOpacity(0.6);

    xamlContainer = std::make_shared<Windows::UI::Xaml::Controls::StackPanel>();

    xamlContainer->Background(*ab1);*/

    //Controls::Toolbar app(L"ToolbarWindow");
    //Controls::Toolbar app(L"ToolbarWindow");


    //f();
    /*xamlContainer->Children().Append(*app.create());
    xamlContainer->UpdateLayout();
    xamlContainer1.UpdateLayout();*/
    //hWndXamlIsland = createXamlIslands(L"Toolbar Window", 0, 0, 500, 800, *xamlContainer);
    Controls::ControlWindow w(L"toolbar window", 0, 0, 500, 800, nullptr);
    Controls::ControlWindow w1(L"toolbar window", 600, 0, 500, 800, nullptr);

    hWndXamlIsland = w.create(m_hwnd);
    hWndXamlIsland1 = w1.create(m_hwnd); 
    //hWndXamlIsland1 = createXamlIslands(L"Toolbar Window 2", 600, 0, 500, 800, xamlContainer1);
    ShowWindow(m_hwnd, cmdShow);
    UpdateWindow(m_hwnd);

    loop();
}

std::shared_ptr<Windows::UI::Xaml::Controls::StackPanel> Window::getStackPanel()
{
    return xamlContainer;
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
    case WM_CREATE:
    {        
        //hWndXamlIsland = createXamlIslands();
    }        
    break;
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

//std::shared_ptr<DesktopWindowXamlSource> Window::createXamlIslands()
//{
//    /*auto interop = desktopSource->as<IDesktopWindowXamlSourceNative>();
//    winrt::check_hresult(interop->AttachToWindow(m_hwnd));
//
//    winrt::check_hresult(interop->get_WindowHandle(&hWndXamlIsland));
//    const DWORD style = GetWindowLongW(hWndXamlIsland, GWL_STYLE);
//    SetWindowLongW(hWndXamlIsland, GWL_STYLE, style);*/
//
//    return desktopSource;
//}
HWND Window::createXamlIslands(const wchar_t* texto, int posx, int posy, int width, int height, Windows::UI::Xaml::Controls::StackPanel content)
{

    ////DesktopWindowXamlSource desktopSource1;
    //
    //auto interop = desktopSource->as<IDesktopWindowXamlSourceNative>();
    //winrt::check_hresult(interop->AttachToWindow(m_hwnd));

    //HWND hwnd = nullptr;
    //winrt::check_hresult(interop->get_WindowHandle(&hwnd));
    //const DWORD style = GetWindowLongW(hWndXamlIsland, GWL_STYLE);
    //SetWindowLongW(hWndXamlIsland, GWL_STYLE, style);

    //SetWindowPos(hwnd, 0, posx, posy, width, height, SWP_SHOWWINDOW);
    ////Tittle bar configuration    
    //desktopSource->Content(content);
    //return hwnd;
    return HWND();
}
