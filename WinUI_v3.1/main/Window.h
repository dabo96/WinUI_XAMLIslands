#pragma once

#include "WindowT.h"
#include "Controls.h"
#include "../OpenGL/OpenGL.h"

#include <windowsx.h>
#include <vector>

#include <functional>

struct Window : public WindowT
{
public:
	Window(int width, int height);
	void createWindow(HINSTANCE hInstance, int cmdShow, std::function<void()> f);
	void createWindowWithControlsEnabled(HINSTANCE hInstance, int cmdShow, std::function<void()> f);
	std::shared_ptr<Windows::UI::Xaml::Controls::StackPanel> getStackPanel();
	int loop();
private:
	// Inherited via WindowT
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	HWND createXamlIslands(const wchar_t* texto, int posx, int posy, int width, int height, Windows::UI::Xaml::Controls::StackPanel content);
protected:
	std::shared_ptr<Windows::UI::Xaml::Controls::StackPanel> xamlContainer;
	HWND hWndXamlIsland;
	HWND hWndXamlIsland1;
	std::shared_ptr<DesktopWindowXamlSource> desktopSource;
	std::shared_ptr<Windows::UI::Xaml::Media::AcrylicBrush> ab1;
	//std::vector<DesktopWindowXamlSource> xamlIslands;
private:
	std::shared_ptr<OpenGL> openGLWrapper;
	HDC dc;
	int width, height;
};

