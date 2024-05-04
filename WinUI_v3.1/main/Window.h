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

	int loop();
private:
	// Inherited via WindowT
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
protected:
	HWND hWndXamlIsland;
	HWND hWndXamlIsland1;
private:
	std::shared_ptr<OpenGL> openGLWrapper;
	HDC dc;
	int width, height;
};

