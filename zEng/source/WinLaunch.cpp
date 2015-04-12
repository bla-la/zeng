#include <windows.h>
#include <stdio.h>
#include <Render.h>


LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);




int WINAPI wWinMain(HINSTANCE hInstance,
	HINSTANCE prevInstance,
	LPWSTR cmdLine,
	int cmdShow)
{

	WNDCLASSEX mainWnd = { 0 };
	Render * render = new Render();

	mainWnd.cbSize = sizeof(WNDCLASSEX);
	mainWnd.style = CS_HREDRAW | CS_VREDRAW;
	mainWnd.lpfnWndProc = WinProc;
	mainWnd.hInstance = hInstance;
	mainWnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	mainWnd.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	mainWnd.lpszMenuName = NULL;
	mainWnd.lpszClassName = "zENgMainWindow";

	if (!RegisterClassEx(&mainWnd)){
		MessageBox(
			NULL,
			"RegisterClassEx error",
			"Account Details",
			MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
			);
		return -1;
	}

	RECT rc = {0,0,1280,768};
	AdjustWindowRect(&rc,WS_OVERLAPPEDWINDOW,FALSE);

	HWND hwnd = CreateWindowA("zENgMainWindow","Class",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,
							rc.right-rc.left,rc.bottom-rc.top,NULL,NULL,hInstance,NULL);
	if (!hwnd){
		wchar_t buf[256];
		FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buf, 256, NULL);
		MessageBoxW(
			NULL,
			L"CreateWindow error",
			buf,
			MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
			);
		return -1;
	}

	ShowWindow(hwnd,cmdShow);
	if (render->init(hwnd))
	{
		return 1;
	}

	render->setClearColor(0.6f, 0.6f, 0.6f, 1.0f);



	MSG msg = {0};

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			render->clear();

		}
	}

	delete render;
	return 0;
}




LRESULT CALLBACK WinProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	PAINTSTRUCT paintStruct;
	HDC hdc;


	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd,&paintStruct);
		EndPaint(hWnd,&paintStruct);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd,message,wParam,lParam);
	}
	return 0;
}


