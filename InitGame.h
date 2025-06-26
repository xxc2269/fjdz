#pragma once//���ڷ�ֹͷ�ļ�����ΰ���
#include"defines.h"//�����궨��ͷ�ļ�(�Ѱ����˱�׼ͷ�ļ�)
//��ʼ����Ϸ����
void init_game() {
	score = 0; //��ʼ������Ϊ0
	level = 1; //��ʼ���ؿ�Ϊ1
	my_plane.plane_pos.x = SCREEN_WIDTH / 2 - PLANE_SIZE / 2; //���÷ɻ���ʼλ��Ϊ��Ļ����
	my_plane.plane_pos.y = SCREEN_HEIGHT - PLANE_SIZE; //���÷ɻ���ʼλ��Ϊ��Ļ�ײ�
	my_plane.speed = PLANE_SPEED; //���÷ɻ��ٶ�
	my_plane.bullet_num = 0; //�����ӵ�����
	my_plane.bullet_speed = 5.0; //�����ӵ��ٶ�
	my_plane.life = 100; //���÷ɻ�����ֵ
	my_plane.maxlife = 100; //���÷ɻ��������ֵ
	my_plane.size = PLANE_SIZE; //���÷ɻ���С
	my_plane.height = PLANE_SIZE; //���÷ɻ��߶�
	my_plane.power = 0; //���÷ɻ�����
	my_plane.endurance = 100; //���÷ɻ��;ö�
	my_plane.max_endurance = 100; //���÷ɻ�����;ö�
	my_plane.plane_state = PLANE_STATE_NORMAL; //���÷ɻ�״̬Ϊ����


	//��ʼ���л���ر���
	enemy_num = 0; //��ʼ���л�����Ϊ0
	for (int i = 0; i < ENEMY_MAX_NUM; i++) { //��ʼ���л�
		enemy_plane[i].is_alive = false; //���õл����״̬Ϊfalse
		enemy_plane[i].plane_type = ENEMY_TYPE_NORMAL; //���õл�����Ϊ��ͨ�л�
	}
	for (int i = 0; i < BULLET_NUM; i++) { //��ʼ���ӵ�
		bullet[i].is_active = false; //�����ӵ�����״̬Ϊfalse
		bullet[i].bullet_type = BULLET_TYPE_NORMAL; //�����ӵ�����Ϊ��ͨ�ӵ�
		bullet[i].bullet_damage = 10; //�����ӵ��˺�
		bullet[i].bullet_size = 50; //�����ӵ���С
	}

	//��ʼ���ռ���Ʒ
	for (int i = 0; i < ITEM_NUM; i++) { //��ʼ���ռ���Ʒ
		item[i].is_active = false; //������Ʒ����״̬Ϊfalse
		item[i].item_type = ITEM_TYPE_SMALL_LIFE; //������Ʒ����ΪС������
		item[i].item_size = 10; //������Ʒ��С
		item[i].item_speed = 0.3; //������Ʒ�ƶ��ٶ�
	}

	start_time = clock(); //��¼��Ϸ��ʼʱ��
	srand((unsigned)time(NULL)); //�������������
}

