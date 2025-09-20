#include "mcc.h"
#include "win32helper.h"
#include "rasterizer.h"
#include "render.h"

#include <cassert>

static bool need_resize;
static bool should_exit;
static int resize_width;
static int resize_height;

LRESULT CALLBACK
main_window_procedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	switch (Msg) {
	case WM_SIZE:
		need_resize = true;
		resize_width = LOWORD(lParam);
		resize_height = HIWORD(lParam);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}

	return 0;
}

// real main entry
int APIENTRY
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	int result;
	MSG msg;

	win32_set_thread_name("AR_MAIN");

	rasterizer_initialize();

	while (result = GetMessage(&msg, NULL, NULL, NULL)) {
		assert(result != -1);

		TranslateMessage(&msg);
		DispatchMessage(&msg);

		while (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			switch (msg.message) {
			case WM_QUIT:
				should_exit = true;
				break;
			default:
				break;
			}
		}

		if (should_exit) break;

		if (need_resize) {
			need_resize = false;
			rasterizer_on_resize(resize_width, resize_height);
		}

		rasterizer_begin_frame();
		render_main();
		rasterizer_end_frame();
	}

	rasterizer_shutdown();

	return 0;
}
