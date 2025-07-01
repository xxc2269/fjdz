#pragma once//���ڷ�ֹͷ�ļ�����ΰ���
#include"defines.h"//�����궨��ͷ�ļ�(�Ѱ����˱�׼ͷ�ļ�)
#include <math.h>
#include"DrawButtons.h"//���ư�ťͷ�ļ�
#include"outputrecords.h"//�����¼ͷ�ļ�

#ifndef M_PI  
#define M_PI 3.14159265358979323846 // ����Բ���ʳ���  
#endif

void DrawGame() {

	BeginBatchDraw();//��ʼ������ͼ����������Ļ�ϻ��ƶ��ͼ�����������ʾ����ֹ��˸

	setlinestyle(PS_NULL); //����������ʽΪ�ޱ߿�
	//setfillcolor(BLACK); //���������ɫΪ��ɫ
	//������Ϸ����
	 
	// ���±�������λ�� - �������
	bgScrollOffset += BG_SCROLL_SPEED; // ʹ�üӷ�ʹ�������¹���
	if (bgScrollOffset >= SCREEN_HEIGHT) {
		bgScrollOffset -= SCREEN_HEIGHT;
	}

	//���Ʊ���
	//putimage(0, 0, &bg[level-1]); //���Ʊ���ͼƬ1������ͨ������Ҫ���룩
	// ������������ - �������
	// ��float����ת��Ϊint
	int scrollPos = static_cast<int>(bgScrollOffset);

	if (game_state == GAME_STATE_PLAYING) {// �����Ϸ״̬Ϊ�����У�������������
		// ��һ�ű��� - ����Ļ�Ϸ�
		putimage(0, scrollPos - SCREEN_HEIGHT, &bg[level - 1]);

		// �ڶ��ű��� - ����Ļλ��
		putimage(0, scrollPos, &bg[level - 1]);

		// �����ű��� - ����Ļ�·��������޷��νӣ�
		putimage(0, scrollPos + SCREEN_HEIGHT, &bg[level - 1]);
	}
	else {//���������Ϸ״̬Ϊ����״̬�����ư�ɫ����
		// ��һ�ű��� - ����Ļ�Ϸ�
		putimage(0, scrollPos - SCREEN_HEIGHT, &bg_dark[level - 1]);

		// �ڶ��ű��� - ����Ļλ��
		putimage(0, scrollPos, &bg_dark[level - 1]);

		// �����ű��� - ����Ļ�·��������޷��νӣ�
		putimage(0, scrollPos + SCREEN_HEIGHT, &bg_dark[level - 1]);

	}
	if (game_state == GAME_STATE_PLAYING) {//�����Ϸ״̬Ϊ������
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
					int x2 = x1 + (SCREEN_WIDTH - 40) * ((enemy_plane[i].life * 100) / (enemy_plane[i].maxlife * 100));
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
				if (bullet[i].bullet_type == BULLET_TYPE_BIG) { //����Ǵ��ӵ�
					putTransparentImage(
						bullet[i].bullet_pos.x - MEGA_SIZE / 2,
						bullet[i].bullet_pos.y - PLANE_SIZE / 2,
						&mega_bullet_image[bullet[i].bullet_grade],
						&mega_bullet_mask[bullet[i].bullet_grade]
					);
				}
				else if (bullet[i].bullet_type == BULLET_TYPE_MEGA) { //�������˫�ӵ�
					putTransparentImage(
						bullet[i].bullet_pos.x - PLANE_SIZE / 2,
						bullet[i].bullet_pos.y - PLANE_SIZE / 2,
						&mega_time,
						&mega_time_mask
					);
				}
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
			if (enemy_bullet[i].is_active) {
				if (enemy_bullet[i].bullet_type == BULLET_TYPE_NORMAL) { //����ӵ�����
					putTransparentImage(
						enemy_bullet[i].bullet_pos.x - PLANE_SIZE / 2,
						enemy_bullet[i].bullet_pos.y - PLANE_SIZE / 2,
						&enemy_bullet_image[0],
						&enemy_bullet_mask[0]
					);
				}

				else if (enemy_bullet[i].bullet_type == BULLET_TYPE_TRACKING)
				{ //�����׷���ӵ�
					putTransparentImage(
						enemy_bullet[i].bullet_pos.x - PLANE_SIZE / 2,
						enemy_bullet[i].bullet_pos.y - PLANE_SIZE / 2,
						&enemy_bullet_image[1],
						&enemy_bullet_mask[1]
					);
				}
			}
		}

		//���Ʒ���
		RECT score_rect = { 10, 80, 200, 50 }; //����һ�������������ڻ��Ʒ���
		setbkmode(TRANSPARENT); //���ñ���ģʽΪ͸��
		char score_text[20]; //����һ���ַ����飬���ڴ洢�����ı�
		sprintf(score_text, "Score: %d", score); //��������ʽ��Ϊ�ַ���
		drawtext(score_text, &score_rect, DT_SINGLELINE | DT_VCENTER | DT_NOCLIP); //���Ʒ����ı�

		////��������ֵ
		//RECT life_rect = { 10, 90, 200, 100 }; //����һ�������������ڻ�������ֵ
		//sprintf(score_text, "Life: %.0f", my_plane.life); //������ֵ��ʽ��Ϊ�ַ���
		//drawtext(score_text, &life_rect, DT_SINGLELINE | DT_VCENTER | DT_NOCLIP); //��������ֵ�ı�
		////�����;ö�
		//RECT endurance_rect = { 10, 140, 200, 150 }; //����һ�������������ڻ����;ö�
		//sprintf(score_text, "Endurance: %.0f", my_plane.endurance); //���;öȸ�ʽ��Ϊ�ַ���
		//drawtext(score_text, &endurance_rect, DT_SINGLELINE | DT_VCENTER | DT_NOCLIP); //�����;ö��ı�
		////��������ֵ
		//RECT power_rect = { 10, 190, 200, 200 }; //����һ�������������ڻ�������ֵ
		//sprintf(score_text, "Power: %.0f", my_plane.power); //������ֵ��ʽ��Ϊ�ַ���
		//drawtext(score_text, &power_rect, DT_SINGLELINE | DT_VCENTER | DT_NOCLIP); //��������ֵ�ı�
		////���Ƶȼ�
		//RECT level_rect = { 10, 240, 200, 250 }; //����һ�������������ڻ��Ƶȼ�
		//sprintf(score_text, "Level: %d", my_plane.grade); //���ȼ���ʽ��Ϊ�ַ���
		//drawtext(score_text, &level_rect, DT_SINGLELINE | DT_VCENTER | DT_NOCLIP); //���Ƶȼ��ı�



			//����Ѫ��
		int life_x1 = 70;
		int life_y1 = 705;
		int life_x2 = life_x1 + (100) * ((my_plane.life * 100) / (my_plane.maxlife * 100));
		int life_y2 = 715;
		setfillcolor(RED); //���������ɫΪ��ɫ
		fillrectangle(life_x1, life_y1, life_x2, life_y2); //���Ƶл�Ѫ��
		//����������
		int endurance_x1 = 70;
		int endurance_y1 = 715;
		int endurance_x2 = endurance_x1 + (100) * ((my_plane.endurance * 100) / (my_plane.max_endurance * 100));
		int endurance_y2 = 725;
		setfillcolor(WHITE); //���������ɫΪ��ɫ
		fillrectangle(endurance_x1, endurance_y1, endurance_x2, endurance_y2); //����������

		//�����������������α�ʾ��
		switch (my_plane.grade) {
		case 0:
			setfillcolor(WHITE); //���������ɫΪ��ɫ
			fillcircle(43, 714, 25); //�������Ƶȼ�0��Բ��
			setfillcolor(LIGHTGREEN); //���������ɫΪ��ɫ
			if (my_plane.power > 0)fillpie(18, 689, 68, 739, 0, 2 * M_PI * (my_plane.power / 100)); //�������Ƶȼ�0������
			break;
		case 1:
			setfillcolor(LIGHTGREEN); //���������ɫΪ��ɫ
			fillcircle(43, 714, 25); //�������Ƶȼ�1��Բ��
			setfillcolor(LIGHTBLUE); //���������ɫΪ��ɫ
			if (my_plane.power > 0)fillpie(18, 689, 68, 739, 0, 2 * M_PI * (my_plane.power / 110)); //�������Ƶȼ�1������
			break;
		case 2:
			setfillcolor(LIGHTBLUE); //���������ɫΪ��ɫ
			fillcircle(43, 714, 25); //�������Ƶȼ�2��Բ��
			setfillcolor(LIGHTMAGENTA); //���������ɫΪ��ɫ
			if (my_plane.power > 0)fillpie(18, 689, 68, 739, 0, 2 * M_PI * (my_plane.power / 120)); //�������Ƶȼ�2������
			break;
		case 3:
			setfillcolor(LIGHTMAGENTA); //���������ɫΪ��ɫ
			fillcircle(43, 714, 25); //�������Ƶȼ�3��Բ��
			setfillcolor(YELLOW); //���������ɫΪ��ɫ
			if (my_plane.power > 0)fillpie(18, 689, 68, 739, 0, 2 * M_PI * (my_plane.power / 150)); //�������Ƶȼ�3������
			break;
		case 4:
			setfillcolor(YELLOW); //���������ɫΪ��ɫ
			fillcircle(43, 714, 25); //�������Ƶȼ�4��Բ��
			setfillcolor(LIGHTRED); //���������ɫΪ��ɫ
			if (my_plane.power > 0)fillpie(18, 689, 68, 739, 0, 2 * M_PI * (my_plane.power / 400)); //�������Ƶȼ�4������
			break;
		case 5:
			setfillcolor(WHITE); //���������ɫΪ��ɫ
			fillcircle(43, 714, 25); //�������Ƶȼ�0��Բ��
			setfillcolor(LIGHTRED); //���������ɫΪ��ɫ
			if (my_plane.power > 0)fillpie(18, 689, 68, 739, 0, 2 * M_PI * (my_plane.power / 400)); //�������Ƶȼ�5������
			break;
		}

		putTransparentImage(
			20,
			690,
			&plane[my_plane.grade],
			&plane_mask[my_plane.grade]
		);// ���Ʒɻ����Ƶȼ�ͼ��

		//����С�����򡢴������򡢲����򡢴󲹸���λ��ΪBOSS��λ�ã�BOSS����ʱ����
		//if (boss_is_alive == false) { //���BOSS�����
		for (int i = 0; i < ITEM_NUM; i++) {
			if (drop_item[i].is_active) { //�����Ʒ����
				switch (drop_item[i].item_type) { //������Ʒ���ͻ��Ʋ�ͬ��ͼ��
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
	
		switch(game_state) { //������Ϸ״̬���Ʋ�ͬ�Ľ���
		case GAME_STATE_MAIN_MENU:
			//���˵�����
			DrawButton(START); //���ƿ�ʼ��ť
			DrawTitle(); //���Ʊ���
			if (!is_login) {
				DrawButton(LOGIN); //���Ƶ�¼��ť
				DrawButton(REGISTER); //����ע�ᰴť
			}
			else {
				DrawUsername(); // �����û���
				DrawButton(LOGOFF); // �����˳���¼��ť
			}
			
			DrawButton(EXIT); // �����˳���ť
			break;
			case GAME_STATE_PLAYING: //��Ϸ������
				break;
			case GAME_STATE_PAUSED: //��Ϸ��ͣ
				DrawPauseTitle(); // ������ͣ����
				DrawButton(CONTINUE); // ���Ƽ�����ť
				DrawButton(RESTART); // �������¿�ʼ��ť
				DrawButton(EXIT); // �����˳���ť
				DrawButton(HOME); // ���Ʒ�����ҳ��ť
				break;
			case GAME_STATE_GAME_OVER: //��Ϸ����
				DrawOverTitle(); // ������Ϸ��������
				DrawFinalScore(); // �������յ÷�
				DrawButton(RESTART); // �������¿�ʼ��ť
				DrawButton(EXIT); // �����˳���ť
				DrawButton(HOME); // ���Ʒ�����ҳ��ť
				if(is_login)outputrecords(); // �����Ϸ��¼
				break;
			
		}






	EndBatchDraw(); //����������ͼ
}
