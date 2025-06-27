#pragma once
#include "defines.h" // 包含宏定义头文件(已包含了标准头文件)
#include"login.h"// 包含登录头文件
#include"register.h"// 包含注册头文件

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









//若开始按钮被激活，则进入游戏准备状态
void StartGame() {
	if (button[START].state == BUTTON_STATE_ACTIVE) {
		if(!is_login) { // 如果未登录
			if (MessageBox(NULL, "未登录状态下不会记录成绩\n确定要开始吗？", "提示", MB_YESNO | MB_ICONQUESTION) != IDYES) // 弹出提示框
			{ 
			button[START].state = BUTTON_STATE_UP; // 设置开始按钮状态为弹起
			return; // 返回，不进入游戏准备状态
			}
				
		}
		game_state = GAME_STATE_READY; // 设置游戏状态为准备状态
	}
}
//若登录按钮被激活，则打开登录窗口
void LoginGame() {
	if (button[LOGIN].state == BUTTON_STATE_ACTIVE) {
		// 打开登录窗口的代码
		
		button[LOGIN].state = BUTTON_STATE_UP; // 登录后将登录按钮状态设置为弹起
		userlogin(); // 调用登录函数
	}
}
//若注册按钮被激活，则打开注册窗口
void RegisterGame() {
	if (button[REGISTER].state == BUTTON_STATE_ACTIVE && clock() - back_to_home_time > 1000) {// 确保按钮被点击后至少等待1秒
		// 打开注册窗口的代码
		button[REGISTER].state = BUTTON_STATE_UP; // 注册后将注册按钮状态设置为弹起
		userregister(); // 调用注册函数
	}
	else {
		button[REGISTER].state = BUTTON_STATE_UP; // 如果注册按钮未被激活，则将其状态设置为弹起
	}
}
//若退出登录按钮被激活，则退出登录状态
void LogoffGame() {
	if (button[LOGOFF].state == BUTTON_STATE_ACTIVE && clock() - back_to_home_time > 1000) {// 确保按钮被点击后至少等待1秒
		if (MessageBox(NULL, "确定要退出登录吗？", "退出登录", MB_YESNO | MB_ICONQUESTION) == IDYES) {
			is_login = false; // 设置登录状态为false
			button[LOGOFF].state = BUTTON_STATE_DISABLED; // 禁用退出登录按钮
			button[LOGIN].state = BUTTON_STATE_UP; // 激活登录按钮
			button[REGISTER].state = BUTTON_STATE_UP; // 激活注册按钮
		}
		
	}
	else {
		button[LOGOFF].state = BUTTON_STATE_UP;
	}
}

//若退出按钮被激活，则退出游戏
void MenuExitGame() {
	if (button[EXIT].state == BUTTON_STATE_ACTIVE) {
		exit(0); // 退出游戏
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
	if (!is_login) {
		LoginGame(); // 检查是否登录游戏
		RegisterGame();// 检查是否注册游戏
	} 
	else {
		LogoffGame(); // 检查是否退出登录
	}
	MenuExitGame(); // 检查是否退出游戏
}