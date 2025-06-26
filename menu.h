#pragma once
#include "defines.h" // �����궨��ͷ�ļ�(�Ѱ����˱�׼ͷ�ļ�)

void ReadMouseInput() {
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

//������Ϸ����
void DrawTitle() {
	settextstyle(50, 0, _T("����")); // ����������ʽ
	setbkmode(TRANSPARENT); //���ñ���ģʽΪ͸��
	settextcolor(WHITE); // ����������ɫΪ��ɫ
	outtextxy(SCREEN_WIDTH / 2 - 100, 150, _T("�ɻ���ս")); // ����Ļ���Ļ��Ʊ���
}






//���ƿ�ʼ��ť
void DrawStartButton() {
	
	settextstyle(30, 0, _T("����")); // ����������ʽ
	//setbkmode(TRANSPARENT); //���ñ���ģʽΪ͸��
	setbkmode(OPAQUE); // ���ñ���ģʽΪ��͸��
	setbkcolor(BLUE); // ���ð�ť������ɫΪ��ɫ
	setfillcolor(BLUE); // ���ð�ť�����ɫΪ��ɫ
	settextcolor(WHITE); // ����������ɫΪ��ɫ
	rectangle(button[0].x, button[0].y, button[0].x + button[0].width, button[0].y + button[0].height); // ���ư�ť�߿�
	outtextxy(button[0].x + 50, button[0].y + 10, button[0].text); // �ڰ�ť�ϻ�������
}
//����ʼ��ť������������Ϸ׼��״̬
void StartGame() {
	if (button[0].state == BUTTON_STATE_ACTIVE) {
		game_state = GAME_STATE_READY; // ������Ϸ״̬Ϊ׼��״̬
	}
}



void menu() {
	//DrawTitle(); // ������Ϸ����
	//DrawStartButton(); // ���ƿ�ʼ��ť
	//��������
	if (bgmmain) { // ����������ִ���
		BGMMAIN = BASS_SampleGetChannel(bgmmain, FALSE); // ��ȡ��������ͨ��
		//if (!BASS_ChannelIsActive(BGM)) { // �����������δ�ڲ���

			// ������������������Ϊ50%
		BASS_ChannelSetAttribute(BGMMAIN, BASS_ATTRIB_VOL, 1.0f);
		BASS_ChannelPlay(BGMMAIN, TRUE); // ���ű�������
		//}
	}
	ReadMouseInput(); // ��ȡ�������
	StartGame(); // ����Ƿ�ʼ��Ϸ
}