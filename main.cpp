#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include<graphics.h>

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nShowCmd)
{

    initgraph(1280, 720);
    MessageBox(NULL, TEXT("һ���򵥵�Win32Ӧ�ó���"), TEXT("��Ϣ����"), MB_OK);
    return 0;

}