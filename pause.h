#pragma once
#include "defines.h" // �����궨��ͷ�ļ�(�Ѱ����˱�׼ͷ�ļ�)



void gamecontinue() {
		game_state = GAME_STATE_PLAYING; // ������Ϸ״̬Ϊ����״̬
		button[CONTINUE].state = BUTTON_STATE_DISABLED; // ���ü�����ť
		button[RESTART].state = BUTTON_STATE_DISABLED; // �������¿�ʼ��ť
		button[EXIT].state = BUTTON_STATE_DISABLED; // �����˳���ť
		total_paused_time += clock() - start_paused_time; // ��������ͣʱ��
		partly_paused_time = clock() - start_paused_time;// ���㱾����ͣʱ��
		generate_paused_time = partly_paused_time;
		shoot_paused_time = partly_paused_time;
}




//��������ť������������Ϸ����״̬
void ContinueGame() {
	if (button[CONTINUE].state == BUTTON_STATE_ACTIVE) {
		gamecontinue(); // ������Ϸ״̬
		
	}
}

//�����¿�ʼ��ť������������Ϸ׼��״̬
void RestartGame() {
	if (button[RESTART].state == BUTTON_STATE_ACTIVE) {
		if (button[RESTART].state == BUTTON_STATE_ACTIVE) {
			if (MessageBox(NULL, "ȷ��Ҫ���¿�ʼ��\n�㽫ʧȥ��ǰ���ȣ�", "���¿�ʼ", MB_YESNO | MB_ICONQUESTION) == IDYES) {
				game_state = GAME_STATE_READY; // ������Ϸ״̬Ϊ׼��״̬
				button[CONTINUE].state = BUTTON_STATE_DISABLED; // ���ü�����ť
				button[RESTART].state = BUTTON_STATE_DISABLED; // �������¿�ʼ��ť
				button[EXIT].state = BUTTON_STATE_DISABLED; // �����˳���ť
			}
			else button[RESTART].state = BUTTON_STATE_UP; // ����û�ѡ���ؿ���Ϸ�����ؿ���Ϸ��ť״̬����Ϊ����
		}

	}
}

//���˳���ť��������˳���Ϸ
void ExitGame() {
	if (button[EXIT].state == BUTTON_STATE_ACTIVE) {
		if (MessageBox(NULL, "ȷ��Ҫ�˳���Ϸ��\n�㽫ʧȥ��ǰ���ȣ�", "�˳���Ϸ", MB_YESNO | MB_ICONQUESTION) == IDYES) {
			exit(0); // �˳���Ϸ
		}
		else button[EXIT].state = BUTTON_STATE_UP; // ����û�ѡ���˳���Ϸ�����˳���Ϸ��ť״̬����Ϊ����
	}
}

//��������ҳ��ť������򷵻���ҳ
void HomeGame() {
	if (button[HOME].state == BUTTON_STATE_ACTIVE) {
		if (button[HOME].state == BUTTON_STATE_ACTIVE) {
			if (MessageBox(NULL, "ȷ��Ҫ������ҳ��\n�㽫ʧȥ��ǰ���ȣ�", "������ҳ", MB_YESNO | MB_ICONQUESTION) == IDYES) {
				game_state = GAME_STATE_MAIN_MENU; // ������Ϸ״̬Ϊ������
		level = 1; // ���ùؿ�Ϊ1
		generate_speed = 1; // ���������ٶ�Ϊ1
		button[CONTINUE].state = BUTTON_STATE_DISABLED; // ���ü�����ť
		button[RESTART].state = BUTTON_STATE_DISABLED; // �������¿�ʼ��ť
		//button[EXIT].state = BUTTON_STATE_DISABLED; // �����˳���ť
		button[HOME].state = BUTTON_STATE_DISABLED; // ���÷�����ҳ��ť
		button[START].state = BUTTON_STATE_UP; // ���ÿ�ʼ��ť״̬Ϊ����
		if(is_login) {
			button[LOGOFF].state = BUTTON_STATE_UP; // �����˳���¼��ť״̬Ϊ����
		}
		else {
			button[LOGIN].state = BUTTON_STATE_UP; // ���õ�¼��ť״̬Ϊ����
			button[REGISTER].state = BUTTON_STATE_UP; // ����ע�ᰴť״̬Ϊ����
		}
		//ֹͣ������Ϸ������
		BASS_SampleStop(bgm1); // ֹͣ��������1
		BASS_SampleStop(bgm2); // ֹͣ��������2
		BASS_SampleStop(bgm3); // ֹͣ��������3
		BASS_SampleStop(bgm4); // ֹͣ��������4
		BASS_SampleStop(bgm5); // ֹͣ��������5
		BASS_SampleStop(bgmover); // ֹͣ��Ϸ��������
		back_to_home_time = clock(); // ��¼������ҳʱ��
			}
			else button[HOME].state = BUTTON_STATE_UP; // ����û�ѡ���˳���Ϸ�����˳���Ϸ��ť״̬����Ϊ����
		}
		

	}
}

void PauseReadMouseInput() {
	static int mouseDownIndex = -1; // ��¼����ʱ�İ�ť����
	ExMessage msg;
	peekmessage(&msg, EM_MOUSE | EM_KEY);

	switch (msg.message) {
	case WM_MOUSEMOVE:
		for (int i = 0; i < 10; i++) {
			// ����ڰ�ť��Χ���Ұ�ťδ����
			if (msg.x >= button[i].x && msg.x <= button[i].x + button[i].width &&
				msg.y >= button[i].y && msg.y <= button[i].y + button[i].height &&
				button[i].state != BUTTON_STATE_DISABLED) {
				if (button[i].state != BUTTON_STATE_DOWN) // ����ʱ������ͣ
					button[i].state = BUTTON_STATE_HOVER;
			}
			else {
				// ��겻�ڰ�ť�ϣ��Ҳ��ǰ���״̬���ָ�Ϊ����
				if (button[i].state == BUTTON_STATE_HOVER)
					button[i].state = BUTTON_STATE_UP;
			}
		}
		break;

	case WM_LBUTTONDOWN:
		mouseDownIndex = -1;
		for (int i = 0; i < 10; i++) {
			if (msg.x >= button[i].x && msg.x <= button[i].x + button[i].width &&
				msg.y >= button[i].y && msg.y <= button[i].y + button[i].height &&
				button[i].state == BUTTON_STATE_HOVER &&
				button[i].state != BUTTON_STATE_DISABLED) {
				button[i].state = BUTTON_STATE_DOWN;
				mouseDownIndex = i; // ��¼���µİ�ť
			}
			else {
				// ������ť�ָ�Ϊ����
				if (button[i].state == BUTTON_STATE_DOWN)
					button[i].state = BUTTON_STATE_UP;
			}
		}
		break;

	case WM_LBUTTONUP:
		for (int i = 0; i < 10; i++) {
			// ֻ����갴�º��ɿ�����ͬһ����ť�ϲż���
			if (i == mouseDownIndex &&
				msg.x >= button[i].x && msg.x <= button[i].x + button[i].width &&
				msg.y >= button[i].y && msg.y <= button[i].y + button[i].height &&
				button[i].state == BUTTON_STATE_DOWN &&
				button[i].state != BUTTON_STATE_DISABLED) {
				button[i].state = BUTTON_STATE_ACTIVE;
			}
			else if (button[i].state != BUTTON_STATE_DISABLED) {
				button[i].state = BUTTON_STATE_UP;
			}
		}
		mouseDownIndex = -1;
		break;

	case WM_KEYDOWN:
		//����ESC��ʱ��ȡ����ͣ״̬
		if (msg.vkcode == VK_ESCAPE) {
			gamecontinue();
		}
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