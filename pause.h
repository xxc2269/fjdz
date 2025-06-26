#pragma once
#include "defines.h" // 包含宏定义头文件(已包含了标准头文件)

//void ReadMouseInput() {
//	ExMessage msg; // 定义一个ExMessage结构体变量msg，用于存储鼠标消息
//	peekmessage(&msg, EM_MOUSE | EM_KEY); // 获取鼠标消息和键盘消息
//	switch (msg.message) { // 根据消息类型进行处理
//	case WM_LBUTTONDOWN: // 鼠标左键按下事件
//		for (int i = 0;i < 10;i++) {
//			//鼠标在按钮范围内按下时，相应按钮变为按下状态
//			if (msg.x >= button[i].x && msg.x <= button[i].x + button[i].width &&
//				msg.y >= button[i].y && msg.y <= button[i].y + button[i].height
//				&& button[i].state == BUTTON_STATE_UP) {
//				button[i].state = BUTTON_STATE_DOWN;
//			}
//
//		}
//		break;
//	case WM_LBUTTONUP:
//		//鼠标松开时，若在按钮范围内松开，该按钮变为激活状态，否则所有按钮恢复弹起状态
//		for (int i = 0;i < 10;i++) {
//			if (msg.x >= button[i].x && msg.x <= button[i].x + button[i].width &&
//				msg.y >= button[i].y && msg.y <= button[i].y + button[i].height
//				/*&& button[i].state == BUTTON_STATE_DOWN*/) {
//				button[i].state = BUTTON_STATE_ACTIVE; // 设置按钮为激活状态
//			}
//			else {
//				button[i].state = BUTTON_STATE_UP; // 恢复按钮为弹起状态
//			}
//		}
//
//		break;
//	}
//}

//绘制绘制暂停字样
void DrawPauseTitle() {
	settextstyle(50, 0, _T("黑体")); // 设置字体样式
	setbkmode(TRANSPARENT); //设置背景模式为透明
	settextcolor(WHITE); // 设置文字颜色为白色
	outtextxy(SCREEN_WIDTH / 2 - 100, 150, _T("暂   停")); // 在屏幕中心绘制标题
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

//若继续按钮被激活，则进入游戏继续状态
void ContinueGame() {
	if (button[CONTINUE].state == BUTTON_STATE_ACTIVE) {
		gamecontinue(); // 重置游戏状态
		game_state = GAME_STATE_PLAYING; // 设置游戏状态为继续状态
		button[CONTINUE].state = BUTTON_STATE_DISABLED; // 禁用继续按钮
		button[RESTART].state = BUTTON_STATE_DISABLED; // 禁用重新开始按钮
		button[EXIT].state = BUTTON_STATE_DISABLED; // 禁用退出按钮
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

void pause() {
	//音量降低为原来的20%
	BASS_ChannelSetAttribute(BGM1, BASS_ATTRIB_VOL, 0.02f); // 设置背景音乐音量为20%
	BASS_ChannelSetAttribute(BGM2, BASS_ATTRIB_VOL, 0.02f); // 设置背景音乐音量为20%
	BASS_ChannelSetAttribute(BGM3, BASS_ATTRIB_VOL, 0.02f); // 设置背景音乐音量为20%
	BASS_ChannelSetAttribute(BGM4, BASS_ATTRIB_VOL, 0.02f); // 设置背景音乐音量为20%
	BASS_ChannelSetAttribute(BGM5, BASS_ATTRIB_VOL, 0.02f); // 设置背景音乐音量为20%

	ReadMouseInput(); // 读取鼠标输入
	ContinueGame(); // 检查是否继续游戏
	RestartGame(); // 检查是否重新开始游戏
	ExitGame(); // 检查是否退出游戏
}