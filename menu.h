#pragma once
#include "defines.h" // 包含宏定义头文件(已包含了标准头文件)
#include"login.h"// 包含登录头文件
#include"register.h"// 包含注册头文件

void ReadMouseInput() {
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
            } else {
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
            } else {
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
            } else if (button[i].state != BUTTON_STATE_DISABLED) {
                button[i].state = BUTTON_STATE_UP;
            }
        }
        mouseDownIndex = -1;
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
	if (button[REGISTER].state == BUTTON_STATE_ACTIVE ) {// 确保按钮被点击后至少等待1秒
		// 打开注册窗口的代码
		button[REGISTER].state = BUTTON_STATE_UP; // 注册后将注册按钮状态设置为弹起
		userregister(); // 调用注册函数
	}
	//else {
	//	button[REGISTER].state = BUTTON_STATE_UP; // 如果注册按钮未被激活，则将其状态设置为弹起
	//}
}
//若退出登录按钮被激活，则退出登录状态
void LogoffGame() {
	if (button[LOGOFF].state == BUTTON_STATE_ACTIVE ) {// 确保按钮被点击后至少等待1秒
		if (MessageBox(NULL, "确定要退出登录吗？", "退出登录", MB_YESNO | MB_ICONQUESTION) == IDYES) {
			is_login = false; // 设置登录状态为false
			is_auto_login = 0; // 设置自动登录状态为false
			USER.username[0] = '\0'; // 清空用户名
			USER.password[0] = '\0'; // 清空密码
			button[LOGOFF].state = BUTTON_STATE_DISABLED; // 禁用退出登录按钮
			button[LOGIN].state = BUTTON_STATE_UP; // 激活登录按钮
			button[REGISTER].state = BUTTON_STATE_UP; // 激活注册按钮
			record_file = fopen("_RECORD_", "w+"); // 打开记录文件
			fprintf(record_file, "%d %s %s", is_auto_login, USER.username, USER.password); // 写入自动登录状态和用户名密码
		}
		else button[LOGOFF].state = BUTTON_STATE_UP; // 如果用户选择不退出登录，则将退出登录按钮状态设置为弹起
		
	}
	/*else {
		button[LOGOFF].state = BUTTON_STATE_UP;
	}*/
}

//若退出按钮被激活，则退出游戏
void MenuExitGame() {
	if (button[EXIT].state == BUTTON_STATE_ACTIVE) {
		if (MessageBox(NULL, "确定要退出游戏吗？", "退出游戏", MB_YESNO | MB_ICONQUESTION) == IDYES) {
			exit(0); // 退出游戏
		}
		else button[EXIT].state = BUTTON_STATE_UP; // 如果用户选择不退出游戏，则将退出游戏按钮状态设置为弹起
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