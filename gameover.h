#pragma once
#include "defines.h" // �����궨��ͷ�ļ�(�Ѱ����˱�׼ͷ�ļ�)
#include"add.h"// ������ӷ�����ͷ�ļ�
#include"findAll.h"// ������ѯ���м�¼��ͷ�ļ�

void OverReadMouseInput() {
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
		exit(0); // �˳���Ϸ
	}
}

void OverHomeGame() {
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