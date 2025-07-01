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

//绘制最终得分
void DrawFinalScore() {
	settextstyle(30, 0, _T("黑体")); // 设置字体样式
	setbkmode(TRANSPARENT); // 设置背景模式为透明
	settextcolor(WHITE); // 设置文字颜色为白色
	char scoreText[50];
	sprintf(scoreText, "最终得分：%d", score); // 格式化得分文本
	outtextxy(SCREEN_WIDTH / 2 - 100, 200, scoreText); // 在屏幕中心绘制得分
}

//显示用户名
void DrawUsername() {
	settextstyle(30, 0, _T("黑体")); // 设置字体样式
	setbkmode(TRANSPARENT); // 设置背景模式为透明
	settextcolor(WHITE); // 设置文字颜色为白色
	outtextxy(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 100, _T("欢迎你，")); // 在屏幕中心绘制用户名提示
	outtextxy(SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2 - 100, USER.username); // 在用户名提示后绘制用户名
}

// 绘制按钮函数
void DrawButton(int idx) {
	COLORREF fillColor = COLOR_BTN_UP;
	switch (button[idx].state) {
	case BUTTON_STATE_UP:      fillColor = COLOR_BTN_UP; break;
	case BUTTON_STATE_HOVER:   fillColor = COLOR_BTN_HOVER; break;
	case BUTTON_STATE_DOWN:    fillColor = COLOR_BTN_DOWN; break;
	case BUTTON_STATE_ACTIVE:  fillColor = COLOR_BTN_ACTIVE; break;
	case BUTTON_STATE_DISABLED:fillColor = COLOR_BTN_DISABLE; break;
	}
	settextstyle(30, 0, _T("黑体"));
	setbkmode(OPAQUE);
	setbkcolor(fillColor);
	setfillcolor(fillColor);
	settextcolor(COLOR_BTN_TEXT);
	rectangle(button[idx].x, button[idx].y, button[idx].x + button[idx].width, button[idx].y + button[idx].height);
	outtextxy(button[idx].x + 50, button[idx].y + 10, button[idx].text);
}