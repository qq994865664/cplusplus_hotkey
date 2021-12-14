// ScreenShot.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "ScreenShot.h"
#include <shellapi.h>

#define MAX_LOADSTRING 100
#define HOTKEY1 1000

// 判断是否重复运行
BOOL IsAlreadyRun()
{
	HANDLE hMutex = NULL;
	hMutex = ::CreateMutex(NULL, FALSE, L"ScreenShotServer");
	if (hMutex)
	{
		if (ERROR_ALREADY_EXISTS == ::GetLastError())
		{
			return TRUE;
		}
	}
	return FALSE;
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	// 判断是否重复运行
	if (IsAlreadyRun())
	{
		return 0;
	}

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LPWSTR* szArgList;
	int argCount;

	szArgList = CommandLineToArgvW(GetCommandLine(), &argCount);
	if (szArgList == NULL)
	{
		return -1;
	}

	LPCWSTR file_path = szArgList[1];
	LPCWSTR cmd_param = szArgList[2];


	if (RegisterHotKey(NULL, HOTKEY1, MOD_ALT | MOD_SHIFT | MOD_NOREPEAT, 'M'))
	{
		OutputDebugString(L"RegisterHotKey");
	}

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (msg.message == WM_HOTKEY)
		{
			switch (LOWORD(msg.wParam))
			{
			case HOTKEY1:
				if (cmd_param == NULL || cmd_param[0] == 0)
					ShellExecute(NULL, L"open", file_path, NULL, NULL, SW_HIDE);
				else
					ShellExecute(NULL, L"open", file_path, cmd_param, NULL, SW_HIDE);
				break;

			default:
				PostQuitMessage(0);
			}
		}
	}
	LocalFree(szArgList);

	UnregisterHotKey(NULL, HOTKEY1);
	return (int)msg.wParam;
}