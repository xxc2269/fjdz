#pragma once
#include"defines.h" // 包含宏定义头文件(已包含了标准头文件)


//绘制游戏标题
void DrawTitle() {
	settextstyle(50, 0, _T("黑体")); // 设置字体样式
	setbkmode(TRANSPARENT); //设置背景模式为透明
	settextcolor(WHITE); // 设置文字颜色为白色
	outtextxy(SCREEN_WIDTH / 2 - 100, 150, _T("飞机大战")); // 在屏幕中心绘制标题
}


//绘制暂停字样
void DrawPauseTitle() {
	settextstyle(50, 0, _T("黑体")); // 设置字体样式
	setbkmode(TRANSPARENT); //设置背景模式为透明
	settextcolor(WHITE); // 设置文字颜色为白色
	outtextxy(SCREEN_WIDTH / 2 - 100, 150, _T("暂   停")); // 在屏幕中心绘制标题
}


//绘制绘制游戏结束字样
void DrawOverTitle() {
	settextstyle(50, 0, _T("黑体")); // 设置字体样式
	setbkmode(TRANSPARENT); //设置背景模式为透明
	settextcolor(WHITE); // 设置文字颜色为白色
	outtextxy(SCREEN_WIDTH / 2 - 100, 150, _T("游戏结束")); // 在屏幕中心绘制标题
}


// 绘制按钮函数

//绘制开始按钮
void DrawStartButton() {

	settextstyle(30, 0, _T("黑体")); // 设置字体样式
	//setbkmode(TRANSPARENT); //设置背景模式为透明
	setbkmode(OPAQUE); // 设置背景模式为不透明
	setbkcolor(BLUE); // 设置按钮背景颜色为蓝色
	setfillcolor(BLUE); // 设置按钮填充颜色为蓝色
	settextcolor(WHITE); // 设置文字颜色为白色
	rectangle(button[0].x, button[0].y, button[0].x + button[0].width, button[0].y + button[0].height); // 绘制按钮边框
	outtextxy(button[0].x + 50, button[0].y + 10, button[0].text); // 在按钮上绘制文字
}

//绘制注册按钮
void DrawRegisterButton() {
	settextstyle(30, 0, _T("黑体")); // 设置字体样式
	setbkmode(OPAQUE); // 设置背景模式为不透明
	setbkcolor(BLUE); // 设置按钮背景颜色为蓝色
	setfillcolor(BLUE); // 设置按钮填充颜色为蓝色
	settextcolor(WHITE); // 设置文字颜色为白色
	rectangle(button[REGISTER].x, button[REGISTER].y, button[REGISTER].x + button[REGISTER].width, button[REGISTER].y + button[REGISTER].height); // 绘制按钮边框
	outtextxy(button[REGISTER].x + 50, button[REGISTER].y + 10, button[REGISTER].text); // 在按钮上绘制文字
}
//绘制登录按钮
void DrawLoginButton() {
	settextstyle(30, 0, _T("黑体")); // 设置字体样式
	setbkmode(OPAQUE); // 设置背景模式为不透明
	setbkcolor(BLUE); // 设置按钮背景颜色为蓝色
	setfillcolor(BLUE); // 设置按钮填充颜色为蓝色
	settextcolor(WHITE); // 设置文字颜色为白色
	rectangle(button[LOGIN].x, button[LOGIN].y, button[LOGIN].x + button[LOGIN].width, button[LOGIN].y + button[LOGIN].height); // 绘制按钮边框
	outtextxy(button[LOGIN].x + 50, button[LOGIN].y + 10, button[LOGIN].text); // 在按钮上绘制文字
}

//若已登录，显示用户名和退出登录按钮
void DrawLogoffButton() {
	settextstyle(30, 0, _T("黑体")); // 设置字体样式
	setbkmode(OPAQUE); // 设置背景模式为不透明
	setbkcolor(BLUE); // 设置按钮背景颜色为蓝色
	setfillcolor(BLUE); // 设置按钮填充颜色为蓝色
	settextcolor(WHITE); // 设置文字颜色为白色
	rectangle(button[LOGOFF].x, button[LOGOFF].y, button[LOGOFF].x + button[LOGOFF].width, button[LOGOFF].y + button[LOGOFF].height); // 绘制按钮边框
	outtextxy(button[LOGOFF].x + 50, button[LOGOFF].y + 10, button[LOGOFF].text); // 在按钮上绘制文字
}

//显示用户名
void DrawUsername() {
	settextstyle(30, 0, _T("黑体")); // 设置字体样式
	setbkmode(TRANSPARENT); // 设置背景模式为透明
	settextcolor(WHITE); // 设置文字颜色为白色
	outtextxy(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 100, _T("欢迎你，")); // 在屏幕中心绘制用户名提示
	outtextxy(SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2 - 100, USER.username); // 在用户名提示后绘制用户名
}

//绘制继续按钮
void DrawContinueButton() {
	settextstyle(30, 0, _T("黑体")); // 设置字体样式
	setbkmode(OPAQUE); // 设置背景模式为不透明
	setbkcolor(BLUE); // 设置按钮背景颜色为蓝色
	setfillcolor(BLUE); // 设置按钮填充颜色为蓝色
	settextcolor(WHITE); // 设置文字颜色为白色
	rectangle(button[CONTINUE].x, button[CONTINUE].y, button[CONTINUE].x + button[CONTINUE].width, button[CONTINUE].y + button[CONTINUE].height); // 绘制按钮边框
	outtextxy(button[CONTINUE].x + 50, button[CONTINUE].y + 10, button[CONTINUE].text); // 在按钮上绘制文字
}
//绘制重新开始按钮
void DrawRestartButton() {
	settextstyle(30, 0, _T("黑体")); // 设置字体样式
	setbkmode(OPAQUE); // 设置背景模式为不透明
	setbkcolor(BLUE); // 设置按钮背景颜色为蓝色
	setfillcolor(BLUE); // 设置按钮填充颜色为蓝色
	settextcolor(WHITE); // 设置文字颜色为白色
	rectangle(button[RESTART].x, button[RESTART].y, button[RESTART].x + button[RESTART].width, button[RESTART].y + button[RESTART].height); // 绘制按钮边框
	outtextxy(button[RESTART].x + 50, button[RESTART].y + 10, button[RESTART].text); // 在按钮上绘制文字
}
//绘制退出按钮
void DrawExitButton() {
	settextstyle(30, 0, _T("黑体")); // 设置字体样式
	setbkmode(OPAQUE); // 设置背景模式为不透明
	setbkcolor(BLUE); // 设置按钮背景颜色为蓝色
	setfillcolor(BLUE); // 设置按钮填充颜色为蓝色
	settextcolor(WHITE); // 设置文字颜色为白色
	rectangle(button[EXIT].x, button[EXIT].y, button[EXIT].x + button[EXIT].width, button[EXIT].y + button[EXIT].height); // 绘制按钮边框
	outtextxy(button[EXIT].x + 50, button[EXIT].y + 10, button[EXIT].text); // 在按钮上绘制文字
}
//绘制返回主页按钮
void DrawHomeButton() {
	settextstyle(30, 0, _T("黑体")); // 设置字体样式
	setbkmode(OPAQUE); // 设置背景模式为不透明
	setbkcolor(BLUE); // 设置按钮背景颜色为蓝色
	setfillcolor(BLUE); // 设置按钮填充颜色为蓝色
	settextcolor(WHITE); // 设置文字颜色为白色
	rectangle(button[HOME].x, button[HOME].y, button[HOME].x + button[HOME].width, button[HOME].y + button[HOME].height); // 绘制按钮边框
	outtextxy(button[HOME].x + 50, button[HOME].y + 10, button[HOME].text); // 在按钮上绘制文字
}
