#pragma once//用于防止头文件被多次包含
#include"defines.h"//包含宏定义头文件(已包含了标准头文件)

void DrawGame() {

	BeginBatchDraw();//开始批量绘图，可以在屏幕上绘制多个图像而不立即显示，防止闪烁

	//setfillcolor(BLACK); //设置填充颜色为黑色
	//绘制游戏界面
	//绘制背景
	putimage(0, 0, &bg[0]); //绘制背景图片1（背景通常不需要掩码）

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
				int x2 = x1 + (SCREEN_WIDTH-40) * ((enemy_plane[i].life * 100) / (enemy_plane[i].maxlife * 100));
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
			if(bullet[i].bullet_type == BULLET_TYPE_BIG) { //如果是大子弹
				putTransparentImage(
					bullet[i].bullet_pos.x - MEGA_SIZE  / 2,
					bullet[i].bullet_pos.y - PLANE_SIZE / 2,
					&mega_bullet_image[bullet[i].bullet_grade],
					&mega_bullet_mask[bullet[i].bullet_grade]
				);
			}
			//else if (bullet[i].bullet_type == BULLET_TYPE_MEGA) { //如果是无双子弹
			//	putTransparentImage(
			//		bullet[i].bullet_pos.x - PLANE_SIZE / 2,
			//		bullet[i].bullet_pos.y - PLANE_SIZE / 2,
			//		&mega_bullet_image[my_plane.grade],
			//		&mega_bullet_mask[my_plane.grade]
			//	);
			//}
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
		if (enemy_bullet[i].is_active) { //如果子弹激活
			putTransparentImage(
				enemy_bullet[i].bullet_pos.x - PLANE_SIZE / 2,
				enemy_bullet[i].bullet_pos.y - PLANE_SIZE / 2,
				&enemy_bullet_image[0],
				&enemy_bullet_mask[0]
			);
		}
	}

	//绘制分数
	RECT score_rect = { 10, 10, 200, 50 }; //定义一个矩形区域，用于绘制分数
	setbkmode(TRANSPARENT); //设置背景模式为透明
	char score_text[20]; //定义一个字符数组，用于存储分数文本
	sprintf(score_text, "Score: %d", score); //将分数格式化为字符串
	drawtext(score_text, &score_rect, DT_SINGLELINE | DT_VCENTER | DT_NOCLIP); //绘制分数文本

	//绘制生命值
	RECT life_rect = { 10, 60, 200, 100 }; //定义一个矩形区域，用于绘制生命值
	sprintf(score_text, "Life: %.0f", my_plane.life); //将生命值格式化为字符串
	drawtext(score_text, &life_rect, DT_SINGLELINE | DT_VCENTER | DT_NOCLIP); //绘制生命值文本
	//绘制耐久度
	RECT endurance_rect = { 10, 110, 200, 150 }; //定义一个矩形区域，用于绘制耐久度
	sprintf(score_text, "Endurance: %.0f", my_plane.endurance); //将耐久度格式化为字符串
	drawtext(score_text, &endurance_rect, DT_SINGLELINE | DT_VCENTER | DT_NOCLIP); //绘制耐久度文本
	//绘制气势值
	RECT power_rect = { 10, 160, 200, 200 }; //定义一个矩形区域，用于绘制气势值
	sprintf(score_text, "Power: %.0f", my_plane.power); //将气势值格式化为字符串
	drawtext(score_text, &power_rect, DT_SINGLELINE | DT_VCENTER | DT_NOCLIP); //绘制气势值文本
	//绘制等级
	RECT level_rect = { 10, 210, 200, 250 }; //定义一个矩形区域，用于绘制等级
	sprintf(score_text, "Level: %d", my_plane.grade); //将等级格式化为字符串
	drawtext(score_text, &level_rect, DT_SINGLELINE | DT_VCENTER | DT_NOCLIP); //绘制等级文本


	EndBatchDraw(); //结束批量绘图
}
