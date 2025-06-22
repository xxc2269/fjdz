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
		&plane[0],
		&plane_mask[0]
	);

	//绘制敌机
	for (int i = 0; i < ENEMY_MAX_NUM; i++) {
		if (enemy_plane[i].is_alive) { //如果敌机存活
			putTransparentImage(
				enemy_plane[i].plane_pos.x - PLANE_SIZE / 2,
				enemy_plane[i].plane_pos.y - PLANE_SIZE / 2,
				&enemy[0],
				&enemy_mask[0]
			);
		}
	}
	//绘制子弹
	for (int i = 0; i < BULLET_NUM; i++) {
		if (bullet[i].is_active) { //如果子弹激活
			putTransparentImage(
				bullet[i].bullet_pos.x - PLANE_SIZE / 2,
				bullet[i].bullet_pos.y - PLANE_SIZE / 2,
				&bullet_image[0],
				&bullet_mask[0]
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

	EndBatchDraw(); //结束批量绘图
}
