// Prueba.cpp : Defines the entry point for the application.
//
#include "Window.h"

void createControls(Window* w);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    winrt::init_apartment(apartment_type::multi_threaded);

    Window* w = new Window(1920, 1080);
    w->createWindow(hInstance, nCmdShow, [w]() {
        /*Controls::Label l(L"Hola Mundo", 100, 100);
        Controls::Label lm(L"Holi", 100, 300);
        Controls::IButton b(L"Prueba", 10, 10);
        w->getStackPanel()->Children().Append(l.create());
        w->getStackPanel()->Children().Append(lm.create());
        w->getStackPanel()->Children().Append(b.create());*/
        createControls(w);
     });
}

void createControls(Window* w) {
    Controls::Label l(L"Hola Mundo", 100, 100);
    Controls::Label lm(L"Holi", 100, 300);
    Controls::IButton b(L"Prueba", 10, 10);
    Controls::TextField tf(L"Prueba", 300, 300);
    Controls::TextArea ta(L"Prueba", 400, 10);
    w->getStackPanel()->Children().Append(l.create());
    w->getStackPanel()->Children().Append(lm.create());
    w->getStackPanel()->Children().Append(b.create());
    w->getStackPanel()->Children().Append(tf.create());
    w->getStackPanel()->Children().Append(ta.create());
}