#pragma once//���ڷ�ֹͷ�ļ�����ΰ���
#include"defines.h"//�����궨��ͷ�ļ�(�Ѱ����˱�׼ͷ�ļ�)

void DrawGame() {

	BeginBatchDraw();//��ʼ������ͼ����������Ļ�ϻ��ƶ��ͼ�����������ʾ����ֹ��˸

	setfillcolor(BLACK); //���������ɫΪ��ɫ
	//������Ϸ����
	//���Ʊ���
	putimage(0, 0, &bg[0]); //���Ʊ���ͼƬ1
	//���Ʒɻ�
	putimage(my_plane.plane_pos.x - PLANE_SIZE / 2, my_plane.plane_pos.y - PLANE_SIZE / 2, &plane[0], SRCPAINT); //���Ʒɻ�ͼƬ1
	//SRCPAINT��ʾԴͼ���Ŀ��ͼ�����ɫ��ӣ�����͸��Ч��
	//���Ƶл�
	for (int i = 0; i < ENEMY_MAX_NUM; i++) {
		if (enemy_plane[i].is_alive) { //����л����
			putimage(enemy_plane[i].plane_pos.x - PLANE_SIZE / 2, enemy_plane[i].plane_pos.y - PLANE_SIZE / 2, &enemy[0], SRCPAINT); //���Ƶл�ͼƬ1
		}
	}
	//�����ӵ�
	for (int i = 0; i < BULLET_NUM; i++) {
		if (bullet[i].is_active) { //����ӵ�����
			putimage(bullet[i].bullet_pos.x - PLANE_SIZE / 2, bullet[i].bullet_pos.y - PLANE_SIZE / 2, &bullet_image[0], SRCPAINT); //�����ӵ�ͼƬ1
		}
	}
	//���Ʒ���
	RECT score_rect = { 10, 10, 200, 50 }; //����һ�������������ڻ��Ʒ���
	setbkmode(TRANSPARENT); //���ñ���ģʽΪ͸��
	char score_text[20]; //����һ���ַ����飬���ڴ洢�����ı�
	sprintf(score_text, "Score: %d", score); //��������ʽ��Ϊ�ַ���
	drawtext(score_text, &score_rect, DT_SINGLELINE | DT_VCENTER | DT_NOCLIP); //���Ʒ����ı�

	EndBatchDraw(); //����������ͼ
}
