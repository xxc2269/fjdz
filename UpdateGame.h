#pragma once//用于防止头文件被多次包含
#include"defines.h"//包含宏定义头文件(已包含了标准头文件)

//函数声明
void control_plane(); //控制飞机函数
void check_plane_state(); //检查飞机状态函数
void shoot_bullet(); //发射子弹函数
void generate_enemy(); //生成敌机函数
void generate_boss(); //生成BOSS函数
void generate_drop_item(int plane_type,POS plan_pos); //生成物品函数
void enemy_shoot_bullet(); //生成敌机子弹函数
//void generate_laser(); //生成激光函数(未实现)
//void generate_mega_bullet(); //生成无双子弹函数(未实现)

//处理暂停事件（重置所有子弹、飞机、收集物的起始位置）
void gamepaused() {
	////重置子弹的起始位置
	//for (int i = 0;i < BULLET_NUM;i++) {
	//	bullet[i].start_pos.x = bullet[i].bullet_pos.x; // 设置子弹位置为飞机位置
	//	bullet[i].start_pos.y = bullet[i].bullet_pos.y; // 设置子弹位置为飞机位置
	//	bullet[i].generate_time = clock(); // 记录子弹生成时间

	//}
	////重置敌机的起始位置
	//for (int i = 0;i < ENEMY_MAX_NUM;i++) {
	//	enemy_plane[i].start_pos.x = enemy_plane[i].plane_pos.x; // 设置敌机位置为飞机位置
	//	enemy_plane[i].start_pos.y = enemy_plane[i].plane_pos.y; // 设置敌机位置为飞机位置
	//	enemy_plane[i].generate_time = clock(); // 记录敌机生成时间
	//}
	////重置掉落物品的起始位置
	//for (int i = 0;i < ITEM_NUM;i++) {
	//	drop_item[i].start_pos.x = drop_item[i].item_pos.x; // 设置物品位置为飞机位置
	//	drop_item[i].start_pos.y = drop_item[i].item_pos.y; // 设置物品位置为飞机位置
	//	drop_item[i].generate_time = clock(); // 记录物品生成时间
	//	
	//}
	////重置敌机子弹的起始位置
	//for (int i = 0;i < ENEMY_MAX_NUM;i++) {
	//	enemy_bullet[i].start_pos.x = enemy_bullet[i].bullet_pos.x; // 设置敌机子弹位置为飞机位置
	//	enemy_bullet[i].start_pos.y = enemy_bullet[i].bullet_pos.y; // 设置敌机子弹位置为飞机位置
	//	enemy_bullet[i].generate_time = clock(); // 记录敌机子弹生成时间
	//}
	start_paused_time = clock(); // 记录暂停开始时间
	//降低背景音乐音量
	BASS_ChannelSetAttribute(BGM1, BASS_ATTRIB_VOL, 0.02f); // 设置背景音乐音量为20%
	BASS_ChannelSetAttribute(BGM2, BASS_ATTRIB_VOL, 0.02f); // 设置背景音乐音量为20%
	BASS_ChannelSetAttribute(BGM3, BASS_ATTRIB_VOL, 0.02f); // 设置背景音乐音量为20%
	BASS_ChannelSetAttribute(BGM4, BASS_ATTRIB_VOL, 0.02f); // 设置背景音乐音量为20%
	BASS_ChannelSetAttribute(BGM5, BASS_ATTRIB_VOL, 0.02f); // 设置背景音乐音量为20%
}

//控制
void control_plane() {
	// 此处可以添加更新游戏状态的逻辑，例如处理飞机移动、子弹发射、敌机生成等
	// 以下为一个备选方案：用键盘输入控制飞机移动
	//例如，处理飞机移动
	//if (GetAsyncKeyState(VK_LEFT)) { // 如果按下左键
	//	my_plane.plane_pos.x -= my_plane.speed; // 向左移动
	//}
	//if (GetAsyncKeyState(VK_RIGHT)) { // 如果按下右键
	//	my_plane.plane_pos.x += my_plane.speed; // 向右移动
	//}
	//if (GetAsyncKeyState(VK_UP)) { // 如果按下上键
	//	my_plane.plane_pos.y -= my_plane.speed; // 向上移动
	//}
	//if (GetAsyncKeyState(VK_DOWN)) { // 如果按下下键
	//	my_plane.plane_pos.y += my_plane.speed; // 向下移动
	//}
	//// 确保飞机不超出屏幕边界
	//if (my_plane.plane_pos.x < 0) {
	//	my_plane.plane_pos.x = 0;
	//}
	//if (my_plane.plane_pos.x > SCREEN_WIDTH - PLANE_SIZE) {
	//	my_plane.plane_pos.x = SCREEN_WIDTH - PLANE_SIZE;
	//}
	//if (my_plane.plane_pos.y < 0) {
	//	my_plane.plane_pos.y = 0;
	//}
	//if (my_plane.plane_pos.y > SCREEN_HEIGHT - PLANE_SIZE) {
	//	my_plane.plane_pos.y = SCREEN_HEIGHT - PLANE_SIZE;
	//}

	//以下是另一个方案：使用鼠标输入控制飞机移动
	ExMessage msg; // 定义一个ExMessage结构体变量msg，用于存储鼠标消息，用于处理鼠标输入
	peekmessage(&msg, EM_MOUSE | EM_KEY); // 获取鼠标消息和键盘消息
	switch (msg.message) { // 根据消息类型进行处理
	case WM_MOUSEMOVE:
		// 鼠标移动事件
		my_plane.plane_pos.x = msg.x; // 设置飞机位置为鼠标位置
		my_plane.plane_pos.y = msg.y; // 设置飞机位置为鼠标位置
		break;
	case WM_LBUTTONDOWN:
		// 鼠标左键按下事件
		if (my_plane.plane_state == PLANE_STATE_NORMAL) { // 如果飞机状态为正常
			my_plane.plane_state = PLANE_STATE_SHOOTING; // 切换到射击状态
		}
		else if (my_plane.plane_state == PLANE_STATE_MEGA_NORMAL) {
			my_plane.plane_state = PLANE_STATE_MEGA_SHOOTING;
		}
		break;
	case WM_LBUTTONUP:
		// 鼠标左键松开事件
		if (my_plane.plane_state == PLANE_STATE_SHOOTING) { // 如果飞机状态为射击
			my_plane.plane_state = PLANE_STATE_NORMAL; // 切换到正常状态
		}
		else if (my_plane.plane_state == PLANE_STATE_MEGA_SHOOTING) {
			my_plane.plane_state = PLANE_STATE_MEGA_NORMAL;
		}
		break;

	case WM_RBUTTONDOWN:
		// 鼠标右键按下事件
		if (my_plane.plane_state == PLANE_STATE_NORMAL && !mega_bullet[0].is_active) { // 如果飞机状态为正常
			start_charge_time = clock(); // 记录开始蓄力的时间
			my_plane.plane_state = PLANE_STATE_CHARGING; // 切换到蓄力中状态
		}
		break;

	case WM_RBUTTONUP:
		// 鼠标右键松开事件
		if (my_plane.plane_state == PLANE_STATE_CHARGING) { // 如果飞机状态为蓄力中状态
			my_plane.plane_state = PLANE_STATE_CHARGED; // 切换到蓄力完成状态
			//charge_time = clock() - partly_paused_time -  start_charge_time; // 计算蓄力时间
		}
		break;
	case WM_KEYDOWN:
		if (msg.vkcode == VK_ESCAPE) {
			gamepaused(); // 调用暂停函数
			game_state = GAME_STATE_PAUSED;
			button[CONTINUE].state = BUTTON_STATE_UP;
			button[EXIT].state = BUTTON_STATE_UP;
			button[HOME].state = BUTTON_STATE_UP;
			button[RESTART].state = BUTTON_STATE_UP;
		}
	}
	

}

//检测飞机状态为蓄力中状态时，每秒减少飞机5点耐久度，且每秒增加飞机气势100点，且气势等级最多为3级
void check_plane_state() {
	if (my_plane.plane_state == PLANE_STATE_CHARGING && clock() - partly_paused_time -  start_charge_time > 200  ) { // 如果飞机状态为蓄力中状态
		if (my_plane.endurance > 0) {
			my_plane.endurance -= 1; // 每秒减少飞机5点耐久度
			if(my_plane.grade <= 2){
				my_plane.power += 20; // 每秒增加飞机气势100点
			}
			start_charge_time = clock(); // 重置开始蓄力的时间
		}
		else {
			my_plane.endurance = 0; // 将耐久度设置为0
			my_plane.plane_state = PLANE_STATE_CHARGED; // 切换到完成状态
		}
	}
}
	




//发射子弹
	void shoot_bullet(){
		if (my_plane.plane_state == PLANE_STATE_SHOOTING && my_plane.endurance > 0) {
			for (int i = 0; i <= my_plane.bullet_num; i++) {
				if (!bullet[i].is_active && clock() - partly_paused_time -  my_plane.last_shoot_time > 200) { // 如果子弹未激活且距离上次射击时间超过200毫秒
					// 子弹发射音效
					if (bullet_sound) {
						DWORD chan = BASS_SampleGetChannel(bullet_sound, FALSE);
						BASS_ChannelPlay(chan, TRUE);
					}

					//根据飞机气势等级设置子弹类型和伤害
					if (my_plane.grade == 0) { // 一级气势
						bullet[i].bullet_type = BULLET_TYPE_NORMAL; //
						bullet[i].bullet_damage = 10; // 设置子弹伤害
					}

					else if (my_plane.grade == 1) { // 二级气势
						bullet[i].bullet_type = BULLET_TYPE_NORMAL; // 
						bullet[i].bullet_damage = 11; // 设置子弹伤害
					}

					else if (my_plane.grade == 2) { // 三级气势
						bullet[i].bullet_type = BULLET_TYPE_NORMAL; // 
						bullet[i].bullet_damage = 12; // 设置子弹伤害
					}

					else if (my_plane.grade == 3) { // 四级及以上气势
						bullet[i].bullet_type = BULLET_TYPE_NORMAL; // 
						bullet[i].bullet_damage = 15; // 设置子弹伤害
					}

					else if (my_plane.grade >= 4) { // 五级及以上气势
						bullet[i].bullet_type = BULLET_TYPE_NORMAL; //
						bullet[i].bullet_damage = 20; // 设置子弹伤害
					}

					bullet[i].is_active = true; // 激活子弹
					bullet[i].start_pos.x = my_plane.plane_pos.x + PLANE_SIZE / 2; // 设置子弹位置为飞机位置
					bullet[i].bullet_pos.x = bullet[i].start_pos.x; // 设置子弹位置为起始位置
					bullet[i].start_pos.y = my_plane.plane_pos.y - PLANE_SIZE / 2; // 设置子弹位置为飞机位置
					bullet[i].bullet_pos.y = bullet[i].start_pos.y; // 设置子弹位置为起始位置
					bullet[i].bullet_speed = 0.3; // 设置子弹速度
					bullet[i].bullet_size = BULLET_SIZE; // 设置子弹大小
					bullet[i].bullet_grade = my_plane.grade; // 设置子弹等级为飞机等级
					my_plane.endurance -= 1; // 减少飞机耐久度
					bullet[i].generate_time = clock(); // 记录子弹生成时间
					bullet[i].last_move_time = clock();//记录上次移动时间

					my_plane.last_shoot_time = clock(); // 记录最后一次射击时间
					if (my_plane.bullet_num < BULLET_NUM) { // 如果子弹数量小于最大子弹数量
						my_plane.bullet_num++; // 增加子弹数量
					}
					break; // 退出循环
				}
			}
		}
		if (my_plane.plane_state == PLANE_STATE_CHARGED) {
			// 子弹发射音效
			if (my_plane.grade <= 2) {
				if (bullet_sound) {
					DWORD chan = BASS_SampleGetChannel(bullet_sound, FALSE);
					BASS_ChannelPlay(chan, TRUE);
				}
			}
			else {
				if (mega_bullet_sound) {
					DWORD chan = BASS_SampleGetChannel(mega_bullet_sound, FALSE);
					BASS_ChannelPlay(chan, TRUE);
				}
			}

			//根据飞机气势等级设置子弹类型和伤害
			mega_bullet[0].bullet_size = 100; // 设置子弹大小为100
			if (my_plane.grade == 0) { // 一级气势
				mega_bullet[0].bullet_type = BULLET_TYPE_BIG; //
				mega_bullet[0].bullet_damage = 30; // 设置子弹伤害
			}

			else if (my_plane.grade == 1) { // 二级气势
				mega_bullet[0].bullet_type = BULLET_TYPE_BIG; // 
				mega_bullet[0].bullet_damage = 50; // 设置子弹伤害
			}

			else if (my_plane.grade == 2) { // 三级气势
				mega_bullet[0].bullet_type = BULLET_TYPE_BIG; // 
				mega_bullet[0].bullet_damage = 100; // 设置子弹伤害
			}

			else if (my_plane.grade == 3) { // 四级及以上气势
				mega_bullet[0].bullet_type = BULLET_TYPE_BIG; // 
				mega_bullet[0].bullet_damage = 150; // 设置子弹伤害
			}

			else if (my_plane.grade == 4) { // 五级及以上气势
				mega_bullet[0].bullet_type = BULLET_TYPE_BIG; //
				mega_bullet[0].bullet_damage = 200; // 设置子弹伤害
			}

			else if (my_plane.grade == 5) { // 六级
				mega_bullet[0].bullet_type = BULLET_TYPE_BIG; //
				mega_bullet[0].bullet_damage = 400; // 设置子弹伤害
				mega_bullet[0].bullet_size = MEGA_SIZE; // 设置子弹大小
				start_grade = clock(); // 记录进入无双状态的时间
				my_plane.plane_state = PLANE_STATE_MEGA_NORMAL; // 切换到无双射击状态
			}

			mega_bullet[0].is_active = true; // 激活子弹
			mega_bullet[0].bullet_grade = my_plane.grade; // 设置子弹等级为飞机等级
			mega_bullet[0].generate_time = clock();
			mega_bullet[0].start_pos.x = my_plane.plane_pos.x + PLANE_SIZE / 2; // 设置子弹位置为飞机位置
			mega_bullet[0].bullet_pos.x = mega_bullet[0].start_pos.x; // 设置子弹位置为起始位置
			mega_bullet[0].start_pos.y = my_plane.plane_pos.y - PLANE_SIZE / 2; // 设置子弹位置为飞机位置
			mega_bullet[0].bullet_pos.y = mega_bullet[0].start_pos.y; // 设置子弹位置为起始位置
			mega_bullet[0].bullet_speed = 0.7; // 设置子弹速度
			my_plane.endurance -= 10; // 减少飞机耐久度
			mega_bullet[0].generate_time = clock(); // 记录子弹生成时间
			mega_bullet[0].last_move_time = clock();// 记录上次移动时间
			bullet[my_plane.bullet_num++] = mega_bullet[0];
			my_plane.last_shoot_time = clock(); // 记录最后一次射击时间
			if (my_plane.bullet_num < BULLET_NUM) { // 如果子弹数量小于最大子弹数量
				my_plane.bullet_num++; // 增加子弹数量
			}
			if (my_plane.grade >= 5) {
				start_grade = clock(); // 记录进入无双状态的时间
				my_plane.plane_state = PLANE_STATE_MEGA_NORMAL; // 切换到无双射击状态
			}
			else {
			my_plane.plane_state = PLANE_STATE_NORMAL;
			my_plane.grade = 0; // 重置飞机等级
			my_plane.power = 0; // 重置飞机气势
			}
		}
		if (my_plane.plane_state == PLANE_STATE_MEGA_SHOOTING) {
			
			
				for (int i = 0; i <= my_plane.bullet_num; i++) {
					if (!bullet[i].is_active && clock() - partly_paused_time -  my_plane.last_shoot_time > 100) { // 如果子弹未激活且距离上次射击时间超过100毫秒
						// 子弹发射音效
						if (bullet_sound) {
							DWORD chan = BASS_SampleGetChannel(bullet_sound, FALSE);
							BASS_ChannelPlay(chan, TRUE);
						}

						bullet[i].is_active = true; // 激活子弹
						bullet[i].bullet_type = BULLET_TYPE_MEGA;
						bullet[i].start_pos.x = my_plane.plane_pos.x + PLANE_SIZE / 2; // 设置子弹位置为飞机位置
						bullet[i].bullet_pos.x = bullet[i].start_pos.x; // 设置子弹位置为起始位置
						bullet[i].start_pos.y = my_plane.plane_pos.y - PLANE_SIZE / 2; // 设置子弹位置为飞机位置
						bullet[i].bullet_pos.y = bullet[i].start_pos.y; // 设置子弹位置为起始位置
						bullet[i].bullet_speed = 0.3; // 设置子弹速度
						bullet[i].bullet_damage = 20; // 设置子弹伤害
						bullet[i].generate_time = clock(); // 记录子弹生成时间
						bullet[i].last_move_time = clock();// 记录上次移动时间
						my_plane.last_shoot_time = clock(); // 记录最后一次射击时间
						if (my_plane.bullet_num < BULLET_NUM) { // 如果子弹数量小于最大子弹数量
							my_plane.bullet_num++; // 增加子弹数量
						}
						break; // 退出循环
					}
				}
			}
		}
	
	

//更新子弹位置
void bullet_move() {
	
		// 更新子弹位置
		for (int i = 0; i < BULLET_NUM; i++) {
			if (bullet[i].is_active) { // 如果子弹激活
				time_t t = clock() - partly_paused_time - bullet[i].last_move_time;
				if (t >= 1) {
					
					bullet[i].bullet_pos.y -= t * bullet[i].bullet_speed; // 更新子弹位置
					
				}
				bullet[i].last_move_time = clock();
				if (bullet[i].bullet_pos.y < -150) { // 如果子弹超出屏幕上边界
					bullet[i].is_active = false; // 禁用子弹
					if (bullet[i].bullet_type == BULLET_TYPE_BIG) {
						mega_bullet[0].is_active = false; // 禁用大子弹
						for(int j = 0;j < ENEMY_MAX_NUM;j++){
							enemy_plane[j].is_hitted_by_mega = false; // 重置敌机被大子弹击中的状态
						}
					}
					//char teststr[50];
					//sprintf(teststr, "bullet_num: %d", i);
					//MessageBox(NULL, teststr, "提示", MB_OK); // 弹出提示框显示子弹数量(排除bug用）
					my_plane.bullet_num--; // 减少子弹数量
				}
			}
		}
	}


//生成敌机
void generate_enemy() {
	if (enemy_num < ENEMY_MAX_NUM) { // 如果敌机数量小于最大敌机数量
		for (int i = 0; i < ENEMY_MAX_NUM; i++) {
			if (!enemy_plane[i].is_alive) { // 如果敌机未激活
				enemy_plane[i].is_alive = true; // 激活敌机
				//概率生成敌机类型
				if (rand() % 100 < (level-1)*5) { // 概率生成精英敌机
					enemy_plane[i].plane_type = ENEMY_TYPE_ELITE; // 设置敌机类型为BOSS敌机
					enemy_plane[i].maxlife = 200; // 设置敌机最大生命值
					enemy_plane[i].life = 200; // 设置敌机生命值
					enemy_plane[i].size = PLANE_ELITE_SIZE; // 设置精英敌机大小
					enemy_plane[i].height = 80; // 设置精英敌机高度
				}
				else {
					enemy_plane[i].plane_type = ENEMY_TYPE_NORMAL; // 设置敌机类型为普通敌机
					enemy_plane[i].maxlife = 50; // 设置敌机最大生命值
					enemy_plane[i].life = 50; // 设置敌机生命值
					enemy_plane[i].size = PLANE_SIZE; // 设置普通敌机大小
					enemy_plane[i].height = PLANE_SIZE; // 设置普通敌机高度
				}
				
				//enemy_plane[i].size = PLANE_SIZE; // 设置敌机大小
				//enemy_plane[i].height = PLANE_SIZE; // 设置敌机高度
				enemy_plane[i].start_pos.x = rand() % (SCREEN_WIDTH - enemy_plane[i].size)+25; // 随机生成敌机位置
				enemy_plane[i].plane_pos.x = enemy_plane[i].start_pos.x; // 设置敌机位置为起始位置
				enemy_plane[i].start_pos.y = -enemy_plane[i].height; // 设置敌机初始位置在屏幕上方
				enemy_plane[i].plane_pos.y = enemy_plane[i].start_pos.y; // 设置敌机位置为起始位置
				enemy_plane[i].speed = 0.1; // 设置敌机速度
				
				/*enemy_plane[i].plane_type = ENEMY_TYPE_NORMAL;*/ // 设置敌机类型为普通敌机
				
				enemy_plane[i].generate_time = clock(); // 记录敌机生成时间
				enemy_plane[i].last_move_time = clock();//记录上次移动时间

				enemy_num++; // 增加敌机数量
				srand(time(NULL));
				enemy_plane[i].style = rand() % 3;  // 0, 1, 2
				break; // 退出循环
			}
		}
	}
}
// 更新敌机位置
void update_enemy() {
	for (int i = 0; i < ENEMY_MAX_NUM; i++) {
		if (enemy_plane[i].is_alive) { // 如果敌机激活
			time_t t = clock() - partly_paused_time - enemy_plane[i].last_move_time;
			if (t >= 1) {
				enemy_plane[i].plane_pos.y += t * enemy_plane[i].speed; // 更新敌机位置

			}
			enemy_plane[i].last_move_time = clock();
			if (enemy_plane[i].plane_type == ENEMY_TYPE_BOSS && enemy_plane[i].plane_pos.y > 150) {
				enemy_plane[i].plane_pos.y = 150; // 如果是BOSS敌机，限制其位置在屏幕上方150像素
			}
			if (enemy_plane[i].plane_pos.y > SCREEN_HEIGHT) { // 如果敌机超出屏幕下边界
				enemy_plane[i].is_alive = false; // 禁用敌机
				enemy_num--; // 减少敌机数量
			}
		}
	}
}

//发射敌机子弹
void enemy_shoot_bullet() {
	for(int j = 0; j < ENEMY_MAX_NUM; j++) {
		if (enemy_plane[j].is_alive && clock() - partly_paused_time -  enemy_plane[j].generate_time > 1000 && clock() - shoot_paused_time -  enemy_plane[j].last_shoot_time > 1000) { // 如果敌机激活且距离生成时间超过1000毫秒
			for (int i = 0; i < BULLET_NUM; i++) {
				if (!enemy_bullet[i].is_active) { // 如果敌机子弹未激活
					enemy_bullet[i].is_active = true; // 激活敌机子弹
					enemy_bullet[i].start_pos.x = enemy_plane[j].plane_pos.x + enemy_plane[i].size / 2; // 设置敌机子弹位置为敌机位置
					enemy_bullet[i].bullet_pos.x = enemy_bullet[i].start_pos.x; // 设置敌机子弹位置为起始位置
					enemy_bullet[i].start_pos.y = enemy_plane[j].plane_pos.y + enemy_plane[i].height / 2; // 设置敌机子弹位置为敌机位置
					enemy_bullet[i].bullet_pos.y = enemy_bullet[i].start_pos.y; // 设置敌机子弹位置为起始位置
					enemy_bullet[i].bullet_speed = 0.3; // 设置敌机子弹速度
					// 敌机子弹伤害,精英敌机伤害为3，普通敌机伤害为1
					if (enemy_plane[j].plane_type == ENEMY_TYPE_ELITE || enemy_plane[j].plane_type == ENEMY_TYPE_BOSS) {
						enemy_bullet[i].bullet_damage = 3; // 设置敌机子弹伤害
						enemy_bullet[i].bullet_type = BULLET_TYPE_TRACKING; // 设置敌机子弹类型为追踪子弹
						enemy_bullet[i].aim_pos.x = my_plane.plane_pos.x; // 设置目标位置为玩家飞机位置
						enemy_bullet[i].aim_pos.y = my_plane.plane_pos.y; // 设置目标位置为玩家飞机位置
						
						enemy_bullet[i].bullet_speed_x = enemy_bullet[i].bullet_speed * ((enemy_bullet[i].aim_pos.x - enemy_bullet[i].start_pos.x) / 
							sqrt(pow(enemy_bullet[i].aim_pos.x - enemy_bullet[i].start_pos.x, 2) + pow(enemy_bullet[i].aim_pos.y - enemy_bullet[i].start_pos.y, 2))); // 设置敌机子弹速度X分量
						enemy_bullet[i].bullet_speed_y = enemy_bullet[i].bullet_speed * ((enemy_bullet[i].aim_pos.y - enemy_bullet[i].start_pos.y) / 
							sqrt(pow(enemy_bullet[i].aim_pos.x - enemy_bullet[i].start_pos.x, 2) + pow(enemy_bullet[i].aim_pos.y - enemy_bullet[i].start_pos.y, 2))) ; // 设置敌机子弹速度Y分量
						if(enemy_bullet[i].bullet_speed_y < 0.1) { // 如果Y分量速度过小
							enemy_bullet[i].bullet_speed_y = 0.3; // 设置Y分量速度为0.3
							enemy_bullet[i].bullet_speed_x = 0;// 设置X分量速度
						}
					}
					else if (enemy_plane[j].plane_type == ENEMY_TYPE_NORMAL) {
						enemy_bullet[i].bullet_damage = 1; // 设置敌机子弹伤害
						enemy_bullet[i].bullet_type = BULLET_TYPE_NORMAL; // 设置敌机子弹类型为普通子弹
					}
					enemy_bullet[i].generate_time = clock(); // 记录敌机子弹生成时间
					enemy_bullet[i].last_move_time = clock();// 记录上次移动时间
					enemy_plane[j].last_shoot_time = clock(); // 记录最后一次射击时间
					enemy_bullet_num++; // 增加敌机子弹数量
					break; // 退出循环
				}
			}
		//enemy_plane[j].generate_time = clock(); // 更新敌机生成时间
			shoot_paused_time = 0;
			break; // 退出循环
		}
	}
}

//更新敌机子弹位置
void enemy_bullet_move() {

	// 更新子弹位置
	for (int i = 0; i <= ENEMY_MAX_NUM; i++) {
		if (enemy_bullet[i].is_active) { // 如果子弹激活
			time_t t = clock() - partly_paused_time - enemy_bullet[i].last_move_time;
			//如果为普通敌机子弹
			if (enemy_bullet[i].bullet_type == BULLET_TYPE_NORMAL) {
				if (t >= 1) {
					enemy_bullet[i].bullet_pos.y += t * enemy_bullet[i].bullet_speed; // 更新子弹位置
					enemy_bullet[i].last_move_time = clock();
				}

			}
			//如果为精英敌机子弹
			else if (enemy_bullet[i].bullet_type == BULLET_TYPE_TRACKING) {

				if (t >= 1) {
					enemy_bullet[i].bullet_pos.x += t * enemy_bullet[i].bullet_speed_x; // 更新子弹位置
					enemy_bullet[i].bullet_pos.y += t * enemy_bullet[i].bullet_speed_y; // 更新子弹位置


				}

			}

		}
		enemy_bullet[i].last_move_time = clock();
		if (enemy_bullet[i].bullet_pos.y > SCREEN_HEIGHT) { // 如果子弹超出屏幕下边界
			enemy_bullet[i].is_active = false; // 禁用子弹
			enemy_bullet_num--; // 减少敌机子弹数量
		}

	}
}


//敌机子弹与玩家飞机碰撞
void check_enemy_bullet_collision() {
	for (int i = 0; i < BULLET_NUM; i++) {
		if (enemy_bullet[i].is_active) { // 如果敌机子弹激活
			// 检测敌机子弹与玩家飞机的碰撞
			if (abs(enemy_bullet[i].bullet_pos.x - my_plane.plane_pos.x) < my_plane.size /2 &&
				abs(enemy_bullet[i].bullet_pos.y - my_plane.plane_pos.y) < my_plane.height /2) {
				// 子弹击中音效
				if (bullet_hit_sound) {
					DWORD chan = BASS_SampleGetChannel(bullet_hit_sound, FALSE);
					BASS_ChannelPlay(chan, TRUE);
				}
				my_plane.life -= enemy_bullet[i].bullet_damage; // 玩家飞机受到伤害
				enemy_bullet[i].is_active = false; // 禁用敌机子弹
				enemy_bullet_num--; // 减少敌机子弹数量
				if (my_plane.life <= 0) { // 如果玩家飞机生命值小于等于0
					my_plane.is_alive = false; // 玩家飞机死亡
					break; // 退出循环
				}
			}
		}
	}
}

//敌机与玩家飞机碰撞检测
void check_collision() {
	for (int i = 0; i < ENEMY_MAX_NUM; i++) {
		if (enemy_plane[i].is_alive) { // 如果敌机激活
			// 检测敌机与玩家飞机的碰撞
			if (enemy_plane[i].plane_type != ENEMY_TYPE_BOSS && // 如果不是BOSS敌机
				abs(enemy_plane[i].plane_pos.x - my_plane.plane_pos.x) < enemy_plane[i].size/2 &&
				abs(enemy_plane[i].plane_pos.y - my_plane.plane_pos.y) < enemy_plane[i].height/2) {
				// 敌机被击落音效
				if (enemy_down_sound) {
					DWORD chan = BASS_SampleGetChannel(enemy_down_sound, FALSE);
					BASS_ChannelPlay(chan, TRUE);
				}
				//如果为精英敌机受30点伤害，普通敌机受10点伤害
				if (enemy_plane[i].plane_type == ENEMY_TYPE_ELITE) {
					my_plane.life -= 30; // 玩家飞机受到伤害
				} else if (enemy_plane[i].plane_type == ENEMY_TYPE_NORMAL) {
					my_plane.life -= 10; // 玩家飞机受到伤害
				}
				//my_plane.life -= 10; // 玩家飞机受到伤害
				enemy_plane[i].is_alive = false; // 禁用敌机
				enemy_num--; // 减少敌机数量
				if (my_plane.life <= 0) { // 如果玩家飞机生命值小于等于0
					my_plane.is_alive = false; // 玩家飞机死亡
					break; // 退出循环
				}
			}
		}
	}
}

//玩家子弹与敌机碰撞检测
void check_bullet_collision() {
	for (int i = 0; i < BULLET_NUM; i++) {
		if (bullet[i].is_active) { // 如果子弹激活
			for (int j = 0; j < ENEMY_MAX_NUM; j++) {
				if (enemy_plane[j].is_alive && !enemy_plane[j].is_hitted_by_mega) { // 如果敌机激活
					// 检测子弹与敌机的碰撞
					if (enemy_plane[j].plane_type == ENEMY_TYPE_BOSS) {// 如果是BOSS敌机
						if (abs(bullet[i].bullet_pos.x - enemy_plane[j].plane_pos.x) < bullet[i].bullet_size * 2 &&
							abs(bullet[i].bullet_pos.y - enemy_plane[j].plane_pos.y) < enemy_plane[j].height / 2) {
							enemy_plane[j].life -= bullet[i].bullet_damage; // 敌机受到伤害
							if (enemy_plane[i].life > 0 || bullet[i].bullet_type == BULLET_TYPE_BIG) {
								// 子弹击中音效
								if (bullet[i].bullet_grade > 2 && bullet[i].bullet_type == BULLET_TYPE_BIG) {
									if (mega_bullet_hit_sound) {
										DWORD chan = BASS_SampleGetChannel(mega_bullet_hit_sound, FALSE);
										BASS_ChannelPlay(chan, TRUE);
									}
								}
								else if (enemy_plane[j].life > 0) {
									if (bullet_hit_sound) {
										DWORD chan = BASS_SampleGetChannel(bullet_hit_sound, FALSE);
										BASS_ChannelPlay(chan, TRUE);
									}
								}
							}
							if (bullet[i].bullet_type == BULLET_TYPE_BIG && bullet[i].bullet_grade > 2 ) {
								enemy_plane[j].is_hitted_by_mega = true; // 设置敌机被重击子弹击中状态为true
							}
							else {
								bullet[i].is_active = false; // 禁用子弹
								my_plane.bullet_num--; // 减少子弹数量
								if (bullet[i].bullet_type == BULLET_TYPE_BIG) {
									mega_bullet[0].is_active = false; // 禁用大子弹
								}
							}
							
							if (enemy_plane[j].life <= 0) { // 如果敌机生命值小于等于0
								// 敌机被击落音效
								if (enemy_down_sound) {
									DWORD chan = BASS_SampleGetChannel(boss_down_sound, FALSE);
									BASS_ChannelPlay(chan, TRUE);
								}
								enemy_plane[j].is_alive = false; // 禁用敌机
								enemy_num--; // 减少敌机数量
								score += enemy_plane[j].maxlife;// 增加分数
								last_complete_time = clock(); // 更新上次通关时间
								total_paused_time = 0;// 重置总暂停时间
								boss_is_alive = false; // BOSS激活状态设置为false
								
								if(level < 5)level++; // 关卡数增加
								if (drop_item_num < ITEM_NUM - 1)generate_drop_item(ENEMY_TYPE_BOSS, enemy_plane[j].plane_pos); // 生成BOSS掉落物品
							}
							if (bullet[i].bullet_type == BULLET_TYPE_NORMAL) {
								my_plane.power += 10;
								if (my_plane.power > 400) my_plane.power = 400; // 限制飞机气势最大值为400
							} // 增加飞机气势
							break; // 退出循环
						}
					}
					else {// 如果是普通敌机或精英敌机
						if (abs(bullet[i].bullet_pos.x - enemy_plane[j].plane_pos.x) < bullet[i].bullet_size &&
							abs(bullet[i].bullet_pos.y - enemy_plane[j].plane_pos.y) < enemy_plane[j].height){
							enemy_plane[j].life -= bullet[i].bullet_damage; // 敌机受到伤害
							if (enemy_plane[i].life > 0 || bullet[i].bullet_type == BULLET_TYPE_BIG) {
								// 子弹击中音效
								if (bullet[i].bullet_grade > 2 && bullet[i].bullet_type == BULLET_TYPE_BIG)  {
									if (mega_bullet_hit_sound) {
										DWORD chan = BASS_SampleGetChannel(mega_bullet_hit_sound, FALSE);
										BASS_ChannelPlay(chan, TRUE);
									}
								}
								else if(enemy_plane[j].life > 0) {
									if (bullet_hit_sound) {
										DWORD chan = BASS_SampleGetChannel(bullet_hit_sound, FALSE);
										BASS_ChannelPlay(chan, TRUE);
									}
								}
							}
							if (bullet[i].bullet_type == BULLET_TYPE_BIG && bullet[i].bullet_grade > 2 ) {
								enemy_plane[j].is_hitted_by_mega = true; // 设置敌机被重击子弹击中状态为true
							}
							else {
								bullet[i].is_active = false; // 禁用子弹
								my_plane.bullet_num--; // 减少子弹数量
								if (bullet[i].bullet_type == BULLET_TYPE_BIG) {
									mega_bullet[0].is_active = false; // 禁用大子弹
								}
							}
							
							if (enemy_plane[j].life <= 0) { // 如果敌机生命值小于等于0
								// 敌机被击落音效
								if(enemy_plane[j].plane_type == ENEMY_TYPE_ELITE) {
									if (elite_down_sound) {
										DWORD chan = BASS_SampleGetChannel(elite_down_sound, FALSE);
										BASS_ChannelPlay(chan, TRUE);
									}
								}
								else if (enemy_plane[j].plane_type == ENEMY_TYPE_NORMAL) {
									if (enemy_down_sound) {
										DWORD chan = BASS_SampleGetChannel(enemy_down_sound, FALSE);
										BASS_ChannelPlay(chan, TRUE);
									}
								}
								
								enemy_plane[j].is_alive = false; // 禁用敌机
								if (drop_item_num < ITEM_NUM)generate_drop_item(enemy_plane[j].plane_type, enemy_plane[j].plane_pos); // 生成敌机掉落物品
								enemy_num--; // 减少敌机数量
								score += enemy_plane[j].maxlife;// 增加分数
							}
							if (bullet[i].bullet_type == BULLET_TYPE_NORMAL) {
								my_plane.power += 10;
								if (my_plane.power > 400) my_plane.power = 400; // 限制飞机气势最大值为400
							} // 增加飞机气势
							break; // 退出循环
							}

					}
				}
			}
		}
	}
}

//游戏开始90秒后生成BOSS
void generate_boss() {
	if (clock()  -  last_complete_time > 90000 + total_paused_time && !boss_is_alive) { // 如果游戏开始超过90秒且BOSS未激活
		for (int i = 0; i < ENEMY_MAX_NUM; i++) {
			if (!enemy_plane[i].is_alive) { // 如果敌机未激活
				enemy_plane[i].is_alive = true; // 激活敌机
				enemy_plane[i].size = BOSS_SIZE; // 设置BOSS大小
				enemy_plane[i].height = BOSS_HEIGHT;// 设置BOSS高度
				enemy_plane[i].start_pos.x = SCREEN_WIDTH / 2 /*- enemy_plane[i].size / 2*/; // 设置BOSS位置为屏幕中心
				enemy_plane[i].plane_pos.x = enemy_plane[i].start_pos.x; // 设置BOSS位置为起始位置
				enemy_plane[i].start_pos.y = -enemy_plane[i].height; // 设置BOSS初始位置在屏幕上方
				enemy_plane[i].plane_pos.y = enemy_plane[i].start_pos.y; // 设置BOSS位置为起始位置
				enemy_plane[i].speed = 0.03; // 设置BOSS速度
				enemy_plane[i].plane_type = ENEMY_TYPE_BOSS; // 设置BOSS类型为BOSS敌机
				enemy_plane[i].maxlife = BOSS_LIFE + level * 500; // 设置BOSS最大生命值
				enemy_plane[i].life = BOSS_LIFE + level * 500; // 设置BOSS生命值
				enemy_plane[i].generate_time = clock(); // 记录BOSS生成时间
				enemy_plane[i].last_move_time = clock();//记录上次移动时间
				boss_is_alive = true; // BOSS激活状态设置为true
				srand(time(NULL));
				if (level <= 3) {
					enemy_plane[i].style = 0;
				}
				else {

					enemy_plane[i].style = 1;

				}
				break; // 退出循环
			}
		}
	}
}

//检测玩家生命状态
void check_player_life() {
	if (my_plane.life <= 0) { // 如果玩家飞机生命值小于等于0
		my_plane.is_alive = false; // 玩家飞机死亡
		game_state = GAME_STATE_GAME_OVER ; // 切换游戏状态为结束状态
		button[EXIT].state = BUTTON_STATE_UP;
		button[HOME].state = BUTTON_STATE_UP;
		button[RESTART].state = BUTTON_STATE_UP;
		if (is_login)ready_to_insert = true; // 如果是登录状态，准备插入数据
	}
}
//耐久的加减，正常状态每秒恢复15耐久
void add_endurance() {
	
	if ((my_plane.plane_state == PLANE_STATE_NORMAL || my_plane.plane_state == PLANE_STATE_MEGA_NORMAL || my_plane.plane_state == PLANE_STATE_MEGA_SHOOTING) && clock()-last_added_time > 200 && clock()-my_plane.last_shoot_time > 300) { // 如果飞机状态为正常
		
		my_plane.endurance += 3; // 每秒恢复15耐久
		last_added_time = clock(); // 重置上次添加耐久的时间
		if (my_plane.endurance > 100) { // 如果耐久度超过100
			my_plane.endurance = 100; // 将耐久度设置为100
		}
	}
}


//检测飞机耐久，归零时终止射击
void check_player_endurance() {
	if (my_plane.endurance <= 0) { // 如果玩家飞机耐久度小于等于0
		my_plane.endurance = 0; // 将耐久度设置为0
		my_plane.plane_state = my_plane.plane_state == PLANE_STATE_MEGA_NORMAL? PLANE_STATE_MEGA_NORMAL: (my_plane.plane_state == PLANE_STATE_CHARGING ? PLANE_STATE_CHARGED : PLANE_STATE_NORMAL) ; // 切换到正常状态，若为蓄力状态则切换到蓄力完成状态
		
	}
}

//检测飞机数值，与升级体系
void check_player_power() {
	if (my_plane.power >= GRADE1_SCORE && my_plane.grade == 0) { // 如果飞机气势大于等于100
		//升级音效
		if (grade1_sound) {
			DWORD chan = BASS_SampleGetChannel(grade1_sound, FALSE);
			BASS_ChannelPlay(chan, TRUE);
		}
		my_plane.power -= 100; // 重置气势
		my_plane.grade++; // 升级气势等级
	}

	if (my_plane.power >= GRADE2_SCORE && my_plane.grade == 1) { // 如果飞机气势大于等于110
		//升级音效
		if (grade2_sound) {
			DWORD chan = BASS_SampleGetChannel(grade2_sound, FALSE);
			BASS_ChannelPlay(chan, TRUE);
		}
		my_plane.power -= 110; // 重置气势
		my_plane.grade++; // 升级气势等级
	}

	if (my_plane.power >= GRADE3_SCORE && my_plane.grade == 2) { // 如果飞机气势大于等于120
		//升级音效
		if (grade3_sound) {
			DWORD chan = BASS_SampleGetChannel(grade3_sound, FALSE);
			BASS_ChannelPlay(chan, TRUE);
		}
		my_plane.power -= 120; // 重置气势
		my_plane.grade++; // 升级气势等级
	}

	if (my_plane.power >= GRADE4_SCORE && my_plane.grade == 3) { // 如果飞机气势大于等于150
		//升级音效
		if (grade4_sound) {
			DWORD chan = BASS_SampleGetChannel(grade4_sound, FALSE);
			BASS_ChannelPlay(chan, TRUE);
		}
		my_plane.power -= 150; // 重置气势
		my_plane.grade++; // 升级气势等级
	}

	if (my_plane.power >= GRADE5_SCORE && my_plane.grade == 4) { // 如果飞机气势大于等于400
		//升级音效
		if (grade5_sound) {
			DWORD chan = BASS_SampleGetChannel(grade5_sound, FALSE);
			BASS_ChannelPlay(chan, TRUE);
		}
		my_plane.power = 400; // 重置气势
		my_plane.grade++; // 升级气势等级
		last_power_time = clock(); // 记录或重置上次减少气势的时间
	}

	if (my_plane.grade >= 5 && (my_plane.plane_state == PLANE_STATE_NORMAL || my_plane.plane_state == PLANE_STATE_SHOOTING)) { // 如果气势等级超过5
		my_plane.grade = 5; // 将气势等级设置为5
		my_plane.power = 400;// 将气势设置为400
	}
}

//当飞机气势等级大于等于3时，气势每秒减少5点，但不会小于0
void diminish_player_power() {
	if (my_plane.grade >= 3 && clock() - partly_paused_time -  last_power_time > 200) { // 如果飞机气势等级大于3且距离上次减少气势时间超过1秒
		if (my_plane.power > 0) {
			my_plane.power -= 1; // 每秒减少5点气势
		}
		last_power_time = clock(); // 重置上次减少气势的时间
	}
	if ((my_plane.plane_state == PLANE_STATE_MEGA_NORMAL || my_plane.plane_state == PLANE_STATE_MEGA_SHOOTING) && clock() - partly_paused_time -  last_power_time > 25) {
			my_plane.power -= 1; // 每秒减少10点气势
			if (my_plane.power <= 0) {
				my_plane.grade = 0;
				if (my_plane.plane_state == PLANE_STATE_MEGA_NORMAL) my_plane.plane_state = PLANE_STATE_NORMAL;
				else my_plane.plane_state = PLANE_STATE_SHOOTING;
			}
			last_power_time = clock(); // 重置上次减少气势的时间
	}
}

//当敌机死亡时，掉落收集物，位置为敌机位置
void generate_drop_item(int plane_type, POS plane_pos) {
	for (int j = 0;j < ITEM_NUM - 1;j++) {
		if (drop_item[j].is_active) continue; // 如果掉落物已激活，跳过
		int i = rand();
		switch (plane_type) {
		case ENEMY_TYPE_NORMAL: // 普通敌机
			if (i % 1000 < 3) { // 0.3%的概率掉落物品
				drop_item[j].is_active = true; // 激活掉落物
				drop_item[j].item_type = ITEM_TYPE_BIG_SUPPLY; // 设置掉落物类型为大补给球
				drop_item[j].start_pos.x = plane_pos.x; // 设置掉落物位置为敌机位置
				drop_item[j].start_pos.y = plane_pos.y; // 设置掉落物位置为敌机位置
				drop_item[j].item_pos.x = plane_pos.x; // 设置掉落物位置为敌机位置
				drop_item[j].item_pos.y = plane_pos.y; // 设置掉落物位置为敌机位置
				drop_item[j].generate_time = clock(); // 设置掉落物起始时间
				drop_item[j].last_move_time = clock();// 设置上次移动时间
				drop_item[j].item_speed = 0.1; // 设置掉落物速度
				drop_item_num++; // 增加掉落物数量
				break; // 退出循环
			}
			if (i % 1000 < 8) { // 0.5%的概率掉落物品
				drop_item[j].is_active = true; // 激活掉落物
				drop_item[j].item_type = ITEM_TYPE_BIG_LIFE; // 设置掉落物类型为大生命球
				drop_item[j].start_pos.x = plane_pos.x; // 设置掉落物位置为敌机位置
				drop_item[j].start_pos.y = plane_pos.y; // 设置掉落物位置为敌机位置
				drop_item[j].item_pos.x = plane_pos.x; // 设置掉落物位置为敌机位置
				drop_item[j].item_pos.y = plane_pos.y; // 设置掉落物位置为敌机位置
				drop_item[j].generate_time = clock(); // 设置掉落物起始时间
				drop_item[j].last_move_time = clock();// 设置上次移动时间
				drop_item[j].item_speed = 0.1; // 设置掉落物速度
				drop_item_num++; // 增加掉落物数量
				break; // 退出循环
			}
			if (i % 1000 < 38) { // 3%的概率掉落物品
				drop_item[j].is_active = true; // 激活掉落物
				drop_item[j].item_type = ITEM_TYPE_SUPPLY; // 设置掉落物类型为小补给球
				drop_item[j].start_pos.x = plane_pos.x; // 设置掉落物位置为敌机位置
				drop_item[j].start_pos.y = plane_pos.y; // 设置掉落物位置为敌机位置
				drop_item[j].item_pos.x = plane_pos.x; // 设置掉落物位置为敌机位置
				drop_item[j].item_pos.y = plane_pos.y; // 设置掉落物位置为敌机位置
				drop_item[j].generate_time = clock(); // 设置掉落物起始时间
				drop_item[j].last_move_time = clock();// 设置上次移动时间
				drop_item[j].item_speed = 0.1; // 设置掉落物速度
				drop_item_num++; // 增加掉落物数量
				break; // 退出循环
			}
			if (i % 1000 < 88) { // 5%的概率掉落物品
				drop_item[j].is_active = true; // 激活掉落物
				drop_item[j].item_type = ITEM_TYPE_SMALL_LIFE; // 设置掉落物类型为小生命球
				drop_item[j].start_pos.x = plane_pos.x; // 设置掉落物位置为敌机位置
				drop_item[j].start_pos.y = plane_pos.y; // 设置掉落物位置为敌机位置
				drop_item[j].item_pos.x = plane_pos.x; // 设置掉落物位置为敌机位置
				drop_item[j].item_pos.y = plane_pos.y; // 设置掉落物位置为敌机位置
				drop_item[j].generate_time = clock(); // 设置掉落物起始时间
				drop_item[j].last_move_time = clock();// 设置上次移动时间
				drop_item[j].item_speed = 0.1; // 设置掉落物速度
				drop_item_num++; // 增加掉落物数量
				break; // 退出循环
			}



			break;
		case ENEMY_TYPE_ELITE: // 精英敌机
			if (i % 1000 < 15) { // 1.5%的概率掉落物品
				drop_item[j].is_active = true; // 激活掉落物
				drop_item[j].item_type = ITEM_TYPE_BIG_SUPPLY; // 设置掉落物类型为大补给球
				drop_item[j].start_pos.x = plane_pos.x; // 设置掉落物位置为敌机位置
				drop_item[j].start_pos.y = plane_pos.y; // 设置掉落物位置为敌机位置
				drop_item[j].item_pos.x = plane_pos.x; // 设置掉落物位置为敌机位置
				drop_item[j].item_pos.y = plane_pos.y; // 设置掉落物位置为敌机位置
				drop_item[j].generate_time = clock(); // 设置掉落物起始时间
				drop_item[j].last_move_time = clock();// 设置上次移动时间
				drop_item[j].item_speed = 0.1; // 设置掉落物速度
				drop_item_num++; // 增加掉落物数量
				break; // 退出循环
			}
			if (i % 1000 < 35) { // 2%的概率掉落物品
				drop_item[j].is_active = true; // 激活掉落物
				drop_item[j].item_type = ITEM_TYPE_BIG_LIFE; // 设置掉落物类型为大生命球
				drop_item[j].start_pos.x = plane_pos.x; // 设置掉落物位置为敌机位置
				drop_item[j].start_pos.y = plane_pos.y; // 设置掉落物位置为敌机位置
				drop_item[j].item_pos.x = plane_pos.x; // 设置掉落物位置为敌机位置
				drop_item[j].item_pos.y = plane_pos.y; // 设置掉落物位置为敌机位置
				drop_item[j].generate_time = clock(); // 设置掉落物起始时间
				drop_item[j].last_move_time = clock();// 设置上次移动时间
				drop_item[j].item_speed = 0.1; // 设置掉落物速度
				drop_item_num++; // 增加掉落物数量
				break; // 退出循环
			}
			if (i % 1000 < 185) { // 15%的概率掉落物品
				drop_item[j].is_active = true; // 激活掉落物
				drop_item[j].item_type = ITEM_TYPE_SUPPLY; // 设置掉落物类型为小补给球
				drop_item[j].start_pos.x = plane_pos.x; // 设置掉落物位置为敌机位置
				drop_item[j].start_pos.y = plane_pos.y; // 设置掉落物位置为敌机位置
				drop_item[j].item_pos.x = plane_pos.x; // 设置掉落物位置为敌机位置
				drop_item[j].item_pos.y = plane_pos.y; // 设置掉落物位置为敌机位置
				drop_item[j].generate_time = clock(); // 设置掉落物起始时间
				drop_item[j].last_move_time = clock();// 设置上次移动时间
				drop_item[j].item_speed = 0.1; // 设置掉落物速度
				drop_item_num++; // 增加掉落物数量
				break; // 退出循环
			}

			if (i % 1000 < 385) { // 20%的概率掉落物品
				drop_item[j].is_active = true; // 激活掉落物
				drop_item[j].item_type = ITEM_TYPE_SMALL_LIFE; // 设置掉落物类型为小生命球
				drop_item[j].start_pos.x = plane_pos.x; // 设置掉落物位置为敌机位置
				drop_item[j].start_pos.y = plane_pos.y; // 设置掉落物位置为敌机位置
				drop_item[j].item_pos.x = plane_pos.x; // 设置掉落物位置为敌机位置
				drop_item[j].item_pos.y = plane_pos.y; // 设置掉落物位置为敌机位置
				drop_item[j].generate_time = clock(); // 设置掉落物起始时间
				drop_item[j].last_move_time = clock();// 设置上次移动时间
				drop_item[j].item_speed = 0.1; // 设置掉落物速度
				drop_item_num++; // 增加掉落物数量
				break; // 退出循环
			}




			break;
		case ENEMY_TYPE_BOSS: // BOSS敌机

			//BOSS必掉大生命球
			drop_item[j].is_active = true; // 激活掉落物
			drop_item[j].item_type = ITEM_TYPE_BIG_LIFE; // 设置掉落物类型为大生命球
			drop_item[j].start_pos.x = plane_pos.x; // 设置掉落物位置为敌机位置
			drop_item[j].start_pos.y = plane_pos.y; // 设置掉落物位置为敌机位置
			drop_item[j].item_pos.x = plane_pos.x; // 设置掉落物位置为敌机位置
			drop_item[j].item_pos.y = plane_pos.y; // 设置掉落物位置为敌机位置
			drop_item[j].generate_time = clock(); // 设置掉落物起始时间
			drop_item[j].last_move_time = clock();// 设置上次移动时间
			drop_item[j].item_speed = 0.1; // 设置掉落物速度
			drop_item_num++; // 增加掉落物数量
			if (i % 100 < 5) { // 5%的概率掉落物品
				drop_item[++j].is_active = true; // 激活掉落物
				drop_item[j].item_type = ITEM_TYPE_BIG_SUPPLY; // 设置掉落物类型为大补给球
				drop_item[j].start_pos.x = plane_pos.x - 100; // 设置掉落物位置为敌机位置
				drop_item[j].start_pos.y = plane_pos.y; // 设置掉落物位置为敌机位置
				drop_item[j].item_pos.x = plane_pos.x - 100; // 设置掉落物位置为敌机位置
				drop_item[j].item_pos.y = plane_pos.y; // 设置掉落物位置为敌机位置
				drop_item[j].generate_time = clock(); // 设置掉落物起始时间
				drop_item[j].last_move_time = clock();// 设置上次移动时间
				drop_item[j].item_speed = 0.1; // 设置掉落物速度
				drop_item_num++; // 增加掉落物数量
				break; // 退出循环
			}
			 if (i % 100 < 55) { // 50%的概率掉落物品
				drop_item[++j].is_active = true; // 激活掉落物
				drop_item[j].item_type = ITEM_TYPE_SUPPLY; // 设置掉落物类型为小补给球
				drop_item[j].start_pos.x = plane_pos.x - 100; // 设置掉落物位置为敌机位置
				drop_item[j].start_pos.y = plane_pos.y; // 设置掉落物位置为敌机位置
				drop_item[j].item_pos.x = plane_pos.x - 100; // 设置掉落物位置为敌机位置
				drop_item[j].item_pos.y = plane_pos.y; // 设置掉落物位置为敌机位置
				drop_item[j].generate_time = clock(); // 设置掉落物起始时间
				drop_item[j].last_move_time = clock();// 设置上次移动时间
				drop_item[j].item_speed = 0.1; // 设置掉落物速度
				drop_item_num++; // 增加掉落物数量
				break; // 退出循环
			}



			break;

		}
		break; // 退出循环
	}

}


//更新掉落物位置
void update_drop_item() {
	for (int i = 0; i < ITEM_NUM; i++) {
		if (drop_item[i].is_active) { // 如果掉落物激活
			time_t t = clock() - partly_paused_time - drop_item[i].last_move_time;
			if (t >= 1) {
				drop_item[i].item_pos.y += t * drop_item[i].item_speed; // 更新掉落物位置
				
			}
			drop_item[i].last_move_time = clock();
			if (drop_item[i].item_pos.y > SCREEN_HEIGHT) { // 如果掉落物超出屏幕下边界
				drop_item[i].is_active = false; // 禁用掉落物
				drop_item_num--; // 减少掉落物数量
			}
		}
	}
}

//玩家与掉落物碰撞检测
void check_player_drop_item_collision() {
	for (int i = 0; i < ITEM_NUM; i++) {
		if (drop_item[i].is_active) { // 如果掉落物激活
			// 检测掉落物与玩家飞机的碰撞
			if (abs(drop_item[i].item_pos.x - my_plane.plane_pos.x) < PLANE_SIZE * 2 &&
				abs(drop_item[i].item_pos.y - my_plane.plane_pos.y) < PLANE_SIZE * 2) {
				switch (drop_item[i].item_type) { // 根据掉落物类型执行不同操作
				case ITEM_TYPE_SMALL_LIFE: // 小生命球
					my_plane.life += 30; // 玩家飞机生命值增加1
					if (my_plane.life > 100) my_plane.life = 100; // 生命值不超过100
					drop_item[i].is_active = false; // 禁用掉落物
					//播放音效
					if (get_life_sound) {
						DWORD chan = BASS_SampleGetChannel(get_life_sound, FALSE);
						BASS_ChannelPlay(chan, TRUE);
					}
					break;
				case ITEM_TYPE_BIG_LIFE: // 大生命球
					my_plane.life = 100; // 玩家飞机生命值增加5
					my_plane.endurance = 100; // 玩家飞机耐久度增加20
					drop_item[i].is_active = false; // 禁用掉落物
					//播放音效
					if (get_life_sound) {
						DWORD chan = BASS_SampleGetChannel(get_life_sound, FALSE);
						BASS_ChannelPlay(chan, TRUE);
					}
					break;
				case ITEM_TYPE_SUPPLY: // 小补给球
					if(my_plane.plane_state == PLANE_STATE_NORMAL || my_plane.plane_state == PLANE_STATE_SHOOTING)my_plane.power += 100; // 玩家飞机气势增加100
					drop_item[i].is_active = false; // 禁用掉落物
					//播放音效
					if (get_power_sound) {
						DWORD chan = BASS_SampleGetChannel(get_power_sound, FALSE);
						BASS_ChannelPlay(chan, TRUE);
					}
					break;
				case ITEM_TYPE_BIG_SUPPLY: // 大补给球
					if(my_plane.plane_state == PLANE_STATE_NORMAL || my_plane.plane_state == PLANE_STATE_SHOOTING)my_plane.power += 480; // 玩家飞机气势增加480
					drop_item[i].is_active = false; // 禁用掉落物
					//播放音效
					if (get_power_sound) {
						DWORD chan = BASS_SampleGetChannel(get_power_sound, FALSE);
						BASS_ChannelPlay(chan, TRUE);
					}

				}
				drop_item[i].is_active = false; // 禁用掉落物
				drop_item_num--; // 减少掉落物数量
			}
		}
	}
}

//播放音乐
void play_music() {
	switch (level) {
		case 1: // 第一关
			//停止所有背景音乐
			//BASS_SampleStop(bgm1); // 停止背景音乐1
			BASS_SampleStop(bgm2); // 停止背景音乐2
			BASS_SampleStop(bgm3); // 停止背景音乐3
			BASS_SampleStop(bgm4); // 停止背景音乐4
			BASS_SampleStop(bgm5); // 停止背景音乐5

			
		if (bgm1) { // 如果背景音乐存在
				BGM1 = BASS_SampleGetChannel(bgm1, FALSE); // 获取背景音乐通道
				//if (!BASS_ChannelIsActive(BGM)) { // 如果背景音乐未在播放
			
					// 将背景音乐音量设置为30%
					BASS_ChannelSetAttribute(BGM1, BASS_ATTRIB_VOL, 0.3f);
					BASS_ChannelPlay(BGM1, TRUE); // 播放背景音乐
				//}
			}
		break;
		case 2: // 第二关
			BASS_SampleStop(bgm1); // 停止背景音乐1
			if (bgm2) { // 如果背景音乐存在
				BGM2 = BASS_SampleGetChannel(bgm2, FALSE); // 获取背景音乐通道
				//if (!BASS_ChannelIsActive(BGM)) { // 如果背景音乐未在播放
					// 将背景音乐音量设置为30%
					BASS_ChannelSetAttribute(BGM2, BASS_ATTRIB_VOL, 0.3f);
					BASS_ChannelPlay(BGM2, TRUE); // 播放背景音乐
				//}
			}
			break;
		case 3: // 第三关
			BASS_SampleStop(bgm2); // 停止背景音乐2
			if (bgm3) { // 如果背景音乐存在
				BGM3 = BASS_SampleGetChannel(bgm3, FALSE); // 获取背景音乐通道
				//if (!BASS_ChannelIsActive(BGM)) { // 如果背景音乐未在播放
					// 将背景音乐音量设置为30%
					BASS_ChannelSetAttribute(BGM3, BASS_ATTRIB_VOL, 0.3f);
					BASS_ChannelPlay(BGM3, TRUE); // 播放背景音乐
				//}
			}
			break;
		case 4: // 第四关
			BASS_SampleStop(bgm3); // 停止背景音乐3
			if (bgm4) { // 如果背景音乐存在
				BGM4 = BASS_SampleGetChannel(bgm4, FALSE); // 获取背景音乐通道
				//if (!BASS_ChannelIsActive(BGM)) { // 如果背景音乐未在播放
					// 将背景音乐音量设置为30%
					BASS_ChannelSetAttribute(BGM4, BASS_ATTRIB_VOL, 0.3f);
					BASS_ChannelPlay(BGM4, TRUE); // 播放背景音乐
				//}
			}
			break;
		case 5: // 第五关
			BASS_SampleStop(bgm4); // 停止背景音乐4
			if (bgm5) { // 如果背景音乐存在
				BGM5 = BASS_SampleGetChannel(bgm5, FALSE); // 获取背景音乐通道
				//if (!BASS_ChannelIsActive(BGM)) { // 如果背景音乐未在播放
					// 将背景音乐音量设置为30%
					BASS_ChannelSetAttribute(BGM5, BASS_ATTRIB_VOL, 0.3f);
					BASS_ChannelPlay(BGM5, TRUE); // 播放背景音乐
				//}
			}
			break;
	}
	
}

// 更新游戏状态函数
void UpdateGame() {
	play_music(); // 调用播放音乐函数，处理背景音乐播放
	control_plane(); // 调用控制飞机函数，处理飞机移动和射击状态
	check_plane_state();

	shoot_bullet(); // 调用发射子弹函数，处理子弹发射
	
	bullet_move(); // 调用更新子弹位置函数，处理子弹移动

	if(clock() - generate_paused_time -  last_generate_enemy_time > (6000/generate_speed)) { // 如果距上次生成时间超过（6/关卡数）秒
		generate_enemy(); // 调用生成敌机函数，处理敌机生成
		last_generate_enemy_time = clock(); // 重置生成敌机时间
		generate_count++; // 增加生成计数
		generate_paused_time = 0;
		if(generate_count >= 20 * generate_speed) { // 如果生成计数超过120
			generate_speed++; // 增加生成速度
			generate_count = 0; // 重置生成计数
		}
	}
	generate_boss(); // 调用生成BOSS函数，处理BOSS生成
	update_enemy(); // 调用更新敌机位置函数，处理敌机移动
	enemy_shoot_bullet(); // 调用发射敌机子弹函数，处理敌机子弹发射
	enemy_bullet_move(); // 调用更新敌机子弹位置函数，处理敌机子弹移动
	check_enemy_bullet_collision(); // 调用敌机子弹与玩家飞机碰撞检测函数，处理敌机子弹与玩家飞机的碰撞
	check_collision(); // 调用碰撞检测函数，处理敌机与玩家飞机的碰撞
	check_bullet_collision(); // 调用碰撞检测函数，处理玩家子弹与敌机的碰撞
	check_player_life(); // 调用检测玩家生命状态函数，处理玩家飞机的生命状态
	check_player_endurance(); // 调用检测飞机耐久函数，处理飞机耐久状态
	check_player_power();// 调用检测飞机气势函数，处理飞机气势状态
	diminish_player_power(); // 调用检测飞机气势函数，处理飞机气势状态
	add_endurance(); // 调用添加耐久函数，处理飞机耐久状态

	

	update_drop_item(); // 调用更新掉落物位置函数，处理掉落物位置更新
	check_player_drop_item_collision(); // 调用玩家与掉落物碰撞检测函数，处理玩家飞机与掉落物的碰撞

	partly_paused_time = 0;
}
