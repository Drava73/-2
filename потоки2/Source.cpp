#include <Windows.h>
#include <tchar.h>
#include <CommCtrl.h>
#include "resource.h"

HWND hB, hBar;
HANDLE hTimer, Th;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG), NULL, (DLGPROC)DlgProc);
}

DWORD WINAPI Thread(LPVOID lp, HWND hWnd)
{
	DWORD pr = GetPriorityClass(GetCurrentProcess());
	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL)
		// - - -
		HWND hEdit = (HWND)lp;
	while (true)
	{
		TCHAR buff[64];
		short seconds = 120;
		while (seconds != NULL)
		{
			--seconds;
			wsprintf(buff, TEXT("%d left"), seconds);
			SetWindowText(hEdit, buff);
		}
		if (seconds == NULL)
		{
			TerminateThread(Th, NULL);
			CloseHandle(Th);
			EndDialog(hWnd, NULL);
		}
		Sleep(1000);
	}
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_NORMAL)
		return(NULL);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	short step = NULL;
	short score = NULL;
	switch (message)
	{
	case WM_INITDIALOG:
		hB = GetDlgItem(hWnd, IDC_BUTTON);
		hBar = GetDlgItem(hWnd IDC_BAR);
		SendMessage(hBar, PBM_SETRANGE, NULL, MAKELPARAM(NULL, 200));
		SendMessage(hBar, PBM_SETPOS, NULL, NULL);
		SendMessage(hBar, PBM_SETBKCOLOR, NULL, LPARAM(RGB(255, 255, 255)));
		SendMessage(hBar, PBM_SETBARCOLOR, NULL, LPARAM(RGB(NULL, 214, 120)));
		Th = CreateThread(NULL, NULL, Thread, hTimer, NULL, NULL);
	case WM_COMMAND:
		// box 1
		if (LOWORD(wParam) == IDC_RADIO1)
		{
			step++;
			score++;
		}
		else if (LOWORD(wParam) == IDC_RADIO2)
		{
			step++;
		}
		else if (LOWORD(wParam) == IDC_RADIO3)
		{
			step++;
		}
		else
		{
			return(TRUE);
		}
		// box 2
		if (LOWORD(wParam) == IDC_RADIO4)
		{
			step++;
		}
		else if (LOWORD(wParam) == IDC_RADIO5)
		{
			step++;
			score++;
		}
		else if (LOWORD(wParam) == IDC_RADIO6)
		{
			step++;
			score++;
		}
		else
		{
			return(TRUE);
		}
		// - - -
		if (step == 2)
		{
			EnableWindow(hB, TRUE);
		}
		else
		{
			EnableWindow(hB, FALSE);
		}
		// - - -
		if (score == 1)
		{
			SendMessage(hBar, PBM_SETSTEP, 100, NULL);
		}
		else if (score == 2)
		{
			SendMessage(hBar, PBM_SETSTEP, 100, NULL);
		}
		else
		{
			return(TRUE);
		}
		// - - -
		if (LOWORD(wParam) == IDC_BUTTON)
		{
			SuspendThread(Th);
			if (score == 1)
			{
				EndDialog(hWnd, NULL);
				MessageBox(hWnd, TEXT("It was not bad. Score - 1"), TEXT("Box"), MB_OK);
			}
			else if (score == 2)
			{
				EndDialog(hWnd, NULL);
				MessageBox(hWnd, TEXT("It was so good. Score - 2"), TEXT("Box"), MB_OK);
			}
			else
			{
				EndDialog(hWnd, NULL);
				MessageBox(hWnd, TEXT("It was so bad. Score - 0"), TEXT("Box"), MB_OK);
			}
			TerminateThread(Th, NULL);
			CloseHandle(Th);
		}
		return(TRUE);
	case WM_CLOSE:
		TerminateThread(Th, NULL);
		CloseHandle(Th);
		EndDialog(hWnd, NULL);
		return(TRUE);
	}
	return(FALSE);
}

