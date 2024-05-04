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

void Controls::Label::changeText(const wchar_t* texto)
{
	tb.Text(texto);
}

Controls::IButton::IButton(const wchar_t* texto, int posx, int posy)
{
	TranslateTransform translate;

	translate.X(posx);
	translate.Y(posy);

	//Click function
	//btnCommand = winrt::make<RelayCommand>(f);
	b.Command(IButton::btnCommand);

	b.Content(winrt::box_value(texto));
	b.Background(Windows::UI::Xaml::Media::SolidColorBrush{ Windows::UI::Colors::Blue() });
	b.Click({ this,  Windows::UI::Xaml::RoutedEventHandler(&IButton::onClick) });
}

Windows::UI::Xaml::Input::ICommand Controls::IButton::getBtnCommand()
{
	if (btnCommand == nullptr)
	{
		btnCommand = winrt::make<RelayCommand>([]()
		{
			Windows::UI::Xaml::Controls::ContentDialog msg;
			msg.Content(winrt::box_value(L"prueba"));
			msg.Title(winrt::box_value(L"al fin"));
			msg.CloseButtonText(L"Ok");
			msg.ShowAsync();
		}
		);
	}
	return btnCommand;
}

Windows::UI::Xaml::Controls::Button Controls::IButton::create()
{
	return b;
}

void Controls::IButton::onClick(IInspectable const&,Windows::UI::Xaml::RoutedEventArgs const&)
{
	f();
}
//
//void Controls::IButton::onPress(IInspectable const&)
//{
//
//}
//
void Controls::IButton::setFunction(std::function<void()> function)
{
	f = function;
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

Controls::Toolbar::Toolbar(const wchar_t* texto, int posx, int posy)
{
	TittleBarPanel = std::make_shared<Windows::UI::Xaml::Controls::StackPanel>();
	toolbar = std::make_shared<Windows::UI::Xaml::Controls::AppBar>();
	TranslateTransform translate;

	translate.X(posx);
	translate.Y(posy);

	//Toolbar Brush
	ab = std::make_shared<Windows::UI::Xaml::Media::AcrylicBrush>();
	ab->BackgroundSource(Windows::UI::Xaml::Media::AcrylicBackgroundSource::HostBackdrop);
	ab->TintColor(Windows::UI::Colors::Black());
	ab->FallbackColor(Windows::UI::Colors::DarkGray());
	ab->TintOpacity(0.2);
	
	//Stack Panel that contains the elements of the toolbar
	TittleBarPanel->Background(*ab);
	
	//Texto de la barra de Titulos
	tb.Text(texto);
	tb.RenderTransform(translate);
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

Controls::Container::Container(const wchar_t* texto)
{
	ab = std::make_shared<Windows::UI::Xaml::Media::AcrylicBrush>();
	container = std::make_shared<Windows::UI::Xaml::Controls::StackPanel>();
	t = std::make_shared<Toolbar>(texto, 0, 0);

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

std::shared_ptr<Windows::UI::Xaml::Controls::StackPanel> Controls::Container::getPanel()
{
	return container;
}

Controls::ControlWindow::ControlWindow(const wchar_t* texto, int px, int py, int width, int height)
{
	posx = px;
	posy = py;
	w = width;
	h = height;
	t = texto;

	xamlContainer = std::make_shared<Container>(texto)->getPanel();
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

	xamlContainer->UpdateLayout();
	desktopSource->Content(*xamlContainer);
	return hwnd;
}

Controls::ISlider::ISlider(int posx, int posy, int min, int max, int stepFrequency)
{
	TranslateTransform translate;

	translate.X(posx);
	translate.Y(posy);

	s.RenderTransform(translate);
	s.Minimum(min);
	s.Maximum(max);
	s.StepFrequency(stepFrequency);
}

Slider Controls::ISlider::create()
{
	return Slider();
}


