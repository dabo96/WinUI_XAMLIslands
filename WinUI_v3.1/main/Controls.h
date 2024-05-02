#pragma once

#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.System.h>
#include <winrt/windows.ui.xaml.hosting.h>
#include <windows.ui.xaml.hosting.desktopwindowxamlsource.h>
#include <winrt/windows.ui.xaml.controls.h>
#include <winrt/Windows.ui.xaml.media.h>

using namespace winrt;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Hosting;


namespace Controls
{
	struct IButton : public Button{
	public:
		IButton(const wchar_t* texto, int posx, int posy);
		Windows::UI::Xaml::Controls::Button create();
	private:
		Button b;
	};

	struct Label : public TextBlock{
	public:
		Label(const wchar_t* texto, int posx, int posy);
		Windows::UI::Xaml::Controls::TextBlock create();
	private:
		TextBlock tb;
	};

	struct TextField : public TextBox {
	public:
		TextField(const wchar_t* texto, int posx, int posy);
		Windows::UI::Xaml::Controls::TextBox create();
	private:
		TextBox tb;
	};

	struct TextArea : public RichEditBox {
	public:
		TextArea(const wchar_t* texto, int posx, int posy);
		Windows::UI::Xaml::Controls::RichEditBox create();
	private:
		RichEditBox reb;
	};

	struct Toolbar : public AppBar {
	public:
		Toolbar(const wchar_t* texto);
		std::shared_ptr<Windows::UI::Xaml::Controls::AppBar> create();
	private:
		std::shared_ptr<Windows::UI::Xaml::Controls::AppBar> toolbar;
		std::shared_ptr<Windows::UI::Xaml::Media::AcrylicBrush> ab;
		std::shared_ptr<Windows::UI::Xaml::Controls::StackPanel> TittleBarPanel;
		TextBlock tb;
	};

	struct Container : public StackPanel{
	public:
		Container();
		std::shared_ptr<Windows::UI::Xaml::Controls::StackPanel> create();
	private:
		std::shared_ptr<Windows::UI::Xaml::Controls::StackPanel> container;
		std::shared_ptr<Windows::UI::Xaml::Media::AcrylicBrush> ab;
		std::shared_ptr<Toolbar> t;
	};

	struct ControlWindow {
	public:
		ControlWindow(const wchar_t* texto, int px, int py, int width, int height, Windows::UI::Xaml::Controls::StackPanel content);
		HWND create(HWND m_hwnd);
		std::shared_ptr<Container> getPanel() { return xamlContainer; }
	private:
		int posx;
		int posy;
		int w;
		int h;
		const wchar_t* t;
		std::shared_ptr<DesktopWindowXamlSource> desktopSource;
		std::shared_ptr<Container> xamlContainer;
		HWND hwnd;
	};
};

