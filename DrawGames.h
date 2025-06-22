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
		&plane[0],
		&plane_mask[0]
	);

	//���Ƶл�
	for (int i = 0; i < ENEMY_MAX_NUM; i++) {
		if (enemy_plane[i].is_alive) { //����л����
			putTransparentImage(
				enemy_plane[i].plane_pos.x - PLANE_SIZE / 2,
				enemy_plane[i].plane_pos.y - PLANE_SIZE / 2,
				&enemy[0],
				&enemy_mask[0]
			);
		}
	}
	//�����ӵ�
	for (int i = 0; i < BULLET_NUM; i++) {
		if (bullet[i].is_active) { //����ӵ�����
			putTransparentImage(
				bullet[i].bullet_pos.x - PLANE_SIZE / 2,
				bullet[i].bullet_pos.y - PLANE_SIZE / 2,
				&bullet_image[0],
				&bullet_mask[0]
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

	EndBatchDraw(); //����������ͼ
}
