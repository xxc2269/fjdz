#pragma once
#include"defines.h" // 包含宏定义头文件(已包含了标准头文件)

void outputrecords() {
	// 绘制背景
	
	// 设置字体样式
	settextstyle(30, 0, _T("黑体"));
	setbkmode(TRANSPARENT); // 设置背景模式为透明
	settextcolor(WHITE); // 设置文字颜色为黑色
	// 绘制标题
	outtextxy(SCREEN_WIDTH / 2 - 80, 220, "排行榜");
	// 查询所有记录
	
	// 输出记录到屏幕
	for (int i = 0; i < 5; i++) {
		char output[100];
		sprintf(output, "%d.\t%s\t- %d", i + 1, records[i].username, records[i].score);
		outtextxy(SCREEN_WIDTH / 2 - 100, 250 + i * 30, output);
	}

}