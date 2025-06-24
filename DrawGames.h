#pragma once//���ڷ�ֹͷ�ļ�����ΰ���
#include"defines.h"//�����궨��ͷ�ļ�(�Ѱ����˱�׼ͷ�ļ�)

void DrawGame() {

	BeginBatchDraw();//��ʼ������ͼ����������Ļ�ϻ��ƶ��ͼ�����������ʾ����ֹ��˸

	//setfillcolor(BLACK); //���������ɫΪ��ɫ
	//������Ϸ����
	//���Ʊ���
	putimage(0, 0, &bg[0]); //���Ʊ���ͼƬ1������ͨ������Ҫ���룩

	//���Ʒɻ�������ֻ��plane[0]��plane_mask[0]�����趯̬�л������е����±꣩
	putTransparentImage(
		my_plane.plane_pos.x - PLANE_SIZE / 2,
		my_plane.plane_pos.y - PLANE_SIZE / 2,
		&plane[my_plane.grade],
		&plane_mask[my_plane.grade]
	);

	//���Ƶл�
	for (int i = 0; i < ENEMY_MAX_NUM; i++) {
		if (enemy_plane[i].is_alive) { //����л����
			//����Ѫ��
			if (enemy_plane[i].plane_type != ENEMY_TYPE_BOSS) {
			int x1 = enemy_plane[i].plane_pos.x - enemy_plane[i].size / 2;//�л�Ѫ����ʼλ��x����
			int y1 = enemy_plane[i].plane_pos.y - enemy_plane[i].size / 2 - 10;//�л�Ѫ����ʼλ��y����
			int x2 = x1 + enemy_plane[i].size * ((enemy_plane[i].life * 100) / (enemy_plane[i].maxlife * 100));//�л�Ѫ������λ��x����
			int y2 = enemy_plane[i].plane_pos.y - enemy_plane[i].size / 2;//�л�Ѫ������λ��y����

			setfillcolor(RED); //���������ɫΪ��ɫ
			fillrectangle(x1, y1, x2, y2); //���Ƶл�Ѫ��
		}	
			else {
				int x1 = 20;
				int y1 = 20;
				int x2 = x1 + (SCREEN_WIDTH-40) * ((enemy_plane[i].life * 100) / (enemy_plane[i].maxlife * 100));
				int y2 = 40;
				setfillcolor(RED); //���������ɫΪ��ɫ
				fillrectangle(x1, y1, x2, y2); //���Ƶл�Ѫ��
			}


			if (enemy_plane[i].plane_type == ENEMY_TYPE_BOSS) { //�����BOSS
				putTransparentImage(
					enemy_plane[i].plane_pos.x - enemy_plane[i].size / 2,
					enemy_plane[i].plane_pos.y - enemy_plane[i].size / 2,
					&boss[enemy_plane[i].style],
					&boss_mask[enemy_plane[i].style]
				);
			}
			else if (enemy_plane[i].plane_type == ENEMY_TYPE_ELITE) { //����Ǿ�Ӣ�л�
				putTransparentImage(
					enemy_plane[i].plane_pos.x - enemy_plane[i].size / 2,
					enemy_plane[i].plane_pos.y - enemy_plane[i].size / 2,
					&elite[enemy_plane[i].style],
					&elite_mask[enemy_plane[i].style]
				);
			}
			else { //��ͨ�л�
				putTransparentImage(
					enemy_plane[i].plane_pos.x - enemy_plane[i].size / 2,
					enemy_plane[i].plane_pos.y - enemy_plane[i].size / 2,
					&enemy[enemy_plane[i].style],
					&enemy_mask[enemy_plane[i].style]
				);
			}
		}
	}
	//�����ӵ�
	for (int i = 0; i < BULLET_NUM; i++) {
		if (bullet[i].is_active) { //����ӵ�����
			if(bullet[i].bullet_type == BULLET_TYPE_BIG) { //����Ǵ��ӵ�
				putTransparentImage(
					bullet[i].bullet_pos.x - MEGA_SIZE  / 2,
					bullet[i].bullet_pos.y - PLANE_SIZE / 2,
					&mega_bullet_image[bullet[i].bullet_grade],
					&mega_bullet_mask[bullet[i].bullet_grade]
				);
			}
			//else if (bullet[i].bullet_type == BULLET_TYPE_MEGA) { //�������˫�ӵ�
			//	putTransparentImage(
			//		bullet[i].bullet_pos.x - PLANE_SIZE / 2,
			//		bullet[i].bullet_pos.y - PLANE_SIZE / 2,
			//		&mega_bullet_image[my_plane.grade],
			//		&mega_bullet_mask[my_plane.grade]
			//	);
			//}
			//else if (bullet[i].bullet_type == BULLET_TYPE_LASER) { //����Ǽ���
			//	putTransparentImage(
			//		bullet[i].bullet_pos.x - PLANE_SIZE / 2,
			//		bullet[i].bullet_pos.y - PLANE_SIZE / 2,
			//		&laser_bullet_image[my_plane.grade],
			//		&laser_bullet_mask[my_plane.grade]
			//	);
			//}
			else //��ͨ�ӵ�
			putTransparentImage(
				bullet[i].bullet_pos.x - PLANE_SIZE / 2,
				bullet[i].bullet_pos.y - PLANE_SIZE / 2,
				&bullet_image[bullet[i].bullet_grade],
				&bullet_mask[bullet[i].bullet_grade]
			);
		}
	}

	for (int i = 0; i < BULLET_NUM; i++) {
		if (enemy_bullet[i].is_active) { //����ӵ�����
			putTransparentImage(
				enemy_bullet[i].bullet_pos.x - PLANE_SIZE / 2,
				enemy_bullet[i].bullet_pos.y - PLANE_SIZE / 2,
				&enemy_bullet_image[0],
				&enemy_bullet_mask[0]
			);
		}
	}

	//���Ʒ���
	RECT score_rect = { 10, 10, 200, 50 }; //����һ�������������ڻ��Ʒ���
	setbkmode(TRANSPARENT); //���ñ���ģʽΪ͸��
	char score_text[20]; //����һ���ַ����飬���ڴ洢�����ı�
	sprintf(score_text, "Score: %d", score); //��������ʽ��Ϊ�ַ���
	drawtext(score_text, &score_rect, DT_SINGLELINE | DT_VCENTER | DT_NOCLIP); //���Ʒ����ı�

	//��������ֵ
	RECT life_rect = { 10, 60, 200, 100 }; //����һ�������������ڻ�������ֵ
	sprintf(score_text, "Life: %.0f", my_plane.life); //������ֵ��ʽ��Ϊ�ַ���
	drawtext(score_text, &life_rect, DT_SINGLELINE | DT_VCENTER | DT_NOCLIP); //��������ֵ�ı�
	//�����;ö�
	RECT endurance_rect = { 10, 110, 200, 150 }; //����һ�������������ڻ����;ö�
	sprintf(score_text, "Endurance: %.0f", my_plane.endurance); //���;öȸ�ʽ��Ϊ�ַ���
	drawtext(score_text, &endurance_rect, DT_SINGLELINE | DT_VCENTER | DT_NOCLIP); //�����;ö��ı�
	//��������ֵ
	RECT power_rect = { 10, 160, 200, 200 }; //����һ�������������ڻ�������ֵ
	sprintf(score_text, "Power: %.0f", my_plane.power); //������ֵ��ʽ��Ϊ�ַ���
	drawtext(score_text, &power_rect, DT_SINGLELINE | DT_VCENTER | DT_NOCLIP); //��������ֵ�ı�
	//���Ƶȼ�
	RECT level_rect = { 10, 210, 200, 250 }; //����һ�������������ڻ��Ƶȼ�
	sprintf(score_text, "Level: %d", my_plane.grade); //���ȼ���ʽ��Ϊ�ַ���
	drawtext(score_text, &level_rect, DT_SINGLELINE | DT_VCENTER | DT_NOCLIP); //���Ƶȼ��ı�


	EndBatchDraw(); //����������ͼ
}
