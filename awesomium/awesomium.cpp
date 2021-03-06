#include <windows.h>
#include <d3d9.h>

#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>

// globals
LPDIRECT3D9       g_pDirect3D = NULL;
LPDIRECT3DDEVICE9 g_pDirect3D_Device = NULL;

#define WIDTH   800
#define HEIGHT  600
#define URL     "http://www.google.com"


LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShow) {
	MSG msg;

	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_VREDRAW | CS_HREDRAW | CS_OWNDC,
		WndProc, 0, 0, hInstance, NULL, NULL, (HBRUSH)(COLOR_WINDOW + 1),
		NULL, "DX9_TUTORIAL1_CLASS", NULL };

	RegisterClassEx(&wc);

	HWND hMainWnd = CreateWindow("DX9_TUTORIAL1_CLASS",
		"Iain's DirectX awesomium UI!",
		WS_OVERLAPPEDWINDOW, 100, 100, WIDTH, HEIGHT,
		NULL, NULL, hInstance, NULL);

	// Init the Awesomium objects
	Awesomium::WebCore* webCore = Awesomium::WebCore::Initialize(Awesomium::WebConfig());
	Awesomium::WebView* webView = webCore->CreateWebView(WIDTH, HEIGHT, 0, Awesomium::kWebViewType_Window);
	webView->set_parent_window(hMainWnd);
	webView->LoadURL((const Awesomium::WebURL)Awesomium::WSLit(URL));

	// Wait for our WebView to finish loading
	while (webView->IsLoading()) {
		webCore->Update();
	}

	// Sleep a bit and update once more to give scripts and plugins
	// on the page a chance to finish loading.
	Sleep(300);
	webCore->Update();

	// Init the D3D9 objects
	g_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS PresentParams;
	memset(&PresentParams, 0, sizeof(D3DPRESENT_PARAMETERS));

	PresentParams.Windowed = TRUE;
	PresentParams.SwapEffect = D3DSWAPEFFECT_DISCARD;

	g_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hMainWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &PresentParams,
		&g_pDirect3D_Device);


	ShowWindow(hMainWnd, nShow);
	UpdateWindow(hMainWnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		webCore->Update();
	}

	return(0);
}


LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return(0);
	case WM_PAINT:
		//g_pDirect3D_Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
		//g_pDirect3D_Device->Present(NULL, NULL, NULL, NULL);

		//ValidateRect(hwnd, NULL);
		return(0);
	}

	return(DefWindowProc(hwnd, msg, wParam, lParam));
}