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