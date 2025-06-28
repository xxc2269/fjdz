#pragma once//用于防止头文件被多次包含
#include"defines.h"//包含宏定义头文件(已包含了标准头文件)
//初始化游戏函数
void init_game() {
	score = 0; //初始化分数为0
	level = 1; //初始化关卡为1
	generate_count = 0; //初始化生成计数为0
	generate_speed = 1; //初始化生成速度为1
	my_plane.plane_pos.x = SCREEN_WIDTH / 2 - PLANE_SIZE / 2; //设置飞机初始位置为屏幕中心
	my_plane.plane_pos.y = SCREEN_HEIGHT - PLANE_SIZE; //设置飞机初始位置为屏幕底部
	my_plane.speed = PLANE_SPEED; //设置飞机速度
	my_plane.bullet_num = 0; //设置子弹数量
	my_plane.bullet_speed = 5.0; //设置子弹速度
	my_plane.life = 100; //设置飞机生命值
	my_plane.maxlife = 100; //设置飞机最大生命值
	my_plane.size = PLANE_SIZE; //设置飞机大小
	my_plane.height = PLANE_SIZE; //设置飞机高度
	my_plane.power = 0; //设置飞机火力
	my_plane.grade = 0; //设置飞机等级
	my_plane.endurance = 100; //设置飞机耐久度
	my_plane.max_endurance = 100; //设置飞机最大耐久度
	my_plane.plane_state = PLANE_STATE_NORMAL; //设置飞机状态为正常


	//初始化敌机相关变量
	enemy_num = 0; //初始化敌机数量为0
	for (int i = 0; i < ENEMY_MAX_NUM; i++) { //初始化敌机
		enemy_plane[i].is_alive = false; //设置敌机存活状态为false
		enemy_plane[i].plane_type = ENEMY_TYPE_NORMAL; //设置敌机类型为普通敌机
	}
	for (int i = 0; i < BULLET_NUM; i++) { //初始化子弹
		bullet[i].is_active = false; //设置子弹激活状态为false
		bullet[i].bullet_type = BULLET_TYPE_NORMAL; //设置子弹类型为普通子弹
		bullet[i].bullet_damage = 10; //设置子弹伤害
		bullet[i].bullet_size = 50; //设置子弹大小
	}

	//初始化收集物品
	for (int i = 0; i < ITEM_NUM; i++) { //初始化收集物品
		drop_item[i].is_active = false; //设置物品激活状态为false
		drop_item[i].item_type = ITEM_TYPE_SMALL_LIFE; //设置物品类型为小生命球
		drop_item[i].item_size = 10; //设置物品大小
		drop_item[i].item_speed = 0.3; //设置物品移动速度
	}

	start_time = clock(); //记录游戏开始时间
	start_paused_time = clock(); //记录上次暂停时间
	total_paused_time = 0; //初始化暂停时间为0
	last_complete_time = clock(); //记录上次通关时间
	boss_is_alive = false; //BOSS是否存活
	srand((unsigned)time(NULL)); //设置随机数种子


	button[0] = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 150, 200, 50, "开始游戏" }; // 定义开始按钮
	button[1] = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 200, 100, 50, "登录" }; // 定义登录按钮
	button[2] = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 250, 200, 50, "注册" }; // 定义注册按钮
	button[3] = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 250, 200, 50, "退出登录" , BUTTON_STATE_DISABLED }; // 定义退出登录按钮
	button[4] = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 150, 200, 50, "继续" ,BUTTON_STATE_DISABLED }; // 定义继续按钮
	button[5] = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 300, 200, 50, "退出游戏"  }; // 定义退出按钮
	button[6] = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 200, 200, 50, "重新开始" ,BUTTON_STATE_DISABLED }; // 定义重新开始按钮
	button[7] = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 250, 200, 50, "返回主页" ,BUTTON_STATE_DISABLED }; // 定义排行榜按钮

	//若为准备状态，开始游戏
	if (game_state == GAME_STATE_READY) {
		BASS_SampleStop(bgmmain); // 停止背景音乐
		BASS_SampleStop(bgmover); // 停止游戏结束音乐
		//BASS_SampleFree(bgmmain); // 释放背景音乐资源
		game_state = GAME_STATE_PLAYING; //将游戏状态设置为进行中
		button[START].state = BUTTON_STATE_DISABLED; // 禁用开始按钮
		button[LOGIN].state = BUTTON_STATE_DISABLED; // 禁用登录按钮
		button[REGISTER].state = BUTTON_STATE_DISABLED; // 禁用注册按钮
		button[LOGOFF].state = BUTTON_STATE_DISABLED; // 禁用退出登录按钮
		button[EXIT].state = BUTTON_STATE_DISABLED; // 禁用退出按钮
		
	}
}

