#pragma once

#include <Windows.h>
#include <d3d11.h>

extern struct s_rasterizer_global {
	// win32
	HWND wnd;
	// d3d11
	ID3D11Device* device;
	ID3D11DeviceContext* dc;
	IDXGISwapChain* swapchain;

	// view
	long width, height;
	ID3D11RenderTargetView* view;
} g_rasterizer_global;

int 
rasterizer_initialize();

void
rasterizer_create_view();

void
rasterizer_begin_frame();

void
rasterizer_end_frame();

void
rasterizer_release_view();

void
rasterizer_on_resize(int width, int height);

void 
rasterizer_shutdown();