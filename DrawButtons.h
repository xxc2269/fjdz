#pragma once
#include"defines.h" // �����궨��ͷ�ļ�(�Ѱ����˱�׼ͷ�ļ�)


//������Ϸ����
void DrawTitle() {
	settextstyle(50, 0, _T("����")); // ����������ʽ
	setbkmode(TRANSPARENT); //���ñ���ģʽΪ͸��
	settextcolor(WHITE); // ����������ɫΪ��ɫ
	outtextxy(SCREEN_WIDTH / 2 - 100, 150, _T("�ɻ���ս")); // ����Ļ���Ļ��Ʊ���
}


//������ͣ����
void DrawPauseTitle() {
	settextstyle(50, 0, _T("����")); // ����������ʽ
	setbkmode(TRANSPARENT); //���ñ���ģʽΪ͸��
	settextcolor(WHITE); // ����������ɫΪ��ɫ
	outtextxy(SCREEN_WIDTH / 2 - 100, 150, _T("��   ͣ")); // ����Ļ���Ļ��Ʊ���
}


//���ƻ�����Ϸ��������
void DrawOverTitle() {
	settextstyle(50, 0, _T("����")); // ����������ʽ
	setbkmode(TRANSPARENT); //���ñ���ģʽΪ͸��
	settextcolor(WHITE); // ����������ɫΪ��ɫ
	outtextxy(SCREEN_WIDTH / 2 - 100, 150, _T("��Ϸ����")); // ����Ļ���Ļ��Ʊ���
}


// ���ư�ť����

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

//����ע�ᰴť
void DrawRegisterButton() {
	settextstyle(30, 0, _T("����")); // ����������ʽ
	setbkmode(OPAQUE); // ���ñ���ģʽΪ��͸��
	setbkcolor(BLUE); // ���ð�ť������ɫΪ��ɫ
	setfillcolor(BLUE); // ���ð�ť�����ɫΪ��ɫ
	settextcolor(WHITE); // ����������ɫΪ��ɫ
	rectangle(button[REGISTER].x, button[REGISTER].y, button[REGISTER].x + button[REGISTER].width, button[REGISTER].y + button[REGISTER].height); // ���ư�ť�߿�
	outtextxy(button[REGISTER].x + 50, button[REGISTER].y + 10, button[REGISTER].text); // �ڰ�ť�ϻ�������
}
//���Ƶ�¼��ť
void DrawLoginButton() {
	settextstyle(30, 0, _T("����")); // ����������ʽ
	setbkmode(OPAQUE); // ���ñ���ģʽΪ��͸��
	setbkcolor(BLUE); // ���ð�ť������ɫΪ��ɫ
	setfillcolor(BLUE); // ���ð�ť�����ɫΪ��ɫ
	settextcolor(WHITE); // ����������ɫΪ��ɫ
	rectangle(button[LOGIN].x, button[LOGIN].y, button[LOGIN].x + button[LOGIN].width, button[LOGIN].y + button[LOGIN].height); // ���ư�ť�߿�
	outtextxy(button[LOGIN].x + 50, button[LOGIN].y + 10, button[LOGIN].text); // �ڰ�ť�ϻ�������
}

//���ѵ�¼����ʾ�û������˳���¼��ť
void DrawLogoffButton() {
	settextstyle(30, 0, _T("����")); // ����������ʽ
	setbkmode(OPAQUE); // ���ñ���ģʽΪ��͸��
	setbkcolor(BLUE); // ���ð�ť������ɫΪ��ɫ
	setfillcolor(BLUE); // ���ð�ť�����ɫΪ��ɫ
	settextcolor(WHITE); // ����������ɫΪ��ɫ
	rectangle(button[LOGOFF].x, button[LOGOFF].y, button[LOGOFF].x + button[LOGOFF].width, button[LOGOFF].y + button[LOGOFF].height); // ���ư�ť�߿�
	outtextxy(button[LOGOFF].x + 50, button[LOGOFF].y + 10, button[LOGOFF].text); // �ڰ�ť�ϻ�������
}

//��ʾ�û���
void DrawUsername() {
	settextstyle(30, 0, _T("����")); // ����������ʽ
	setbkmode(TRANSPARENT); // ���ñ���ģʽΪ͸��
	settextcolor(WHITE); // ����������ɫΪ��ɫ
	outtextxy(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 100, _T("��ӭ�㣬")); // ����Ļ���Ļ����û�����ʾ
	outtextxy(SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2 - 100, USER.username); // ���û�����ʾ������û���
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
//���Ʒ�����ҳ��ť
void DrawHomeButton() {
	settextstyle(30, 0, _T("����")); // ����������ʽ
	setbkmode(OPAQUE); // ���ñ���ģʽΪ��͸��
	setbkcolor(BLUE); // ���ð�ť������ɫΪ��ɫ
	setfillcolor(BLUE); // ���ð�ť�����ɫΪ��ɫ
	settextcolor(WHITE); // ����������ɫΪ��ɫ
	rectangle(button[HOME].x, button[HOME].y, button[HOME].x + button[HOME].width, button[HOME].y + button[HOME].height); // ���ư�ť�߿�
	outtextxy(button[HOME].x + 50, button[HOME].y + 10, button[HOME].text); // �ڰ�ť�ϻ�������
}
