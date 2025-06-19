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
    MessageBox(NULL, TEXT("一个简单的Win32应用程序"), TEXT("消息窗口"), MB_OK);
    return 0;

}