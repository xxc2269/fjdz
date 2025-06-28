#pragma once
#include "defines.h" // �����궨��ͷ�ļ�(�Ѱ����˱�׼ͷ�ļ�)

void PauseReadMouseInput() {
	ExMessage msg; // ����һ��ExMessage�ṹ�����msg�����ڴ洢�����Ϣ
	peekmessage(&msg, EM_MOUSE | EM_KEY); // ��ȡ�����Ϣ�ͼ�����Ϣ
	switch (msg.message) { // ������Ϣ���ͽ��д���
	case WM_LBUTTONDOWN: // �����������¼�
		for (int i = 0;i < 10;i++) {
			//����ڰ�ť��Χ�ڰ���ʱ����Ӧ��ť��Ϊ����״̬
			if (msg.x >= button[i].x && msg.x <= button[i].x + button[i].width &&
				msg.y >= button[i].y && msg.y <= button[i].y + button[i].height
				&& button[i].state == BUTTON_STATE_UP) {
				button[i].state = BUTTON_STATE_DOWN;
			}

		}
		break;
	case WM_LBUTTONUP:
		//����ɿ�ʱ�����ڰ�ť��Χ���ɿ����ð�ť��Ϊ����״̬���������а�ť�ָ�����״̬
		for (int i = 0;i < 10;i++) {
			if (msg.x >= button[i].x && msg.x <= button[i].x + button[i].width &&
				msg.y >= button[i].y && msg.y <= button[i].y + button[i].height
				/*&& button[i].state == BUTTON_STATE_DOWN*/) {
				button[i].state = BUTTON_STATE_ACTIVE; // ���ð�ťΪ����״̬
			}
			else {
				button[i].state = BUTTON_STATE_UP; // �ָ���ťΪ����״̬
			}
		}

		break;
	}
}



void gamecontinue() {
	//�����ӵ�����ʼλ��
	for (int i = 0;i < BULLET_NUM;i++) {
		bullet[i].start_pos.x = bullet[i].bullet_pos.x; // �����ӵ�λ��Ϊ�ɻ�λ��
		bullet[i].start_pos.y = bullet[i].bullet_pos.y; // �����ӵ�λ��Ϊ�ɻ�λ��
		bullet[i].generate_time = clock(); // ��¼�ӵ�����ʱ��

	}
	//���õл�����ʼλ��
	for (int i = 0;i < ENEMY_MAX_NUM;i++) {
		enemy_plane[i].start_pos.x = enemy_plane[i].plane_pos.x; // ���õл�λ��Ϊ�ɻ�λ��
		enemy_plane[i].start_pos.y = enemy_plane[i].plane_pos.y; // ���õл�λ��Ϊ�ɻ�λ��
		enemy_plane[i].generate_time = clock(); // ��¼�л�����ʱ��
	}
	//���õ�����Ʒ����ʼλ��
	for (int i = 0;i < ITEM_NUM;i++) {
		drop_item[i].start_pos.x = drop_item[i].item_pos.x; // ������Ʒλ��Ϊ�ɻ�λ��
		drop_item[i].start_pos.y = drop_item[i].item_pos.y; // ������Ʒλ��Ϊ�ɻ�λ��
		drop_item[i].generate_time = clock(); // ��¼��Ʒ����ʱ��

	}
	//���õл��ӵ�����ʼλ��
	for (int i = 0;i < ENEMY_MAX_NUM;i++) {
		enemy_bullet[i].start_pos.x = enemy_bullet[i].bullet_pos.x; // ���õл��ӵ�λ��Ϊ�ɻ�λ��
		enemy_bullet[i].start_pos.y = enemy_bullet[i].bullet_pos.y; // ���õл��ӵ�λ��Ϊ�ɻ�λ��
		enemy_bullet[i].generate_time = clock(); // ��¼�л��ӵ�����ʱ��
	}
}


//��������ť������������Ϸ����״̬
void ContinueGame() {
	if (button[CONTINUE].state == BUTTON_STATE_ACTIVE) {
		gamecontinue(); // ������Ϸ״̬
		game_state = GAME_STATE_PLAYING; // ������Ϸ״̬Ϊ����״̬
		button[CONTINUE].state = BUTTON_STATE_DISABLED; // ���ü�����ť
		button[RESTART].state = BUTTON_STATE_DISABLED; // �������¿�ʼ��ť
		button[EXIT].state = BUTTON_STATE_DISABLED; // �����˳���ť
		total_paused_time += clock() - start_paused_time; // ��������ͣʱ��
	}
}

//�����¿�ʼ��ť������������Ϸ׼��״̬
void RestartGame() {
	if (button[RESTART].state == BUTTON_STATE_ACTIVE) {
		game_state = GAME_STATE_READY; // ������Ϸ״̬Ϊ׼��״̬
		button[CONTINUE].state = BUTTON_STATE_DISABLED; // ���ü�����ť
		button[RESTART].state = BUTTON_STATE_DISABLED; // �������¿�ʼ��ť
		button[EXIT].state = BUTTON_STATE_DISABLED; // �����˳���ť
	}
}

//���˳���ť��������˳���Ϸ
void ExitGame() {
	if (button[EXIT].state == BUTTON_STATE_ACTIVE) {
		exit(0); // �˳���Ϸ
	}
}

//��������ҳ��ť������򷵻���ҳ
void HomeGame() {
	if (button[HOME].state == BUTTON_STATE_ACTIVE) {
		game_state = GAME_STATE_MAIN_MENU; // ������Ϸ״̬Ϊ������
		level = 1; // ���ùؿ�Ϊ1
		generate_speed = 1; // ���������ٶ�Ϊ1
		button[CONTINUE].state = BUTTON_STATE_DISABLED; // ���ü�����ť
		button[RESTART].state = BUTTON_STATE_DISABLED; // �������¿�ʼ��ť
		button[EXIT].state = BUTTON_STATE_DISABLED; // �����˳���ť
		button[HOME].state = BUTTON_STATE_DISABLED; // ���÷�����ҳ��ť
		//ֹͣ������Ϸ������
		BASS_SampleStop(bgm1); // ֹͣ��������1
		BASS_SampleStop(bgm2); // ֹͣ��������2
		BASS_SampleStop(bgm3); // ֹͣ��������3
		BASS_SampleStop(bgm4); // ֹͣ��������4
		BASS_SampleStop(bgm5); // ֹͣ��������5
		BASS_SampleStop(bgmover); // ֹͣ��Ϸ��������
		back_to_home_time = clock(); // ��¼������ҳʱ��

	}
}

void pause() {
	//��������Ϊԭ����20%


	PauseReadMouseInput(); // ��ȡ�������
	ContinueGame(); // ����Ƿ������Ϸ
	RestartGame(); // ����Ƿ����¿�ʼ��Ϸ
	ExitGame(); // ����Ƿ��˳���Ϸ
	HomeGame(); // ����Ƿ񷵻���ҳ
}