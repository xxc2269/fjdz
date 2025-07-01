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

//�������յ÷�
void DrawFinalScore() {
	settextstyle(30, 0, _T("����")); // ����������ʽ
	setbkmode(TRANSPARENT); // ���ñ���ģʽΪ͸��
	settextcolor(WHITE); // ����������ɫΪ��ɫ
	char scoreText[50];
	sprintf(scoreText, "���յ÷֣�%d", score); // ��ʽ���÷��ı�
	outtextxy(SCREEN_WIDTH / 2 - 100, 200, scoreText); // ����Ļ���Ļ��Ƶ÷�
}

//��ʾ�û���
void DrawUsername() {
	settextstyle(30, 0, _T("����")); // ����������ʽ
	setbkmode(TRANSPARENT); // ���ñ���ģʽΪ͸��
	settextcolor(WHITE); // ����������ɫΪ��ɫ
	outtextxy(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 100, _T("��ӭ�㣬")); // ����Ļ���Ļ����û�����ʾ
	outtextxy(SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2 - 100, USER.username); // ���û�����ʾ������û���
}

// ���ư�ť����
void DrawButton(int idx) {
	COLORREF fillColor = COLOR_BTN_UP;
	switch (button[idx].state) {
	case BUTTON_STATE_UP:      fillColor = COLOR_BTN_UP; break;
	case BUTTON_STATE_HOVER:   fillColor = COLOR_BTN_HOVER; break;
	case BUTTON_STATE_DOWN:    fillColor = COLOR_BTN_DOWN; break;
	case BUTTON_STATE_ACTIVE:  fillColor = COLOR_BTN_ACTIVE; break;
	case BUTTON_STATE_DISABLED:fillColor = COLOR_BTN_DISABLE; break;
	}
	settextstyle(30, 0, _T("����"));
	setbkmode(OPAQUE);
	setbkcolor(fillColor);
	setfillcolor(fillColor);
	settextcolor(COLOR_BTN_TEXT);
	rectangle(button[idx].x, button[idx].y, button[idx].x + button[idx].width, button[idx].y + button[idx].height);
	outtextxy(button[idx].x + 50, button[idx].y + 10, button[idx].text);
}