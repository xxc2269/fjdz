#pragma once
#include"defines.h" // �����궨��ͷ�ļ�(�Ѱ����˱�׼ͷ�ļ�)

void outputrecords() {
	// ���Ʊ���
	
	// ����������ʽ
	settextstyle(30, 0, _T("����"));
	setbkmode(TRANSPARENT); // ���ñ���ģʽΪ͸��
	settextcolor(WHITE); // ����������ɫΪ��ɫ
	// ���Ʊ���
	outtextxy(SCREEN_WIDTH / 2 - 80, 220, "���а�");
	// ��ѯ���м�¼
	
	// �����¼����Ļ
	for (int i = 0; i < 5; i++) {
		char output[100];
		sprintf(output, "%d.\t%s\t- %d", i + 1, records[i].username, records[i].score);
		outtextxy(SCREEN_WIDTH / 2 - 100, 250 + i * 30, output);
	}

}