// Prueba.cpp : Defines the entry point for the application.
//
#include "Window.h"

void createControls(Window* w);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    winrt::init_apartment(apartment_type::multi_threaded);

    Window* w = new Window(1920, 1080);
    w->createWindow(hInstance, nCmdShow, [w]() {
        createControls(w);
     });
}

void createControls(Window* w) {
    Controls::ControlWindow* window = new Controls::ControlWindow(L"toolbar window", 0, 0, 500, 800);
    Controls::ControlWindow* window1 = new Controls::ControlWindow(L"toolbar window", 600, 0, 500, 800);
    HWND hwnd = window->create(w->handle());
    HWND hwnd1 = window1->create(w->handle());

    std::shared_ptr<Controls::Label> l =  std::make_shared<Controls::Label>(L"Hola Mundo", 100, 100);
    
    Controls::Label lm(L"Hola", 100, 300);
    std::shared_ptr<Controls::IButton> b = std::make_shared<Controls::IButton>(L"Prueba", 10, 10);

    //HWND btn = CreateWindow(L"BUTTON", L"Hola mundo", WS_CHILD | WS_VISIBLE, 100, 100, 90, 20, hwnd1, (HMENU)1, NULL, NULL);
    
    /*b.Click([l, window1](winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::RoutedEventArgs const&) {
        l->Text() = L"Hola";
        Controls::Label prueba(L"hola", 100, 100);
        window1->getPanel()->Children().Append(prueba.create());
        window1->getPanel()->UpdateLayout();
    });*/
    //Controls::TextField tf(L"Prueba", 300, 300);
    //Controls::TextArea ta(L"Prueba", 400, 10);
    //Controls::ISlider s(100, 700, 0, 100, 10);

    window->getPanel()->Children().Append(l->create());
    window->getPanel()->Children().Append(lm.create());
    window->getPanel()->Children().Append(b->create());
    //window->getPanel()->Children().Append(tf.create());
    //window->getPanel()->Children().Append(ta.create());
}