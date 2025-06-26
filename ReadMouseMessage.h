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