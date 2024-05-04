#pragma once

#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.System.h>
#include <winrt/windows.ui.xaml.hosting.h>
#include <windows.ui.xaml.hosting.desktopwindowxamlsource.h>
#include <winrt/windows.ui.xaml.controls.h>
#include <winrt/Windows.ui.xaml.media.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>
#include <winrt/Windows.UI.Xaml.Input.h>

#include <functional>

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Hosting;

struct RelayCommand :implements<RelayCommand, Windows::UI::Xaml::Input::ICommand>
{
	winrt::event<EventHandler<IInspectable>> canExecuteChanged;
	typedef void (*Action)();

	RelayCommand(Action action)
	{
		this->action = action;
	}

	void Execute(IInspectable const& /*parameter*/)
	{
		if (action != nullptr)
		{
			action();
		}
	}

	bool CanExecute(IInspectable const& /*parameter*/)
	{
		return true;
	}

	event_token CanExecuteChanged(EventHandler<IInspectable> const& handler)
	{
		return canExecuteChanged.add(handler);
	}

	void CanExecuteChanged(event_token const& cookie)
	{
		canExecuteChanged.remove(cookie);
	}
private:
	Action action;
};

//struct RelayCommand : implements<RelayCommand, Windows::UI::Xaml::Input::ICommand>
//{
//	winrt::event<EventHandler<IInspectable>> canExecuteChanged;
//
//	RelayCommand(std::function<void(IInspectable const&)> execute)
//	{
//		this->m_execute = execute;
//	}
//
//	void Execute(IInspectable const& parameter) const
//	{
//		m_execute(parameter);
//	}
//
//	bool CanExecute(IInspectable const& parameter) const
//	{
//		// Implementa aquí tu lógica para determinar si el comando puede ejecutarse.
//		return true;
//	}
//
//	event_token CanExecuteChanged(EventHandler<IInspectable> const& handler)
//	{
//		return canExecuteChanged.add(handler);
//	}
//
//	void CanExecuteChanged(event_token const& cookie)
//	{
//		canExecuteChanged.remove(cookie);
//	}
//
//private:
//	std::function<void(IInspectable const&)> m_execute;
//};

namespace Controls
{
	struct IButton : public Button{
	public:
		IButton(const wchar_t* texto, int posx, int posy);
		Windows::UI::Xaml::Controls::Button create();
		Windows::UI::Xaml::Input::ICommand getBtnCommand();
		
		void setFunction(std::function<void()> function);
	protected:
		void onClick(IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const& args);
		//void onPress(IInspectable const&);
	private:
		Button b;
		//winrt::Windows::UI::Xaml::Controls::Button::Click_revoker clickRevoker;
		std::function<void()> f;
		Windows::UI::Xaml::Input::ICommand btnCommand;
	};

	struct Label : public TextBlock{
	public:
		Label(const wchar_t* texto, int posx, int posy);
		Windows::UI::Xaml::Controls::TextBlock create();
		void changeText(const wchar_t* texto);
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
		Toolbar(const wchar_t* texto, int posx, int posy);
		std::shared_ptr<Windows::UI::Xaml::Controls::AppBar> create();
	private:
		std::shared_ptr<Windows::UI::Xaml::Controls::AppBar> toolbar;
		std::shared_ptr<Windows::UI::Xaml::Media::AcrylicBrush> ab;
		std::shared_ptr<Windows::UI::Xaml::Controls::StackPanel> TittleBarPanel;
		TextBlock tb;
	};

	struct Container : public StackPanel{
	public:
		Container(const wchar_t* texto);
		std::shared_ptr<Windows::UI::Xaml::Controls::StackPanel> create();
		std::shared_ptr<Windows::UI::Xaml::Controls::StackPanel> getPanel();
	private:
		std::shared_ptr<Windows::UI::Xaml::Controls::StackPanel> container;
		std::shared_ptr<Windows::UI::Xaml::Media::AcrylicBrush> ab;
		std::shared_ptr<Toolbar> t;
	};

	struct ControlWindow {
	public:
		ControlWindow(const wchar_t* texto, int px, int py, int width, int height);
		HWND create(HWND m_hwnd);
		std::shared_ptr<Windows::UI::Xaml::Controls::StackPanel> getPanel() { return xamlContainer; }
	private:
		int posx;
		int posy;
		int w;
		int h;
		const wchar_t* t;
		std::shared_ptr<DesktopWindowXamlSource> desktopSource;
		std::shared_ptr<Windows::UI::Xaml::Controls::StackPanel> xamlContainer;
		HWND hwnd;
	};

	struct ISlider {
	public:
		ISlider(int posx, int posy, int min, int max, int stepFrequency);
		Slider create();
	private:
		Slider s;
	};
};

