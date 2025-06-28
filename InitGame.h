#pragma once//���ڷ�ֹͷ�ļ�����ΰ���
#include"defines.h"//�����궨��ͷ�ļ�(�Ѱ����˱�׼ͷ�ļ�)
//��ʼ����Ϸ����
void init_game() {
	score = 0; //��ʼ������Ϊ0
	level = 1; //��ʼ���ؿ�Ϊ1
	generate_count = 0; //��ʼ�����ɼ���Ϊ0
	generate_speed = 1; //��ʼ�������ٶ�Ϊ1
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
	my_plane.grade = 0; //���÷ɻ��ȼ�
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
		drop_item[i].is_active = false; //������Ʒ����״̬Ϊfalse
		drop_item[i].item_type = ITEM_TYPE_SMALL_LIFE; //������Ʒ����ΪС������
		drop_item[i].item_size = 10; //������Ʒ��С
		drop_item[i].item_speed = 0.3; //������Ʒ�ƶ��ٶ�
	}

	start_time = clock(); //��¼��Ϸ��ʼʱ��
	start_paused_time = clock(); //��¼�ϴ���ͣʱ��
	total_paused_time = 0; //��ʼ����ͣʱ��Ϊ0
	last_complete_time = clock(); //��¼�ϴ�ͨ��ʱ��
	boss_is_alive = false; //BOSS�Ƿ���
	srand((unsigned)time(NULL)); //�������������


	button[0] = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 150, 200, 50, "��ʼ��Ϸ" }; // ���忪ʼ��ť
	button[1] = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 200, 100, 50, "��¼" }; // �����¼��ť
	button[2] = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 250, 200, 50, "ע��" }; // ����ע�ᰴť
	button[3] = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 250, 200, 50, "�˳���¼" , BUTTON_STATE_DISABLED }; // �����˳���¼��ť
	button[4] = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 150, 200, 50, "����" ,BUTTON_STATE_DISABLED }; // ���������ť
	button[5] = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 300, 200, 50, "�˳���Ϸ"  }; // �����˳���ť
	button[6] = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 200, 200, 50, "���¿�ʼ" ,BUTTON_STATE_DISABLED }; // �������¿�ʼ��ť
	button[7] = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 250, 200, 50, "������ҳ" ,BUTTON_STATE_DISABLED }; // �������а�ť

	//��Ϊ׼��״̬����ʼ��Ϸ
	if (game_state == GAME_STATE_READY) {
		BASS_SampleStop(bgmmain); // ֹͣ��������
		BASS_SampleStop(bgmover); // ֹͣ��Ϸ��������
		//BASS_SampleFree(bgmmain); // �ͷű���������Դ
		game_state = GAME_STATE_PLAYING; //����Ϸ״̬����Ϊ������
		button[START].state = BUTTON_STATE_DISABLED; // ���ÿ�ʼ��ť
		button[LOGIN].state = BUTTON_STATE_DISABLED; // ���õ�¼��ť
		button[REGISTER].state = BUTTON_STATE_DISABLED; // ����ע�ᰴť
		button[LOGOFF].state = BUTTON_STATE_DISABLED; // �����˳���¼��ť
		button[EXIT].state = BUTTON_STATE_DISABLED; // �����˳���ť
		
	}
}

