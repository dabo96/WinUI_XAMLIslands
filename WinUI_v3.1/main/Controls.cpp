#include "Controls.h"

Controls::Label::Label(const wchar_t* texto, int posx, int posy)
{
	TranslateTransform translate;

	translate.X(posx);
	translate.Y(posy);

	tb.Text(texto);
	tb.RenderTransform(translate);
	tb.Foreground(Windows::UI::Xaml::Media::SolidColorBrush{ Windows::UI::Colors::GhostWhite() });
}

Windows::UI::Xaml::Controls::TextBlock Controls::Label::create()
{
	return tb;
}

Controls::IButton::IButton(const wchar_t* texto, int posx, int posy)
{
	TranslateTransform translate;

	translate.X(posx);
	translate.Y(posy);

	b.Content(winrt::box_value(texto));
	b.Background(Windows::UI::Xaml::Media::SolidColorBrush{ Windows::UI::Colors::Blue() });
}

Windows::UI::Xaml::Controls::Button Controls::IButton::create()
{
	return b;
}

Controls::TextField::TextField(const wchar_t* texto, int posx, int posy)
{
	TranslateTransform translate;

	translate.X(posx);
	translate.Y(posy);

	tb.RenderTransform(translate);
}

Windows::UI::Xaml::Controls::TextBox Controls::TextField::create()
{
	return tb;
}

Controls::TextArea::TextArea(const wchar_t* texto, int posx, int posy)
{
	TranslateTransform translate;

	translate.X(posx);
	translate.Y(posy);

	reb.RenderTransform(translate);
	reb.Name(L"TextArea");
}

Windows::UI::Xaml::Controls::RichEditBox Controls::TextArea::create()
{
	return reb;
}

Controls::Toolbar::Toolbar(const wchar_t* texto)
{
	TittleBarPanel = std::make_shared<Windows::UI::Xaml::Controls::StackPanel>();
	toolbar = std::make_shared<Windows::UI::Xaml::Controls::AppBar>();

	//Toolbar Brush
	ab = std::make_shared<Windows::UI::Xaml::Media::AcrylicBrush>();
	ab->BackgroundSource(Windows::UI::Xaml::Media::AcrylicBackgroundSource::HostBackdrop);
	ab->TintColor(Windows::UI::Colors::Black());
	ab->FallbackColor(Windows::UI::Colors::DarkGray());
	ab->TintOpacity(0.2);

	
	//Stack Panel that contains the elements of the toolbar
	TittleBarPanel->Background(*ab);
	

	tb.Text(texto);
	tb.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Top);
	tb.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Left);
	tb.FontSize(16);
	tb.FontFamily(Windows::UI::Xaml::Media::FontFamily::FontFamily(L"Cascadia Mono"));
	tb.Foreground(Windows::UI::Xaml::Media::SolidColorBrush{ Windows::UI::Colors::GhostWhite() });

	TittleBarPanel->Children().Append(tb);

	toolbar->Background(*ab);
	toolbar->Width(500);
	toolbar->Height(20);
	toolbar->IsOpen(true);
	toolbar->IsSticky(true);
	toolbar->Content(*TittleBarPanel);
}

std::shared_ptr<Windows::UI::Xaml::Controls::AppBar> Controls::Toolbar::create()
{
	return toolbar;
}

Controls::Container::Container()
{
	ab = std::make_shared<Windows::UI::Xaml::Media::AcrylicBrush>();
	container = std::make_shared<Windows::UI::Xaml::Controls::StackPanel>();
	t = std::make_shared<Toolbar>(L"Toolbar Window");

	ab->BackgroundSource(Windows::UI::Xaml::Media::AcrylicBackgroundSource::HostBackdrop);
	ab->TintColor(Windows::UI::Colors::White());
	ab->FallbackColor(Windows::UI::Colors::Black());
	ab->TintOpacity(0.6);

	container->Background(*ab);
	container->Children().Append(*t->create());
}

std::shared_ptr<Windows::UI::Xaml::Controls::StackPanel> Controls::Container::create()
{
	return container;
}

Controls::ControlWindow::ControlWindow(const wchar_t* texto, int px, int py, int width, int height, Windows::UI::Xaml::Controls::StackPanel content)
{
	posx = px;
	posy = py;
	w = width;
	h = height;
	t = texto;

	xamlContainer = std::make_shared<Container>();
	desktopSource= std::make_shared<DesktopWindowXamlSource>();
}

HWND Controls::ControlWindow::create(HWND m_hwnd)
{
	auto interop = desktopSource->as<IDesktopWindowXamlSourceNative>();
	winrt::check_hresult(interop->AttachToWindow(m_hwnd));

	HWND hwnd = nullptr;
	winrt::check_hresult(interop->get_WindowHandle(&hwnd));
	const DWORD style = GetWindowLongW(hwnd, GWL_STYLE);
	SetWindowLongW(hwnd, GWL_STYLE, style);

	SetWindowPos(hwnd, 0, posx, posy, w, h, SWP_SHOWWINDOW);
	//Tittle bar configuration

	xamlContainer->UpdateLayout();
	desktopSource->Content(*xamlContainer->create());
	return hwnd;
}
