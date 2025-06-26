#pragma once//用于防止头文件被多次包含
#include"defines.h"//包含宏定义头文件(已包含了标准头文件)
//初始化游戏函数
void init_game() {
	score = 0; //初始化分数为0
	level = 1; //初始化关卡为1
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
		item[i].is_active = false; //设置物品激活状态为false
		item[i].item_type = ITEM_TYPE_SMALL_LIFE; //设置物品类型为小生命球
		item[i].item_size = 10; //设置物品大小
		item[i].item_speed = 0.3; //设置物品移动速度
	}

	start_time = clock(); //记录游戏开始时间
	srand((unsigned)time(NULL)); //设置随机数种子
}

