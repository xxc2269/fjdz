#pragma once
#include "defines.h" // 包含宏定义头文件(已包含了标准头文件)
#include"add.h"// 包含添加分数的头文件
#include"findAll.h"// 包含查询所有记录的头文件

void OverReadMouseInput() {
	static int mouseDownIndex = -1; // 记录按下时的按钮索引
	ExMessage msg;
	peekmessage(&msg, EM_MOUSE | EM_KEY);

	switch (msg.message) {
	case WM_MOUSEMOVE:
		for (int i = 0; i < 10; i++) {
			// 鼠标在按钮范围内且按钮未禁用
			if (msg.x >= button[i].x && msg.x <= button[i].x + button[i].width &&
				msg.y >= button[i].y && msg.y <= button[i].y + button[i].height &&
				button[i].state != BUTTON_STATE_DISABLED) {
				if (button[i].state != BUTTON_STATE_DOWN) // 按下时不变悬停
					button[i].state = BUTTON_STATE_HOVER;
			}
			else {
				// 鼠标不在按钮上，且不是按下状态，恢复为弹起
				if (button[i].state == BUTTON_STATE_HOVER)
					button[i].state = BUTTON_STATE_UP;
			}
		}
		break;

	case WM_LBUTTONDOWN:
		mouseDownIndex = -1;
		for (int i = 0; i < 10; i++) {
			if (msg.x >= button[i].x && msg.x <= button[i].x + button[i].width &&
				msg.y >= button[i].y && msg.y <= button[i].y + button[i].height &&
				button[i].state == BUTTON_STATE_HOVER &&
				button[i].state != BUTTON_STATE_DISABLED) {
				button[i].state = BUTTON_STATE_DOWN;
				mouseDownIndex = i; // 记录按下的按钮
			}
			else {
				// 其它按钮恢复为弹起
				if (button[i].state == BUTTON_STATE_DOWN)
					button[i].state = BUTTON_STATE_UP;
			}
		}
		break;

	case WM_LBUTTONUP:
		for (int i = 0; i < 10; i++) {
			// 只有鼠标按下和松开都在同一个按钮上才激活
			if (i == mouseDownIndex &&
				msg.x >= button[i].x && msg.x <= button[i].x + button[i].width &&
				msg.y >= button[i].y && msg.y <= button[i].y + button[i].height &&
				button[i].state == BUTTON_STATE_DOWN &&
				button[i].state != BUTTON_STATE_DISABLED) {
				button[i].state = BUTTON_STATE_ACTIVE;
			}
			else if (button[i].state != BUTTON_STATE_DISABLED) {
				button[i].state = BUTTON_STATE_UP;
			}
		}
		mouseDownIndex = -1;
		break;
	}
}






////绘制重新开始按钮
//void DrawRestartButton() {
//	settextstyle(30, 0, _T("黑体")); // 设置字体样式
//	setbkmode(OPAQUE); // 设置背景模式为不透明
//	setbkcolor(BLUE); // 设置按钮背景颜色为蓝色
//	setfillcolor(BLUE); // 设置按钮填充颜色为蓝色
//	settextcolor(WHITE); // 设置文字颜色为白色
//	rectangle(button[RESTART].x, button[RESTART].y, button[RESTART].x + button[RESTART].width, button[RESTART].y + button[RESTART].height); // 绘制按钮边框
//	outtextxy(button[RESTART].x + 50, button[RESTART].y + 10, button[RESTART].text); // 在按钮上绘制文字
//}
////绘制退出按钮
//void DrawExitButton() {
//	settextstyle(30, 0, _T("黑体")); // 设置字体样式
//	setbkmode(OPAQUE); // 设置背景模式为不透明
//	setbkcolor(BLUE); // 设置按钮背景颜色为蓝色
//	setfillcolor(BLUE); // 设置按钮填充颜色为蓝色
//	settextcolor(WHITE); // 设置文字颜色为白色
//	rectangle(button[EXIT].x, button[EXIT].y, button[EXIT].x + button[EXIT].width, button[EXIT].y + button[EXIT].height); // 绘制按钮边框
//	outtextxy(button[EXIT].x + 50, button[EXIT].y + 10, button[EXIT].text); // 在按钮上绘制文字
//}


//若重新开始按钮被激活，则进入游戏准备状态
void OverRestartGame() {
	if (button[RESTART].state == BUTTON_STATE_ACTIVE) {
		game_state = GAME_STATE_READY; // 设置游戏状态为准备状态
		button[CONTINUE].state = BUTTON_STATE_DISABLED; // 禁用继续按钮
		button[RESTART].state = BUTTON_STATE_DISABLED; // 禁用重新开始按钮
		button[EXIT].state = BUTTON_STATE_DISABLED; // 禁用退出按钮
	}
}

//若退出按钮被激活，则退出游戏
void OverExitGame() {
	if (button[EXIT].state == BUTTON_STATE_ACTIVE) {
		if (MessageBox(NULL, "确定要退出游戏吗？", "退出游戏", MB_YESNO | MB_ICONQUESTION) == IDYES) {
			exit(0); // 退出游戏
		}
		else button[EXIT].state = BUTTON_STATE_UP; // 如果用户选择不退出游戏，则将退出游戏按钮状态设置为弹起
	}
}

void OverHomeGame() {
	if (button[HOME].state == BUTTON_STATE_ACTIVE) {
		game_state = GAME_STATE_MAIN_MENU; // 设置游戏状态为主界面
		level = 1; // 重置关卡为1
		generate_speed = 1; // 重置生成速度为1
		button[CONTINUE].state = BUTTON_STATE_DISABLED; // 禁用继续按钮
		button[RESTART].state = BUTTON_STATE_DISABLED; // 禁用重新开始按钮
		//button[EXIT].state = BUTTON_STATE_DISABLED; // 禁用退出按钮
		button[HOME].state = BUTTON_STATE_DISABLED; // 禁用返回主页按钮
		button[START].state = BUTTON_STATE_UP; // 设置开始按钮状态为弹起
		if (is_login) {
			button[LOGOFF].state = BUTTON_STATE_UP; // 设置退出登录按钮状态为弹起
		}
		else {
			button[LOGIN].state = BUTTON_STATE_UP; // 设置登录按钮状态为弹起
			button[REGISTER].state = BUTTON_STATE_UP; // 设置注册按钮状态为弹起
		}
		//停止所有游戏内音乐
		BASS_SampleStop(bgm1); // 停止背景音乐1
		BASS_SampleStop(bgm2); // 停止背景音乐2
		BASS_SampleStop(bgm3); // 停止背景音乐3
		BASS_SampleStop(bgm4); // 停止背景音乐4
		BASS_SampleStop(bgm5); // 停止背景音乐5
		BASS_SampleStop(bgmover); // 停止游戏结束音乐
		back_to_home_time = clock(); // 记录返回主页时间

	}
}

void gameover() {
	//停止所有游戏内音乐
	BASS_SampleStop(bgm1); // 停止背景音乐1
	BASS_SampleStop(bgm2); // 停止背景音乐2
	BASS_SampleStop(bgm3); // 停止背景音乐3
	BASS_SampleStop(bgm4); // 停止背景音乐4
	BASS_SampleStop(bgm5); // 停止背景音乐5
	
	//播放游戏结束音乐
	if (bgmover) { // 如果背景音乐存在
		BGMOVER = BASS_SampleGetChannel(bgmover, FALSE); // 获取背景音乐通道
		//if (!BASS_ChannelIsActive(BGM)) { // 如果背景音乐未在播放

			// 将背景音乐音量设置为70%
		BASS_ChannelSetAttribute(BGMOVER, BASS_ATTRIB_VOL, 0.7f);
		BASS_ChannelPlay(BGMOVER, TRUE); // 播放背景音乐
		//}
	}
	if (is_login && ready_to_insert) {// 如果已登录，则添加分数
		add_score();
		findAll(); // 查询所有记录
		ready_to_insert = false;// 准备插入数据状态设置为false
	}
	OverReadMouseInput(); // 读取鼠标输入
	OverRestartGame(); // 检查是否重新开始游戏
	OverExitGame(); // 检查是否退出游戏
	OverHomeGame(); // 检查是否返回主页
}