#pragma once//用于防止头文件被多次包含
#include"defines.h"//包含宏定义头文件(已包含了标准头文件)

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
		break;
	case WM_LBUTTONUP:
		// 鼠标左键松开事件
		if (my_plane.plane_state == PLANE_STATE_SHOOTING) { // 如果飞机状态为射击
			my_plane.plane_state = PLANE_STATE_NORMAL; // 切换到正常状态
		}
		break;
	}
}

//发射子弹
void shoot_bullet() {
	if (my_plane.plane_state == PLANE_STATE_SHOOTING && my_plane.endurance > 0) {
		for (int i = 0; i <= my_plane.bullet_num; i++) {
			if (!bullet[i].is_active && clock() - my_plane.last_shoot_time > 200) { // 如果子弹未激活且距离上次射击时间超过200毫秒
				// 子弹发射音效
				if (bullet_sound) {
					DWORD chan = BASS_SampleGetChannel(bullet_sound, FALSE);
					BASS_ChannelPlay(chan, TRUE);
				}
				bullet[i].is_active = true; // 激活子弹
				bullet[i].start_pos.x = my_plane.plane_pos.x + PLANE_SIZE / 2; // 设置子弹位置为飞机位置
				bullet[i].bullet_pos.x = bullet[i].start_pos.x; // 设置子弹位置为起始位置
				bullet[i].start_pos.y = my_plane.plane_pos.y - PLANE_SIZE / 2; // 设置子弹位置为飞机位置
				bullet[i].bullet_pos.y = bullet[i].start_pos.y; // 设置子弹位置为起始位置
				bullet[i].bullet_speed = 0.3; // 设置子弹速度
				my_plane.endurance -= 1; // 减少飞机耐久度
				bullet[i].generate_time = clock(); // 记录子弹生成时间
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
				bullet[i].bullet_pos.y = bullet[i].start_pos.y - (clock() - bullet[i].generate_time) * bullet[i].bullet_speed; // 更新子弹位置
				if (bullet[i].bullet_pos.y < 0) { // 如果子弹超出屏幕上边界
					bullet[i].is_active = false; // 禁用子弹
					char teststr[50];
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
				enemy_plane[i].size = PLANE_SIZE; // 设置敌机大小
				enemy_plane[i].height = PLANE_SIZE; // 设置敌机高度
				enemy_plane[i].start_pos.x = rand() % (SCREEN_WIDTH - enemy_plane[i].size)+25; // 随机生成敌机位置
				enemy_plane[i].plane_pos.x = enemy_plane[i].start_pos.x; // 设置敌机位置为起始位置
				enemy_plane[i].start_pos.y = -enemy_plane[i].height; // 设置敌机初始位置在屏幕上方
				enemy_plane[i].plane_pos.y = enemy_plane[i].start_pos.y; // 设置敌机位置为起始位置
				enemy_plane[i].speed = 0.1; // 设置敌机速度
				enemy_plane[i].plane_type = ENEMY_TYPE_NORMAL; // 设置敌机类型为普通敌机
				enemy_plane[i].maxlife = 50; // 设置敌机最大生命值
				enemy_plane[i].life = 50; // 设置敌机生命值
				enemy_plane[i].generate_time = clock(); // 记录敌机生成时间

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
			enemy_plane[i].plane_pos.y = enemy_plane[i].start_pos.y + (clock()-enemy_plane[i].generate_time)*enemy_plane[i].speed; // 更新敌机位置
			if (enemy_plane[i].plane_type == ENEMY_TYPE_BOSS && enemy_plane[i].plane_pos.y > 200) {
				enemy_plane[i].plane_pos.y = 200; // 如果是BOSS敌机，限制其位置在屏幕上方200像素
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
		if (enemy_plane[j].is_alive && clock() - enemy_plane[j].generate_time > 1000 && clock() - enemy_plane[j].last_shoot_time > 1000) { // 如果敌机激活且距离生成时间超过1000毫秒
			for (int i = 0; i < BULLET_NUM; i++) {
				if (!enemy_bullet[i].is_active) { // 如果敌机子弹未激活
					enemy_bullet[i].is_active = true; // 激活敌机子弹
					enemy_bullet[i].start_pos.x = enemy_plane[j].plane_pos.x + enemy_plane[i].size / 2; // 设置敌机子弹位置为敌机位置
					enemy_bullet[i].bullet_pos.x = enemy_bullet[i].start_pos.x; // 设置敌机子弹位置为起始位置
					enemy_bullet[i].start_pos.y = enemy_plane[j].plane_pos.y + enemy_plane[i].height / 2; // 设置敌机子弹位置为敌机位置
					enemy_bullet[i].bullet_pos.y = enemy_bullet[i].start_pos.y; // 设置敌机子弹位置为起始位置
					enemy_bullet[i].bullet_speed = 0.3; // 设置敌机子弹速度
					enemy_bullet[i].generate_time = clock(); // 记录敌机子弹生成时间
					enemy_plane[j].last_shoot_time = clock(); // 记录最后一次射击时间
					enemy_bullet_num++; // 增加敌机子弹数量
					break; // 退出循环
				}
			}
		//enemy_plane[j].generate_time = clock(); // 更新敌机生成时间
			break; // 退出循环
		}
	}
}

//更新敌机子弹位置
void enemy_bullet_move() {

		// 更新子弹位置
		for (int i = 0; i <= ENEMY_MAX_NUM; i++) {
			if (enemy_bullet[i].is_active) { // 如果子弹激活
				enemy_bullet[i].bullet_pos.y = enemy_bullet[i].start_pos.y + (clock() - enemy_bullet[i].generate_time) * enemy_bullet[i].bullet_speed; // 更新子弹位置
				if (enemy_bullet[i].bullet_pos.y > SCREEN_HEIGHT) { // 如果子弹超出屏幕下边界
					enemy_bullet[i].is_active = false; // 禁用子弹
					enemy_bullet_num--; // 减少敌机子弹数量
				}
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
				my_plane.life -= 1; // 玩家飞机受到伤害
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
				my_plane.life -= 10; // 玩家飞机受到伤害
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
				if (enemy_plane[j].is_alive) { // 如果敌机激活
					// 检测子弹与敌机的碰撞
					if (enemy_plane[j].plane_type == ENEMY_TYPE_BOSS) {// 如果是BOSS敌机
						if (abs(bullet[i].bullet_pos.x - enemy_plane[j].plane_pos.x) < enemy_plane[j].size / 2 &&
							abs(bullet[i].bullet_pos.y - enemy_plane[j].plane_pos.y) < enemy_plane[j].height / 2) {
							enemy_plane[j].life -= bullet[i].bullet_damage; // 敌机受到伤害
							if (enemy_plane[i].life > 0) {
								// 子弹击中音效
								if (bullet_hit_sound) {
									DWORD chan = BASS_SampleGetChannel(bullet_hit_sound, FALSE);
									BASS_ChannelPlay(chan, TRUE);
								}
							}
							bullet[i].is_active = false; // 禁用子弹
							my_plane.bullet_num--; // 减少子弹数量
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
								boss_is_alive = false; // BOSS激活状态设置为false
							}
							break; // 退出循环
						}
					}
					else {// 如果是普通敌机或精英敌机
						if (abs(bullet[i].bullet_pos.x - enemy_plane[j].plane_pos.x) < enemy_plane[j].size &&
							abs(bullet[i].bullet_pos.y - enemy_plane[j].plane_pos.y) < enemy_plane[j].height){
							enemy_plane[j].life -= bullet[i].bullet_damage; // 敌机受到伤害
							if (enemy_plane[i].life > 0) {
								// 子弹击中音效
								if (bullet_hit_sound) {
									DWORD chan = BASS_SampleGetChannel(bullet_hit_sound, FALSE);
									BASS_ChannelPlay(chan, TRUE);
								}
							}
							bullet[i].is_active = false; // 禁用子弹
							my_plane.bullet_num--; // 减少子弹数量
							if (enemy_plane[j].life <= 0) { // 如果敌机生命值小于等于0
								// 敌机被击落音效
								if (enemy_down_sound) {
									DWORD chan = BASS_SampleGetChannel(enemy_down_sound, FALSE);
									BASS_ChannelPlay(chan, TRUE);
								}
								enemy_plane[j].is_alive = false; // 禁用敌机
								enemy_num--; // 减少敌机数量
								score += enemy_plane[j].maxlife;// 增加分数
							}
							break; // 退出循环
							}

					}
				}
			}
		}
	}
}

//游戏开始2分钟后生成BOSS
void generate_boss() {
	if (clock() - last_complete_time > 90000 && !boss_is_alive) { // 如果游戏开始超过2分钟且BOSS未激活
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
				enemy_plane[i].maxlife = BOSS_LIFE; // 设置BOSS最大生命值
				enemy_plane[i].life = BOSS_LIFE; // 设置BOSS生命值
				enemy_plane[i].generate_time = clock(); // 记录BOSS生成时间
				boss_is_alive = true; // BOSS激活状态设置为true
				srand(time(NULL));
				if (level <= 3) {
					enemy_plane[i].style = 0;
				} else {
					
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
		PlaySound("src/sound/game_over.wav", NULL, SND_FILENAME | SND_ASYNC | SND_NOWAIT); // 播放游戏结束音效
		MessageBox(NULL, "Game Over!", "提示", MB_OK); // 弹出游戏结束提示框
		exit(0); // 退出游戏
	}
}
//耐久的加减，正常状态每秒恢复15耐久
void add_endurance() {
	
	if (my_plane.plane_state == PLANE_STATE_NORMAL && clock()-last_added_time > 200 && clock()-my_plane.last_shoot_time > 300) { // 如果飞机状态为正常
		
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
		my_plane.plane_state = PLANE_STATE_NORMAL; // 切换到正常状态
		
	}
}

//播放音乐
void play_music() {
	if (bgm1) { // 如果背景音乐存在
		BGM = BASS_SampleGetChannel(bgm1, FALSE); // 获取背景音乐通道
		//if (!BASS_ChannelIsActive(BGM)) { // 如果背景音乐未在播放
			
			// 将背景音乐音量设置为50%
			BASS_ChannelSetAttribute(BGM, BASS_ATTRIB_VOL, 0.5f);
			BASS_ChannelPlay(BGM, TRUE); // 播放背景音乐
		//}
	}
}

// 更新游戏状态函数
void UpdateGame() {

	control_plane(); // 调用控制飞机函数，处理飞机移动和射击状态

	shoot_bullet(); // 调用发射子弹函数，处理子弹发射
	
	bullet_move(); // 调用更新子弹位置函数，处理子弹移动

	if(clock() - last_generate_enemy_time > (5000/level)) { // 如果距上次生成时间超过（5/关卡数）秒
		generate_enemy(); // 调用生成敌机函数，处理敌机生成
		last_generate_enemy_time = clock(); // 重置生成敌机时间
	}

	update_enemy(); // 调用更新敌机位置函数，处理敌机移动
	enemy_shoot_bullet(); // 调用发射敌机子弹函数，处理敌机子弹发射
	enemy_bullet_move(); // 调用更新敌机子弹位置函数，处理敌机子弹移动
	check_enemy_bullet_collision(); // 调用敌机子弹与玩家飞机碰撞检测函数，处理敌机子弹与玩家飞机的碰撞
	check_collision(); // 调用碰撞检测函数，处理敌机与玩家飞机的碰撞
	check_bullet_collision(); // 调用碰撞检测函数，处理玩家子弹与敌机的碰撞
	check_player_life(); // 调用检测玩家生命状态函数，处理玩家飞机的生命状态
	check_player_endurance(); // 调用检测飞机耐久函数，处理飞机耐久状态


	check_player_endurance(); // 调用检测飞机耐久函数，处理飞机耐久状态
	add_endurance(); // 调用添加耐久函数，处理飞机耐久状态

	generate_boss(); // 调用生成BOSS函数，处理BOSS生成


	play_music(); // 调用播放音乐函数，处理背景音乐播放
}
