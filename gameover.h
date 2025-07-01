#pragma once
#include "defines.h" // �����궨��ͷ�ļ�(�Ѱ����˱�׼ͷ�ļ�)
#include"add.h"// ������ӷ�����ͷ�ļ�
#include"findAll.h"// ������ѯ���м�¼��ͷ�ļ�

void OverReadMouseInput() {
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
	}
}






////�������¿�ʼ��ť
//void DrawRestartButton() {
//	settextstyle(30, 0, _T("����")); // ����������ʽ
//	setbkmode(OPAQUE); // ���ñ���ģʽΪ��͸��
//	setbkcolor(BLUE); // ���ð�ť������ɫΪ��ɫ
//	setfillcolor(BLUE); // ���ð�ť�����ɫΪ��ɫ
//	settextcolor(WHITE); // ����������ɫΪ��ɫ
//	rectangle(button[RESTART].x, button[RESTART].y, button[RESTART].x + button[RESTART].width, button[RESTART].y + button[RESTART].height); // ���ư�ť�߿�
//	outtextxy(button[RESTART].x + 50, button[RESTART].y + 10, button[RESTART].text); // �ڰ�ť�ϻ�������
//}
////�����˳���ť
//void DrawExitButton() {
//	settextstyle(30, 0, _T("����")); // ����������ʽ
//	setbkmode(OPAQUE); // ���ñ���ģʽΪ��͸��
//	setbkcolor(BLUE); // ���ð�ť������ɫΪ��ɫ
//	setfillcolor(BLUE); // ���ð�ť�����ɫΪ��ɫ
//	settextcolor(WHITE); // ����������ɫΪ��ɫ
//	rectangle(button[EXIT].x, button[EXIT].y, button[EXIT].x + button[EXIT].width, button[EXIT].y + button[EXIT].height); // ���ư�ť�߿�
//	outtextxy(button[EXIT].x + 50, button[EXIT].y + 10, button[EXIT].text); // �ڰ�ť�ϻ�������
//}


//�����¿�ʼ��ť������������Ϸ׼��״̬
void OverRestartGame() {
	if (button[RESTART].state == BUTTON_STATE_ACTIVE) {
		game_state = GAME_STATE_READY; // ������Ϸ״̬Ϊ׼��״̬
		button[CONTINUE].state = BUTTON_STATE_DISABLED; // ���ü�����ť
		button[RESTART].state = BUTTON_STATE_DISABLED; // �������¿�ʼ��ť
		button[EXIT].state = BUTTON_STATE_DISABLED; // �����˳���ť
	}
}

//���˳���ť��������˳���Ϸ
void OverExitGame() {
	if (button[EXIT].state == BUTTON_STATE_ACTIVE) {
		if (MessageBox(NULL, "ȷ��Ҫ�˳���Ϸ��", "�˳���Ϸ", MB_YESNO | MB_ICONQUESTION) == IDYES) {
			exit(0); // �˳���Ϸ
		}
		else button[EXIT].state = BUTTON_STATE_UP; // ����û�ѡ���˳���Ϸ�����˳���Ϸ��ť״̬����Ϊ����
	}
}

void OverHomeGame() {
	if (button[HOME].state == BUTTON_STATE_ACTIVE) {
		game_state = GAME_STATE_MAIN_MENU; // ������Ϸ״̬Ϊ������
		level = 1; // ���ùؿ�Ϊ1
		generate_speed = 1; // ���������ٶ�Ϊ1
		button[CONTINUE].state = BUTTON_STATE_DISABLED; // ���ü�����ť
		button[RESTART].state = BUTTON_STATE_DISABLED; // �������¿�ʼ��ť
		//button[EXIT].state = BUTTON_STATE_DISABLED; // �����˳���ť
		button[HOME].state = BUTTON_STATE_DISABLED; // ���÷�����ҳ��ť
		button[START].state = BUTTON_STATE_UP; // ���ÿ�ʼ��ť״̬Ϊ����
		if (is_login) {
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
}

void gameover() {
	//ֹͣ������Ϸ������
	BASS_SampleStop(bgm1); // ֹͣ��������1
	BASS_SampleStop(bgm2); // ֹͣ��������2
	BASS_SampleStop(bgm3); // ֹͣ��������3
	BASS_SampleStop(bgm4); // ֹͣ��������4
	BASS_SampleStop(bgm5); // ֹͣ��������5
	
	//������Ϸ��������
	if (bgmover) { // ����������ִ���
		BGMOVER = BASS_SampleGetChannel(bgmover, FALSE); // ��ȡ��������ͨ��
		//if (!BASS_ChannelIsActive(BGM)) { // �����������δ�ڲ���

			// ������������������Ϊ70%
		BASS_ChannelSetAttribute(BGMOVER, BASS_ATTRIB_VOL, 0.7f);
		BASS_ChannelPlay(BGMOVER, TRUE); // ���ű�������
		//}
	}
	if (is_login && ready_to_insert) {// ����ѵ�¼������ӷ���
		add_score();
		findAll(); // ��ѯ���м�¼
		ready_to_insert = false;// ׼����������״̬����Ϊfalse
	}
	OverReadMouseInput(); // ��ȡ�������
	OverRestartGame(); // ����Ƿ����¿�ʼ��Ϸ
	OverExitGame(); // ����Ƿ��˳���Ϸ
	OverHomeGame(); // ����Ƿ񷵻���ҳ
}