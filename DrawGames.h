#pragma once//用于防止头文件被多次包含
#include"defines.h"//包含宏定义头文件(已包含了标准头文件)
#include <math.h>
#include"DrawButtons.h"//绘制按钮头文件
#include"outputrecords.h"//输出记录头文件

#ifndef M_PI  
#define M_PI 3.14159265358979323846 // 定义圆周率常量  
#endif

void DrawGame() {

	BeginBatchDraw();//开始批量绘图，可以在屏幕上绘制多个图像而不立即显示，防止闪烁

	setlinestyle(PS_NULL); //设置线条样式为无边框
	//setfillcolor(BLACK); //设置填充颜色为黑色
	//绘制游戏界面
	 
	// 更新背景滚动位置 - 纵向滚动
	bgScrollOffset += BG_SCROLL_SPEED; // 使用加法使背景向下滚动
	if (bgScrollOffset >= SCREEN_HEIGHT) {
		bgScrollOffset -= SCREEN_HEIGHT;
	}

	//绘制背景
	//putimage(0, 0, &bg[level-1]); //绘制背景图片1（背景通常不需要掩码）
	// 绘制流动背景 - 纵向滚动
	// 将float坐标转换为int
	int scrollPos = static_cast<int>(bgScrollOffset);

	if (game_state == GAME_STATE_PLAYING) {// 如果游戏状态为进行中，绘制正常背景
		// 第一张背景 - 在屏幕上方
		putimage(0, scrollPos - SCREEN_HEIGHT, &bg[level - 1]);

		// 第二张背景 - 在屏幕位置
		putimage(0, scrollPos, &bg[level - 1]);

		// 第三张背景 - 在屏幕下方（用于无缝衔接）
		putimage(0, scrollPos + SCREEN_HEIGHT, &bg[level - 1]);
	}
	else {//否则如果游戏状态为其他状态，绘制暗色背景
		// 第一张背景 - 在屏幕上方
		putimage(0, scrollPos - SCREEN_HEIGHT, &bg_dark[level - 1]);

		// 第二张背景 - 在屏幕位置
		putimage(0, scrollPos, &bg_dark[level - 1]);

		// 第三张背景 - 在屏幕下方（用于无缝衔接）
		putimage(0, scrollPos + SCREEN_HEIGHT, &bg_dark[level - 1]);

	}
	if (game_state == GAME_STATE_PLAYING) {//如果游戏状态为进行中
		//绘制飞机（假设只用plane[0]和plane_mask[0]，如需动态切换请自行调整下标）
		putTransparentImage(
			my_plane.plane_pos.x - PLANE_SIZE / 2,
			my_plane.plane_pos.y - PLANE_SIZE / 2,
			&plane[my_plane.grade],
			&plane_mask[my_plane.grade]
		);

		//绘制敌机
		for (int i = 0; i < ENEMY_MAX_NUM; i++) {
			if (enemy_plane[i].is_alive) { //如果敌机存活
				//绘制血条
				if (enemy_plane[i].plane_type != ENEMY_TYPE_BOSS) {
					int x1 = enemy_plane[i].plane_pos.x - enemy_plane[i].size / 2;//敌机血条起始位置x坐标
					int y1 = enemy_plane[i].plane_pos.y - enemy_plane[i].size / 2 - 10;//敌机血条起始位置y坐标
					int x2 = x1 + enemy_plane[i].size * ((enemy_plane[i].life * 100) / (enemy_plane[i].maxlife * 100));//敌机血条结束位置x坐标
					int y2 = enemy_plane[i].plane_pos.y - enemy_plane[i].size / 2;//敌机血条结束位置y坐标

					setfillcolor(RED); //设置填充颜色为红色
					fillrectangle(x1, y1, x2, y2); //绘制敌机血条
				}
				else {
					int x1 = 20;
					int y1 = 20;
					int x2 = x1 + (SCREEN_WIDTH - 40) * ((enemy_plane[i].life * 100) / (enemy_plane[i].maxlife * 100));
					int y2 = 40;
					setfillcolor(RED); //设置填充颜色为红色
					fillrectangle(x1, y1, x2, y2); //绘制敌机血条
				}


				if (enemy_plane[i].plane_type == ENEMY_TYPE_BOSS) { //如果是BOSS
					putTransparentImage(
						enemy_plane[i].plane_pos.x - enemy_plane[i].size / 2,
						enemy_plane[i].plane_pos.y - enemy_plane[i].size / 2,
						&boss[enemy_plane[i].style],
						&boss_mask[enemy_plane[i].style]
					);
				}
				else if (enemy_plane[i].plane_type == ENEMY_TYPE_ELITE) { //如果是精英敌机
					putTransparentImage(
						enemy_plane[i].plane_pos.x - enemy_plane[i].size / 2,
						enemy_plane[i].plane_pos.y - enemy_plane[i].size / 2,
						&elite[enemy_plane[i].style],
						&elite_mask[enemy_plane[i].style]
					);
				}
				else { //普通敌机
					putTransparentImage(
						enemy_plane[i].plane_pos.x - enemy_plane[i].size / 2,
						enemy_plane[i].plane_pos.y - enemy_plane[i].size / 2,
						&enemy[enemy_plane[i].style],
						&enemy_mask[enemy_plane[i].style]
					);
				}
			}
		}
		//绘制子弹
		for (int i = 0; i < BULLET_NUM; i++) {
			if (bullet[i].is_active) { //如果子弹激活
				if (bullet[i].bullet_type == BULLET_TYPE_BIG) { //如果是大子弹
					putTransparentImage(
						bullet[i].bullet_pos.x - MEGA_SIZE / 2,
						bullet[i].bullet_pos.y - PLANE_SIZE / 2,
						&mega_bullet_image[bullet[i].bullet_grade],
						&mega_bullet_mask[bullet[i].bullet_grade]
					);
				}
				else if (bullet[i].bullet_type == BULLET_TYPE_MEGA) { //如果是无双子弹
					putTransparentImage(
						bullet[i].bullet_pos.x - PLANE_SIZE / 2,
						bullet[i].bullet_pos.y - PLANE_SIZE / 2,
						&mega_time,
						&mega_time_mask
					);
				}
				//else if (bullet[i].bullet_type == BULLET_TYPE_LASER) { //如果是激光
				//	putTransparentImage(
				//		bullet[i].bullet_pos.x - PLANE_SIZE / 2,
				//		bullet[i].bullet_pos.y - PLANE_SIZE / 2,
				//		&laser_bullet_image[my_plane.grade],
				//		&laser_bullet_mask[my_plane.grade]
				//	);
				//}

				else //普通子弹
					putTransparentImage(
						bullet[i].bullet_pos.x - PLANE_SIZE / 2,
						bullet[i].bullet_pos.y - PLANE_SIZE / 2,
						&bullet_image[bullet[i].bullet_grade],
						&bullet_mask[bullet[i].bullet_grade]
					);
			}
		}

		for (int i = 0; i < BULLET_NUM; i++) {
			if (enemy_bullet[i].is_active) {
				if (enemy_bullet[i].bullet_type == BULLET_TYPE_NORMAL) { //如果子弹激活
					putTransparentImage(
						enemy_bullet[i].bullet_pos.x - PLANE_SIZE / 2,
						enemy_bullet[i].bullet_pos.y - PLANE_SIZE / 2,
						&enemy_bullet_image[0],
						&enemy_bullet_mask[0]
					);
				}

				else if (enemy_bullet[i].bullet_type == BULLET_TYPE_TRACKING)
				{ //如果是追踪子弹
					putTransparentImage(
						enemy_bullet[i].bullet_pos.x - PLANE_SIZE / 2,
						enemy_bullet[i].bullet_pos.y - PLANE_SIZE / 2,
						&enemy_bullet_image[1],
						&enemy_bullet_mask[1]
					);
				}
			}
		}

		//绘制分数
		RECT score_rect = { 10, 80, 200, 50 }; //定义一个矩形区域，用于绘制分数
		setbkmode(TRANSPARENT); //设置背景模式为透明
		char score_text[20]; //定义一个字符数组，用于存储分数文本
		sprintf(score_text, "Score: %d", score); //将分数格式化为字符串
		drawtext(score_text, &score_rect, DT_SINGLELINE | DT_VCENTER | DT_NOCLIP); //绘制分数文本

		////绘制生命值
		//RECT life_rect = { 10, 90, 200, 100 }; //定义一个矩形区域，用于绘制生命值
		//sprintf(score_text, "Life: %.0f", my_plane.life); //将生命值格式化为字符串
		//drawtext(score_text, &life_rect, DT_SINGLELINE | DT_VCENTER | DT_NOCLIP); //绘制生命值文本
		////绘制耐久度
		//RECT endurance_rect = { 10, 140, 200, 150 }; //定义一个矩形区域，用于绘制耐久度
		//sprintf(score_text, "Endurance: %.0f", my_plane.endurance); //将耐久度格式化为字符串
		//drawtext(score_text, &endurance_rect, DT_SINGLELINE | DT_VCENTER | DT_NOCLIP); //绘制耐久度文本
		////绘制气势值
		//RECT power_rect = { 10, 190, 200, 200 }; //定义一个矩形区域，用于绘制气势值
		//sprintf(score_text, "Power: %.0f", my_plane.power); //将气势值格式化为字符串
		//drawtext(score_text, &power_rect, DT_SINGLELINE | DT_VCENTER | DT_NOCLIP); //绘制气势值文本
		////绘制等级
		//RECT level_rect = { 10, 240, 200, 250 }; //定义一个矩形区域，用于绘制等级
		//sprintf(score_text, "Level: %d", my_plane.grade); //将等级格式化为字符串
		//drawtext(score_text, &level_rect, DT_SINGLELINE | DT_VCENTER | DT_NOCLIP); //绘制等级文本



			//绘制血条
		int life_x1 = 70;
		int life_y1 = 705;
		int life_x2 = life_x1 + (100) * ((my_plane.life * 100) / (my_plane.maxlife * 100));
		int life_y2 = 715;
		setfillcolor(RED); //设置填充颜色为红色
		fillrectangle(life_x1, life_y1, life_x2, life_y2); //绘制敌机血条
		//绘制耐力条
		int endurance_x1 = 70;
		int endurance_y1 = 715;
		int endurance_x2 = endurance_x1 + (100) * ((my_plane.endurance * 100) / (my_plane.max_endurance * 100));
		int endurance_y2 = 725;
		setfillcolor(WHITE); //设置填充颜色为白色
		fillrectangle(endurance_x1, endurance_y1, endurance_x2, endurance_y2); //绘制耐力条

		//绘制气势条（用扇形表示）
		switch (my_plane.grade) {
		case 0:
			setfillcolor(WHITE); //设置填充颜色为白色
			fillcircle(43, 714, 25); //绘制气势等级0的圆形
			setfillcolor(LIGHTGREEN); //设置填充颜色为绿色
			if (my_plane.power > 0)fillpie(18, 689, 68, 739, 0, 2 * M_PI * (my_plane.power / 100)); //绘制气势等级0的扇形
			break;
		case 1:
			setfillcolor(LIGHTGREEN); //设置填充颜色为绿色
			fillcircle(43, 714, 25); //绘制气势等级1的圆形
			setfillcolor(LIGHTBLUE); //设置填充颜色为蓝色
			if (my_plane.power > 0)fillpie(18, 689, 68, 739, 0, 2 * M_PI * (my_plane.power / 110)); //绘制气势等级1的扇形
			break;
		case 2:
			setfillcolor(LIGHTBLUE); //设置填充颜色为蓝色
			fillcircle(43, 714, 25); //绘制气势等级2的圆形
			setfillcolor(LIGHTMAGENTA); //设置填充颜色为紫色
			if (my_plane.power > 0)fillpie(18, 689, 68, 739, 0, 2 * M_PI * (my_plane.power / 120)); //绘制气势等级2的扇形
			break;
		case 3:
			setfillcolor(LIGHTMAGENTA); //设置填充颜色为紫色
			fillcircle(43, 714, 25); //绘制气势等级3的圆形
			setfillcolor(YELLOW); //设置填充颜色为黄色
			if (my_plane.power > 0)fillpie(18, 689, 68, 739, 0, 2 * M_PI * (my_plane.power / 150)); //绘制气势等级3的扇形
			break;
		case 4:
			setfillcolor(YELLOW); //设置填充颜色为黄色
			fillcircle(43, 714, 25); //绘制气势等级4的圆形
			setfillcolor(LIGHTRED); //设置填充颜色为红色
			if (my_plane.power > 0)fillpie(18, 689, 68, 739, 0, 2 * M_PI * (my_plane.power / 400)); //绘制气势等级4的扇形
			break;
		case 5:
			setfillcolor(WHITE); //设置填充颜色为白色
			fillcircle(43, 714, 25); //绘制气势等级0的圆形
			setfillcolor(LIGHTRED); //设置填充颜色为红色
			if (my_plane.power > 0)fillpie(18, 689, 68, 739, 0, 2 * M_PI * (my_plane.power / 400)); //绘制气势等级5的扇形
			break;
		}

		putTransparentImage(
			20,
			690,
			&plane[my_plane.grade],
			&plane_mask[my_plane.grade]
		);// 绘制飞机气势等级图标

		//绘制小生命球、大生命球、补给球、大补给球，位置为BOSS的位置，BOSS死亡时生成
		//if (boss_is_alive == false) { //如果BOSS不存活
		for (int i = 0; i < ITEM_NUM; i++) {
			if (drop_item[i].is_active) { //如果物品激活
				switch (drop_item[i].item_type) { //根据物品类型绘制不同的图标
				case ITEM_TYPE_SMALL_LIFE:
					putTransparentImage(
						drop_item[i].item_pos.x - PLANE_SIZE / 2,
						drop_item[i].item_pos.y - PLANE_SIZE / 2,
						&life_image,
						&life_mask
					);
					break;
				case ITEM_TYPE_BIG_LIFE:
					putTransparentImage(
						drop_item[i].item_pos.x - PLANE_SIZE / 2,
						drop_item[i].item_pos.y - PLANE_SIZE / 2,
						&mega_life_image,
						&mega_life_mask
					);
					break;
				case ITEM_TYPE_SUPPLY:
					putTransparentImage(
						drop_item[i].item_pos.x - PLANE_SIZE / 2,
						drop_item[i].item_pos.y - PLANE_SIZE / 2,
						&power_image,
						&power_mask
					);
					break;
				case ITEM_TYPE_BIG_SUPPLY:
					putTransparentImage(
						drop_item[i].item_pos.x - PLANE_SIZE / 2,
						drop_item[i].item_pos.y - PLANE_SIZE / 2,
						&mega_power_image,
						&mega_power_mask
					);
					break;
				}
			}
		}
	}
	//}
	
		switch(game_state) { //根据游戏状态绘制不同的界面
		case GAME_STATE_MAIN_MENU:
			//主菜单界面
			DrawButton(START); //绘制开始按钮
			DrawTitle(); //绘制标题
			if (!is_login) {
				DrawButton(LOGIN); //绘制登录按钮
				DrawButton(REGISTER); //绘制注册按钮
			}
			else {
				DrawUsername(); // 绘制用户名
				DrawButton(LOGOFF); // 绘制退出登录按钮
			}
			
			DrawButton(EXIT); // 绘制退出按钮
			break;
			case GAME_STATE_PLAYING: //游戏进行中
				break;
			case GAME_STATE_PAUSED: //游戏暂停
				DrawPauseTitle(); // 绘制暂停标题
				DrawButton(CONTINUE); // 绘制继续按钮
				DrawButton(RESTART); // 绘制重新开始按钮
				DrawButton(EXIT); // 绘制退出按钮
				DrawButton(HOME); // 绘制返回主页按钮
				break;
			case GAME_STATE_GAME_OVER: //游戏结束
				DrawOverTitle(); // 绘制游戏结束标题
				DrawFinalScore(); // 绘制最终得分
				DrawButton(RESTART); // 绘制重新开始按钮
				DrawButton(EXIT); // 绘制退出按钮
				DrawButton(HOME); // 绘制返回主页按钮
				if(is_login)outputrecords(); // 输出游戏记录
				break;
			
		}






	EndBatchDraw(); //结束批量绘图
}
