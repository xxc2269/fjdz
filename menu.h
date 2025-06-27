#pragma once
#include "defines.h" // �����궨��ͷ�ļ�(�Ѱ����˱�׼ͷ�ļ�)
#include"login.h"// ������¼ͷ�ļ�
#include"register.h"// ����ע��ͷ�ļ�

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









//����ʼ��ť������������Ϸ׼��״̬
void StartGame() {
	if (button[START].state == BUTTON_STATE_ACTIVE) {
		if(!is_login) { // ���δ��¼
			if (MessageBox(NULL, "δ��¼״̬�²����¼�ɼ�\nȷ��Ҫ��ʼ��", "��ʾ", MB_YESNO | MB_ICONQUESTION) != IDYES) // ������ʾ��
			{ 
			button[START].state = BUTTON_STATE_UP; // ���ÿ�ʼ��ť״̬Ϊ����
			return; // ���أ���������Ϸ׼��״̬
			}
				
		}
		game_state = GAME_STATE_READY; // ������Ϸ״̬Ϊ׼��״̬
	}
}
//����¼��ť�������򿪵�¼����
void LoginGame() {
	if (button[LOGIN].state == BUTTON_STATE_ACTIVE) {
		// �򿪵�¼���ڵĴ���
		
		button[LOGIN].state = BUTTON_STATE_UP; // ��¼�󽫵�¼��ť״̬����Ϊ����
		userlogin(); // ���õ�¼����
	}
}
//��ע�ᰴť��������ע�ᴰ��
void RegisterGame() {
	if (button[REGISTER].state == BUTTON_STATE_ACTIVE && clock() - back_to_home_time > 1000) {// ȷ����ť����������ٵȴ�1��
		// ��ע�ᴰ�ڵĴ���
		button[REGISTER].state = BUTTON_STATE_UP; // ע���ע�ᰴť״̬����Ϊ����
		userregister(); // ����ע�ắ��
	}
	else {
		button[REGISTER].state = BUTTON_STATE_UP; // ���ע�ᰴťδ���������״̬����Ϊ����
	}
}
//���˳���¼��ť��������˳���¼״̬
void LogoffGame() {
	if (button[LOGOFF].state == BUTTON_STATE_ACTIVE && clock() - back_to_home_time > 1000) {// ȷ����ť����������ٵȴ�1��
		if (MessageBox(NULL, "ȷ��Ҫ�˳���¼��", "�˳���¼", MB_YESNO | MB_ICONQUESTION) == IDYES) {
			is_login = false; // ���õ�¼״̬Ϊfalse
			button[LOGOFF].state = BUTTON_STATE_DISABLED; // �����˳���¼��ť
			button[LOGIN].state = BUTTON_STATE_UP; // �����¼��ť
			button[REGISTER].state = BUTTON_STATE_UP; // ����ע�ᰴť
		}
		
	}
	else {
		button[LOGOFF].state = BUTTON_STATE_UP;
	}
}

//���˳���ť��������˳���Ϸ
void MenuExitGame() {
	if (button[EXIT].state == BUTTON_STATE_ACTIVE) {
		exit(0); // �˳���Ϸ
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
	if (!is_login) {
		LoginGame(); // ����Ƿ��¼��Ϸ
		RegisterGame();// ����Ƿ�ע����Ϸ
	} 
	else {
		LogoffGame(); // ����Ƿ��˳���¼
	}
	MenuExitGame(); // ����Ƿ��˳���Ϸ
}