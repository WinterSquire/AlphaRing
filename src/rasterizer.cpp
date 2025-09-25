#include "rasterizer.h"

#include <cassert>

#include <imgui.h>
#include <imgui_internal.h>
#include <backends/imgui_impl_win32.h>
#include <backends/imgui_impl_dx11.h>

#define DEFWIDTH 400
#define DEFHEIGHT 240
#define CLSNAME TEXT("ARC")
#define WNDNAME TEXT("AR")

s_rasterizer_global g_rasterizer_global;

extern IMGUI_IMPL_API LRESULT
ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

extern LRESULT CALLBACK
main_window_procedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

static LRESULT CALLBACK
window_procedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	CallWindowProc(ImGui_ImplWin32_WndProcHandler, hWnd, Msg, wParam, lParam);
	return CallWindowProc(main_window_procedure, hWnd, Msg, wParam, lParam);
}

static D3D_FEATURE_LEVEL g_fl[]{
	D3D_FEATURE_LEVEL_11_0
};

static HWND g_parent_window = NULL;

static BOOL CALLBACK 
window_enum_procedure(HWND hWnd, LPARAM lParam) {
	static auto current_process_id = GetCurrentProcessId();
	DWORD window_process_id;

	GetWindowThreadProcessId(hWnd, &window_process_id);

	if (window_process_id != current_process_id || !IsWindowVisible(hWnd)) {
		return true;
	}

	g_parent_window = hWnd;

	return false;
}

int 
rasterizer_initialize() {
	int result = 0;
	auto instance = GetModuleHandle(NULL);

	WNDCLASSEX wc{
		.cbSize = sizeof(wc),
		.style = CS_VREDRAW | CS_HREDRAW,
		.lpfnWndProc = window_procedure,
		.hInstance = instance,
		.lpszClassName = CLSNAME,
	};

	auto cls = RegisterClassEx(&wc);

	assert(cls);

	EnumWindows(window_enum_procedure, NULL);

	auto window_type = g_parent_window != NULL ? WS_CHILD : WS_OVERLAPPEDWINDOW;

	auto hwnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		CLSNAME,
		WNDNAME,
		WS_VISIBLE | WS_SIZEBOX | window_type,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		DEFWIDTH,
		DEFHEIGHT,
		g_parent_window,
		nullptr,
		instance,
		nullptr
	);

	assert((result = GetLastError(), hwnd != NULL));

	// d3d11
	DXGI_SWAP_CHAIN_DESC sd{
		.BufferDesc = {
			.Width = DEFWIDTH,
			.Height = DEFHEIGHT,
			.RefreshRate = {
				.Numerator = 60,
				.Denominator = 1,
			},
			.Format = DXGI_FORMAT_R8G8B8A8_UNORM,
		},
		.SampleDesc = {
			.Count = 1,
			.Quality = 0,
		},
		.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT,
		.BufferCount = 1,
		.OutputWindow = hwnd,
		.Windowed = 1,
	};

	auto hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		g_fl,
		_countof(g_fl),
		D3D11_SDK_VERSION,
		&sd,
		&g_rasterizer_global.swapchain,
		&g_rasterizer_global.device,
		NULL,
		&g_rasterizer_global.dc
	);

	assert(SUCCEEDED(result = hr));

	rasterizer_create_view();

	// imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	auto& io = ImGui::GetIO();

	io.ConfigFlags |= 
		ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad;

	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(g_rasterizer_global.device, g_rasterizer_global.dc);

	g_rasterizer_global.wnd = hwnd;

	return result;
}

void 
rasterizer_begin_frame() {
	ImGui_ImplWin32_NewFrame();
	ImGui_ImplDX11_NewFrame();
	ImGui::NewFrame();
}

void 
rasterizer_end_frame() {
	g_rasterizer_global.dc->OMSetRenderTargets(1, &g_rasterizer_global.view, NULL);
	ImGui_ImplDX11_RenderDrawData((ImGui::EndFrame(), ImGui::Render(), ImGui::GetDrawData()));
	g_rasterizer_global.swapchain->Present(0, 0);
}

void
rasterizer_create_view() {
	ID3D11Texture2D* buffer; 
	D3D11_TEXTURE2D_DESC buffer_desc;

	g_rasterizer_global.swapchain->GetBuffer(0, IID_PPV_ARGS(&buffer));
	g_rasterizer_global.device->CreateRenderTargetView(buffer, NULL, &g_rasterizer_global.view);
	buffer->Release();
}

void
rasterizer_release_view() {
	g_rasterizer_global.view->Release();
}

void
rasterizer_on_resize(int width, int height) {
	rasterizer_release_view();
	g_rasterizer_global.swapchain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);
	g_rasterizer_global.width = width;
	g_rasterizer_global.height = height;
	rasterizer_create_view();
}

void 
rasterizer_shutdown() {
	rasterizer_release_view();
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();

	g_rasterizer_global.swapchain->Release();
	g_rasterizer_global.dc->Release();
	g_rasterizer_global.device->Release();
}