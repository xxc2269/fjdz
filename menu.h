#pragma once
#include "defines.h" // �����궨��ͷ�ļ�(�Ѱ����˱�׼ͷ�ļ�)
#include"login.h"// ������¼ͷ�ļ�
#include"register.h"// ����ע��ͷ�ļ�

void ReadMouseInput() {
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
            } else {
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
            } else {
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
            } else if (button[i].state != BUTTON_STATE_DISABLED) {
                button[i].state = BUTTON_STATE_UP;
            }
        }
        mouseDownIndex = -1;
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
	if (button[REGISTER].state == BUTTON_STATE_ACTIVE ) {// ȷ����ť����������ٵȴ�1��
		// ��ע�ᴰ�ڵĴ���
		button[REGISTER].state = BUTTON_STATE_UP; // ע���ע�ᰴť״̬����Ϊ����
		userregister(); // ����ע�ắ��
	}
	//else {
	//	button[REGISTER].state = BUTTON_STATE_UP; // ���ע�ᰴťδ���������״̬����Ϊ����
	//}
}
//���˳���¼��ť��������˳���¼״̬
void LogoffGame() {
	if (button[LOGOFF].state == BUTTON_STATE_ACTIVE ) {// ȷ����ť����������ٵȴ�1��
		if (MessageBox(NULL, "ȷ��Ҫ�˳���¼��", "�˳���¼", MB_YESNO | MB_ICONQUESTION) == IDYES) {
			is_login = false; // ���õ�¼״̬Ϊfalse
			is_auto_login = 0; // �����Զ���¼״̬Ϊfalse
			USER.username[0] = '\0'; // ����û���
			USER.password[0] = '\0'; // �������
			button[LOGOFF].state = BUTTON_STATE_DISABLED; // �����˳���¼��ť
			button[LOGIN].state = BUTTON_STATE_UP; // �����¼��ť
			button[REGISTER].state = BUTTON_STATE_UP; // ����ע�ᰴť
			record_file = fopen("_RECORD_", "w+"); // �򿪼�¼�ļ�
			fprintf(record_file, "%d %s %s", is_auto_login, USER.username, USER.password); // д���Զ���¼״̬���û�������
		}
		else button[LOGOFF].state = BUTTON_STATE_UP; // ����û�ѡ���˳���¼�����˳���¼��ť״̬����Ϊ����
		
	}
	/*else {
		button[LOGOFF].state = BUTTON_STATE_UP;
	}*/
}

//���˳���ť��������˳���Ϸ
void MenuExitGame() {
	if (button[EXIT].state == BUTTON_STATE_ACTIVE) {
		if (MessageBox(NULL, "ȷ��Ҫ�˳���Ϸ��", "�˳���Ϸ", MB_YESNO | MB_ICONQUESTION) == IDYES) {
			exit(0); // �˳���Ϸ
		}
		else button[EXIT].state = BUTTON_STATE_UP; // ����û�ѡ���˳���Ϸ�����˳���Ϸ��ť״̬����Ϊ����
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