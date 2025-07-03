#pragma once
#include "defines.h" // 包含宏定义头文件(已包含了标准头文件)



void gamecontinue() {
		game_state = GAME_STATE_PLAYING; // 设置游戏状态为继续状态
		button[CONTINUE].state = BUTTON_STATE_DISABLED; // 禁用继续按钮
		button[RESTART].state = BUTTON_STATE_DISABLED; // 禁用重新开始按钮
		button[EXIT].state = BUTTON_STATE_DISABLED; // 禁用退出按钮
		total_paused_time += clock() - start_paused_time; // 计算总暂停时间
		partly_paused_time = clock() - start_paused_time;// 计算本次暂停时间
		generate_paused_time = partly_paused_time;
		shoot_paused_time = partly_paused_time;
}




//若继续按钮被激活，则进入游戏继续状态
void ContinueGame() {
	if (button[CONTINUE].state == BUTTON_STATE_ACTIVE) {
		gamecontinue(); // 重置游戏状态
		
	}
}

//若重新开始按钮被激活，则进入游戏准备状态
void RestartGame() {
	if (button[RESTART].state == BUTTON_STATE_ACTIVE) {
		if (button[RESTART].state == BUTTON_STATE_ACTIVE) {
			if (MessageBox(NULL, "确定要重新开始吗？\n你将失去当前进度！", "重新开始", MB_YESNO | MB_ICONQUESTION) == IDYES) {
				game_state = GAME_STATE_READY; // 设置游戏状态为准备状态
				button[CONTINUE].state = BUTTON_STATE_DISABLED; // 禁用继续按钮
				button[RESTART].state = BUTTON_STATE_DISABLED; // 禁用重新开始按钮
				button[EXIT].state = BUTTON_STATE_DISABLED; // 禁用退出按钮
			}
			else button[RESTART].state = BUTTON_STATE_UP; // 如果用户选择不重开游戏，则将重开游戏按钮状态设置为弹起
		}

	}
}

//若退出按钮被激活，则退出游戏
void ExitGame() {
	if (button[EXIT].state == BUTTON_STATE_ACTIVE) {
		if (MessageBox(NULL, "确定要退出游戏吗？\n你将失去当前进度！", "退出游戏", MB_YESNO | MB_ICONQUESTION) == IDYES) {
			exit(0); // 退出游戏
		}
		else button[EXIT].state = BUTTON_STATE_UP; // 如果用户选择不退出游戏，则将退出游戏按钮状态设置为弹起
	}
}

//若返回主页按钮被激活，则返回主页
void HomeGame() {
	if (button[HOME].state == BUTTON_STATE_ACTIVE) {
		if (button[HOME].state == BUTTON_STATE_ACTIVE) {
			if (MessageBox(NULL, "确定要返回主页吗？\n你将失去当前进度！", "返回主页", MB_YESNO | MB_ICONQUESTION) == IDYES) {
				game_state = GAME_STATE_MAIN_MENU; // 设置游戏状态为主界面
		level = 1; // 重置关卡为1
		generate_speed = 1; // 重置生成速度为1
		button[CONTINUE].state = BUTTON_STATE_DISABLED; // 禁用继续按钮
		button[RESTART].state = BUTTON_STATE_DISABLED; // 禁用重新开始按钮
		//button[EXIT].state = BUTTON_STATE_DISABLED; // 禁用退出按钮
		button[HOME].state = BUTTON_STATE_DISABLED; // 禁用返回主页按钮
		button[START].state = BUTTON_STATE_UP; // 设置开始按钮状态为弹起
		if(is_login) {
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
			else button[HOME].state = BUTTON_STATE_UP; // 如果用户选择不退出游戏，则将退出游戏按钮状态设置为弹起
		}
		

	}
}

void PauseReadMouseInput() {
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

	case WM_KEYDOWN:
		//按下ESC键时，取消暂停状态
		if (msg.vkcode == VK_ESCAPE) {
			gamecontinue();
		}
	}
}

void pause() {
	//音量降低为原来的20%


	PauseReadMouseInput(); // 读取鼠标输入
	ContinueGame(); // 检查是否继续游戏
	RestartGame(); // 检查是否重新开始游戏
	ExitGame(); // 检查是否退出游戏
	HomeGame(); // 检查是否返回主页
}