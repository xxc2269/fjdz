#define _CRT_SECURE_NO_WARNINGS//禁用安全警告,以免编译器提示使用不安全的函数如strcpy、sprintf等

//导入标准头文件
//#include"includes.h"

//宏定义(内含标准头文件)
#include"defines.h"

//此处导入自定义的头文件
//#include"helloworld.h"//自定义的头文件，包含了helloworld函数的声明(测试)
#include"loadImages.h"//自定义的头文件，包含了加载图片函数的声明
#include"DrawGames.h"//自定义的头文件，包含了绘制游戏界面函数的声明
#include"InitGame.h"//自定义的头文件，包含了初始化游戏函数的声明
#include"UpdateGame.h"//自定义的头文件，包含了更新游戏状态函数的声明
#include"loadSounds.h"//自定义的头文件，包含了加载音效函数的声明

//函数声明

//初始化游戏函数
void init_game(); 
//加载图片函数
void loadimages();
//绘制游戏界面函数
void DrawGame();
//更新游戏状态函数
void UpdateGame(); 

//函数定义


//主函数入口点，使用win32程序，不会弹出控制台窗口
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
	int nShowCmd)
{
	//helloworld();//调用自定义的helloworld函数，输出Hello World!（测试）


	loadimages(); //调用加载图片函数，加载所有需要的图片资源
	loadSounds(); //调用加载音效函数，加载所有需要的音效资源


	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);//初始化图形窗口，设置窗口大小
	//MessageBox(NULL, TEXT("一个简单的Win32应用程序"), TEXT("消息窗口"), MB_OK);//弹出一个消息窗口，显示“一个简单的Win32应用程序”(测试)
	init_game(); //调用初始化游戏函数
	while(1){
		UpdateGame(); //调用更新游戏状态函数，更新游戏状态
		DrawGame(); //调用绘制游戏界面函数，绘制游戏界面
		//Sleep(1); //延时1毫秒，控制游戏帧率（弃用）
	}


	
	return 0;//返回值为0表示程序正常结束

}