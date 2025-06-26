#pragma once
#include "defines.h" // �����궨��ͷ�ļ�(�Ѱ����˱�׼ͷ�ļ�)

//void ReadMouseInput() {
//	ExMessage msg; // ����һ��ExMessage�ṹ�����msg�����ڴ洢�����Ϣ
//	peekmessage(&msg, EM_MOUSE | EM_KEY); // ��ȡ�����Ϣ�ͼ�����Ϣ
//	switch (msg.message) { // ������Ϣ���ͽ��д���
//	case WM_LBUTTONDOWN: // �����������¼�
//		for (int i = 0;i < 10;i++) {
//			//����ڰ�ť��Χ�ڰ���ʱ����Ӧ��ť��Ϊ����״̬
//			if (msg.x >= button[i].x && msg.x <= button[i].x + button[i].width &&
//				msg.y >= button[i].y && msg.y <= button[i].y + button[i].height
//				&& button[i].state == BUTTON_STATE_UP) {
//				button[i].state = BUTTON_STATE_DOWN;
//			}
//
//		}
//		break;
//	case WM_LBUTTONUP:
//		//����ɿ�ʱ�����ڰ�ť��Χ���ɿ����ð�ť��Ϊ����״̬���������а�ť�ָ�����״̬
//		for (int i = 0;i < 10;i++) {
//			if (msg.x >= button[i].x && msg.x <= button[i].x + button[i].width &&
//				msg.y >= button[i].y && msg.y <= button[i].y + button[i].height
//				/*&& button[i].state == BUTTON_STATE_DOWN*/) {
//				button[i].state = BUTTON_STATE_ACTIVE; // ���ð�ťΪ����״̬
//			}
//			else {
//				button[i].state = BUTTON_STATE_UP; // �ָ���ťΪ����״̬
//			}
//		}
//
//		break;
//	}
//}

//���ƻ�����ͣ����
void DrawPauseTitle() {
	settextstyle(50, 0, _T("����")); // ����������ʽ
	setbkmode(TRANSPARENT); //���ñ���ģʽΪ͸��
	settextcolor(WHITE); // ����������ɫΪ��ɫ
	outtextxy(SCREEN_WIDTH / 2 - 100, 150, _T("��   ͣ")); // ����Ļ���Ļ��Ʊ���
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

//���Ƽ�����ť
void DrawContinueButton() {
	settextstyle(30, 0, _T("����")); // ����������ʽ
	setbkmode(OPAQUE); // ���ñ���ģʽΪ��͸��
	setbkcolor(BLUE); // ���ð�ť������ɫΪ��ɫ
	setfillcolor(BLUE); // ���ð�ť�����ɫΪ��ɫ
	settextcolor(WHITE); // ����������ɫΪ��ɫ
	rectangle(button[CONTINUE].x, button[CONTINUE].y, button[CONTINUE].x + button[CONTINUE].width, button[CONTINUE].y + button[CONTINUE].height); // ���ư�ť�߿�
	outtextxy(button[CONTINUE].x + 50, button[CONTINUE].y + 10, button[CONTINUE].text); // �ڰ�ť�ϻ�������
}
//�������¿�ʼ��ť
void DrawRestartButton() {
	settextstyle(30, 0, _T("����")); // ����������ʽ
	setbkmode(OPAQUE); // ���ñ���ģʽΪ��͸��
	setbkcolor(BLUE); // ���ð�ť������ɫΪ��ɫ
	setfillcolor(BLUE); // ���ð�ť�����ɫΪ��ɫ
	settextcolor(WHITE); // ����������ɫΪ��ɫ
	rectangle(button[RESTART].x, button[RESTART].y, button[RESTART].x + button[RESTART].width, button[RESTART].y + button[RESTART].height); // ���ư�ť�߿�
	outtextxy(button[RESTART].x + 50, button[RESTART].y + 10, button[RESTART].text); // �ڰ�ť�ϻ�������
}
//�����˳���ť
void DrawExitButton() {
	settextstyle(30, 0, _T("����")); // ����������ʽ
	setbkmode(OPAQUE); // ���ñ���ģʽΪ��͸��
	setbkcolor(BLUE); // ���ð�ť������ɫΪ��ɫ
	setfillcolor(BLUE); // ���ð�ť�����ɫΪ��ɫ
	settextcolor(WHITE); // ����������ɫΪ��ɫ
	rectangle(button[EXIT].x, button[EXIT].y, button[EXIT].x + button[EXIT].width, button[EXIT].y + button[EXIT].height); // ���ư�ť�߿�
	outtextxy(button[EXIT].x + 50, button[EXIT].y + 10, button[EXIT].text); // �ڰ�ť�ϻ�������
}

//��������ť������������Ϸ����״̬
void ContinueGame() {
	if (button[CONTINUE].state == BUTTON_STATE_ACTIVE) {
		gamecontinue(); // ������Ϸ״̬
		game_state = GAME_STATE_PLAYING; // ������Ϸ״̬Ϊ����״̬
		button[CONTINUE].state = BUTTON_STATE_DISABLED; // ���ü�����ť
		button[RESTART].state = BUTTON_STATE_DISABLED; // �������¿�ʼ��ť
		button[EXIT].state = BUTTON_STATE_DISABLED; // �����˳���ť
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

void pause() {
	//��������Ϊԭ����20%
	BASS_ChannelSetAttribute(BGM1, BASS_ATTRIB_VOL, 0.02f); // ���ñ�����������Ϊ20%
	BASS_ChannelSetAttribute(BGM2, BASS_ATTRIB_VOL, 0.02f); // ���ñ�����������Ϊ20%
	BASS_ChannelSetAttribute(BGM3, BASS_ATTRIB_VOL, 0.02f); // ���ñ�����������Ϊ20%
	BASS_ChannelSetAttribute(BGM4, BASS_ATTRIB_VOL, 0.02f); // ���ñ�����������Ϊ20%
	BASS_ChannelSetAttribute(BGM5, BASS_ATTRIB_VOL, 0.02f); // ���ñ�����������Ϊ20%

	ReadMouseInput(); // ��ȡ�������
	ContinueGame(); // ����Ƿ������Ϸ
	RestartGame(); // ����Ƿ����¿�ʼ��Ϸ
	ExitGame(); // ����Ƿ��˳���Ϸ
}