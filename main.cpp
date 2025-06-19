#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<string>
#include<math.h>
#include<time.h>
#include<mmstream.h>
#include<Winuser.h>
#pragma comment(lib,"winmm.lib")
#include"helloworld.h"

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nShowCmd)
{
    helloworld();
    initgraph(1280, 720);
    MessageBox(NULL, TEXT("一个简单的Win32应用程序"), TEXT("消息窗口"), MB_OK);
    return 0;

}