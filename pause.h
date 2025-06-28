#pragma once
#include "defines.h" // 包含宏定义头文件(已包含了标准头文件)

void PauseReadMouseInput() {
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



void gamecontinue() {
	//重置子弹的起始位置
	for (int i = 0;i < BULLET_NUM;i++) {
		bullet[i].start_pos.x = bullet[i].bullet_pos.x; // 设置子弹位置为飞机位置
		bullet[i].start_pos.y = bullet[i].bullet_pos.y; // 设置子弹位置为飞机位置
		bullet[i].generate_time = clock(); // 记录子弹生成时间

	}
	//重置敌机的起始位置
	for (int i = 0;i < ENEMY_MAX_NUM;i++) {
		enemy_plane[i].start_pos.x = enemy_plane[i].plane_pos.x; // 设置敌机位置为飞机位置
		enemy_plane[i].start_pos.y = enemy_plane[i].plane_pos.y; // 设置敌机位置为飞机位置
		enemy_plane[i].generate_time = clock(); // 记录敌机生成时间
	}
	//重置掉落物品的起始位置
	for (int i = 0;i < ITEM_NUM;i++) {
		drop_item[i].start_pos.x = drop_item[i].item_pos.x; // 设置物品位置为飞机位置
		drop_item[i].start_pos.y = drop_item[i].item_pos.y; // 设置物品位置为飞机位置
		drop_item[i].generate_time = clock(); // 记录物品生成时间

	}
	//重置敌机子弹的起始位置
	for (int i = 0;i < ENEMY_MAX_NUM;i++) {
		enemy_bullet[i].start_pos.x = enemy_bullet[i].bullet_pos.x; // 设置敌机子弹位置为飞机位置
		enemy_bullet[i].start_pos.y = enemy_bullet[i].bullet_pos.y; // 设置敌机子弹位置为飞机位置
		enemy_bullet[i].generate_time = clock(); // 记录敌机子弹生成时间
	}
}


//若继续按钮被激活，则进入游戏继续状态
void ContinueGame() {
	if (button[CONTINUE].state == BUTTON_STATE_ACTIVE) {
		gamecontinue(); // 重置游戏状态
		game_state = GAME_STATE_PLAYING; // 设置游戏状态为继续状态
		button[CONTINUE].state = BUTTON_STATE_DISABLED; // 禁用继续按钮
		button[RESTART].state = BUTTON_STATE_DISABLED; // 禁用重新开始按钮
		button[EXIT].state = BUTTON_STATE_DISABLED; // 禁用退出按钮
		total_paused_time += clock() - start_paused_time; // 计算总暂停时间
	}
}

//若重新开始按钮被激活，则进入游戏准备状态
void RestartGame() {
	if (button[RESTART].state == BUTTON_STATE_ACTIVE) {
		game_state = GAME_STATE_READY; // 设置游戏状态为准备状态
		button[CONTINUE].state = BUTTON_STATE_DISABLED; // 禁用继续按钮
		button[RESTART].state = BUTTON_STATE_DISABLED; // 禁用重新开始按钮
		button[EXIT].state = BUTTON_STATE_DISABLED; // 禁用退出按钮
	}
}

//若退出按钮被激活，则退出游戏
void ExitGame() {
	if (button[EXIT].state == BUTTON_STATE_ACTIVE) {
		exit(0); // 退出游戏
	}
}

//若返回主页按钮被激活，则返回主页
void HomeGame() {
	if (button[HOME].state == BUTTON_STATE_ACTIVE) {
		game_state = GAME_STATE_MAIN_MENU; // 设置游戏状态为主界面
		level = 1; // 重置关卡为1
		generate_speed = 1; // 重置生成速度为1
		button[CONTINUE].state = BUTTON_STATE_DISABLED; // 禁用继续按钮
		button[RESTART].state = BUTTON_STATE_DISABLED; // 禁用重新开始按钮
		button[EXIT].state = BUTTON_STATE_DISABLED; // 禁用退出按钮
		button[HOME].state = BUTTON_STATE_DISABLED; // 禁用返回主页按钮
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

void pause() {
	//音量降低为原来的20%


	PauseReadMouseInput(); // 读取鼠标输入
	ContinueGame(); // 检查是否继续游戏
	RestartGame(); // 检查是否重新开始游戏
	ExitGame(); // 检查是否退出游戏
	HomeGame(); // 检查是否返回主页
}