#pragma once
#include "defines.h" // 包含宏定义头文件(已包含了标准头文件)

void ReadMouseInput() {
	ExMessage msg; // 定义一个ExMessage结构体变量msg，用于存储鼠标消息
	peekmessage(&msg, EM_MOUSE | EM_KEY); // 获取鼠标消息和键盘消息
	switch (msg.message) { // 根据消息类型进行处理
	case WM_LBUTTONDOWN: // 鼠标左键按下事件
		for (int i = 0;i < 10;i++) {
			//鼠标在按钮范围内按下时，相应按钮变为按下状态
			if (msg.x >= button[i].x && msg.x <= button[i].x + button[i].width &&
				msg.y >= button[i].y && msg.y <= button[i].y + button[i].height
				&& button[i].state == BUTTON_STATE_UP) {
				button[i].state = BUTTON_STATE_DOWN;
			}

		}
		break;
	case WM_LBUTTONUP:
		//鼠标松开时，若在按钮范围内松开，该按钮变为激活状态，否则所有按钮恢复弹起状态
		for (int i = 0;i < 10;i++) {
			if (msg.x >= button[i].x && msg.x <= button[i].x + button[i].width &&
				msg.y >= button[i].y && msg.y <= button[i].y + button[i].height
				/*&& button[i].state == BUTTON_STATE_DOWN*/) {
				button[i].state = BUTTON_STATE_ACTIVE; // 设置按钮为激活状态
			}
			else {
				button[i].state = BUTTON_STATE_UP; // 恢复按钮为弹起状态
			}
		}

		break;
	}
}

//绘制游戏标题
void DrawTitle() {
	settextstyle(50, 0, _T("黑体")); // 设置字体样式
	setbkmode(TRANSPARENT); //设置背景模式为透明
	settextcolor(WHITE); // 设置文字颜色为白色
	outtextxy(SCREEN_WIDTH / 2 - 100, 150, _T("飞机大战")); // 在屏幕中心绘制标题
}






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
//若开始按钮被激活，则进入游戏准备状态
void StartGame() {
	if (button[0].state == BUTTON_STATE_ACTIVE) {
		game_state = GAME_STATE_READY; // 设置游戏状态为准备状态
	}
}



void menu() {
	//DrawTitle(); // 绘制游戏标题
	//DrawStartButton(); // 绘制开始按钮
	//播放音乐
	if (bgmmain) { // 如果背景音乐存在
		BGMMAIN = BASS_SampleGetChannel(bgmmain, FALSE); // 获取背景音乐通道
		//if (!BASS_ChannelIsActive(BGM)) { // 如果背景音乐未在播放

			// 将背景音乐音量设置为50%
		BASS_ChannelSetAttribute(BGMMAIN, BASS_ATTRIB_VOL, 1.0f);
		BASS_ChannelPlay(BGMMAIN, TRUE); // 播放背景音乐
		//}
	}
	ReadMouseInput(); // 读取鼠标输入
	StartGame(); // 检查是否开始游戏
}