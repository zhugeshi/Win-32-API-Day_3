#include"Fun.h"

int g_status = 0;

//��Ϣ������
//���        ��ϢID          ��������     ��������
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
	case WM_CREATE:       //�����һ�δ�������ʱ����
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
	return DefWindowProc(hWnd, message, wParam, lParam);//Ĭ�ϴ��ڴ�����,��������Ϣ�������ṩĬ�ϵĴ���ʽ
}
//������
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	//ע�ᴰ����
	WNDCLASSEX wc = { 0 };
	
	wc.cbSize = sizeof(WNDCLASSEX);  // ??ȱ����һ�е��³������??

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "MyWindowClass";
	wc.lpfnWndProc = WndProc;  //����Ĵ��ڴ�����������
	wc.hInstance = hInstance;

	RegisterClassEx(&wc);//��������ע�ᵽϵͳ

	//��������
	HWND hWnd = CreateWindowEx(0, "MyWindowClass", "Tetris", WS_OVERLAPPEDWINDOW&~WS_MAXIMIZEBOX&~WS_MINIMIZEBOX&~WS_SIZEBOX, 200, 200, 500, 640, NULL, NULL, hInstance, NULL);
	//��ʾ����
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	//��Ϣѭ��
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
