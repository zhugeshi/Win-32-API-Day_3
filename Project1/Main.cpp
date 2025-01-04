#include"Fun.h"

int g_status = 0;

//消息处理函数
//句柄        消息ID          附带参数     附带参数
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message) {
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_RETURN:
			if (g_status == 0) {
				SetTimer(hWnd, ID_DOWN_TIMER, 500, NULL);
				g_status = 1;
			}
			break;
		case VK_LEFT:
			LeftMove(hWnd);
			break;
		case VK_RIGHT:
			RightMove(hWnd);
			break;
		case VK_UP:
			break;
		case VK_DOWN:
			DownMove(hWnd);
			break;
		case VK_SPACE:
			onChangeProc(hWnd);
			break;
		}
	case WM_TIMER:
		switch (wParam) {
		case ID_DOWN_TIMER:
			OnTimer(hWnd);
			break;
		}
		break;
	case WM_CREATE:       //程序第一次创建窗口时调用
		ReadHighestScore();
		OnCreate();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		OnPaint(hdc, &ps);
		OnPaintText(hdc,&ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);//默认窗口处理函数,给各种消息处理函数提供默认的处理方式
}
//主函数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	//注册窗口类
	WNDCLASSEX wc = { 0 };
	
	wc.cbSize = sizeof(WNDCLASSEX);  // ??缺少这一行导致程序崩溃??

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "MyWindowClass";
	wc.lpfnWndProc = WndProc;  //保存的窗口处理函数的名字
	wc.hInstance = hInstance;

	RegisterClassEx(&wc);//将窗口类注册到系统

	//创建窗口
	HWND hWnd = CreateWindowEx(0, "MyWindowClass", "Tetris", WS_OVERLAPPEDWINDOW&~WS_MAXIMIZEBOX&~WS_MINIMIZEBOX&~WS_SIZEBOX, 200, 200, 500, 640, NULL, NULL, hInstance, NULL);
	//显示窗口
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	//消息循环
	MSG msg = { 0 };
	/*typedef struct tagMSG {
	HWND        hwnd;
	UINT        message;
	WPARAM      wParam;
	LPARAM      lParam;
	DWORD       time;
	POINT       pt;
#ifdef _MAC
	DWORD       lPrivate;
#endif
} MSG, *PMSG, NEAR *NPMSG, FAR *LPMSG;*/
	while (GetMessage(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
	}
	return 0;
}
