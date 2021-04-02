#include <windows.h>
#include <utility>
#include <cstdio>
#include "resource.h"
#include "solve.h"

INT_PTR CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR lpszCmdParam, int nCmdShow) {
//    AllocConsole();
//    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    HWND hWnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

void InitDialog(HWND hWnd) {
    SetWindowTextW(hWnd, L"My Window");
    HWND hEditCtrl = GetDlgItem(hWnd, IDC_EQ_EDIT);
    SetWindowText(hEditCtrl, L"x^2+2x+1");
    SendMessage(hEditCtrl, EM_SETLIMITTEXT, 255, 0);
}

INT_PTR CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_INITDIALOG:
        InitDialog(hWnd);
        break;
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDC_EQ_EDIT && HIWORD(wParam) == EN_CHANGE) {
            wchar_t buf[256];
            HWND hEditCtrl = GetDlgItem(hWnd, IDC_EQ_EDIT);
            GetWindowText(hEditCtrl, buf, 256);
//            wprintf(L"%s\n", buf);
            Roots r;
            HWND hRoot1 = GetDlgItem(hWnd, IDC_ROOT1),
                hRoot2 = GetDlgItem(hWnd, IDC_ROOT2),
                hStatus = GetDlgItem(hWnd, IDC_STATUS);
            if (try_parse_and_solve(buf, r)) {
                if (r.complex) {
                    SetWindowTextW(hStatus, L"complex");
                    swprintf(buf, L"%.4f + %.4fi", r.r1, r.r2);
                    SetWindowTextW(hRoot1, buf);
                    swprintf(buf, L"%.4f - %.4fi", r.r1, r.r2);
                    SetWindowTextW(hRoot2, buf);
                } else {
                    SetWindowTextW(hStatus, L"real");
                    swprintf(buf, L"%.4f", r.r1);
                    SetWindowTextW(hRoot1, buf);
                    swprintf(buf, L"%.4f", r.r2);
                    SetWindowTextW(hRoot2, buf);
                }
            } else {
                SetWindowTextW(hStatus, L"invalid");
                SetWindowTextW(hRoot1, L"");
                SetWindowTextW(hRoot2, L"");
            }
        }
        break;
    default:
        break;
    }
    return 0;
//    return DefDlgProc(hWnd, uMsg, wParam, lParam);
}
