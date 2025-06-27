#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "defines.h"
#include "include/mysql.h"
#include "connect_db.h"


static bool findAll() {
	MYSQL mysql;
	// ���ӵ����ݿ�
	if (!connect_db(mysql)) {
		return false; // ����ʧ��
	}
	
	// �����ַ���
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	
	// ׼�� SQL ��ѯ���
	string sql = "SELECT * FROM record ORDER BY score DESC;";
	
	// ִ�в�ѯ
	if (mysql_query(&mysql, sql.c_str())) {
		char error_msg[256];
		sprintf(error_msg, "��ѯ��¼ʧ��\n\n %s", mysql_error(&mysql));
		MessageBox(NULL, error_msg, "����", MB_ICONWARNING);
		//printf( "��ѯ��¼ʧ��: %s\n", mysql_error(&mysql));
		mysql_close(&mysql); // �ر�����
		return false; // ��ѯʧ��
	}
	
	// ��ȡ�����
	MYSQL_RES* res = mysql_store_result(&mysql);
	if (res == NULL) {
		char error_msg[256];
		sprintf(error_msg, "��ȡ�����ʧ��\n\n %s", mysql_error(&mysql));
		MessageBox(NULL, error_msg, "����", MB_ICONWARNING);
		//printf( "��ȡ�����ʧ��: %s\n", mysql_error(&mysql));
		mysql_close(&mysql); // �ر�����
		return false; // ��ȡ�����ʧ��
	}
	


	// ����������������¼
	MYSQL_ROW row;
	//������������
	record records1[100]; // �������洢100����¼
	int i = 0; // ��¼����
	while ((row = mysql_fetch_row(res)) != NULL) {
		if (row[1] != NULL && row[2] != NULL) {
			// ����ѯ����洢����¼������
			record rec;
			sprintf(rec.username, "%s", row[1]); // ���� username ���ַ�������
			//rec.username = row[1];
			sscanf_s(row[2], "%d", &rec.score); // ���� score ����������
			//rec.score = row[2];
			records1[i] = rec; // ���� i �ǵ�ǰ��¼������
			i++;
		}
	}

 
	//�� records1���дӴ�С����

	//int j, temp;
	//int n = 100;
	//for (i = 0; i < n - 1; i++) {
	//	for (j = 0; j < n - i - 1; j++) {
	//		// �����ǰԪ��С����һ��Ԫ�أ��򽻻�����
	//		if (records1[j].score < records1[j + 1].score) {
	//			temp = records1[j].score;
	//			records1[j] = records1[j + 1];
	//			records1[j + 1].score = temp;
	//		}
	//	}
	//}
	
	//��records1�е����ݸ��Ƶ�records��
	for (int k = 0; k < i; k++) {
		records[k] = records1[k];
	}

	//���recordsǰ���
	for (int k = 0; k < i && k < 5; k++) {
		sprintf(outputrecord[k].username, "%s", records[k].username);// ���û������Ƶ������¼��
		outputrecord[k].score = records[k].score;// ���������Ƶ������¼��
	}
	
	
	// �ͷŽ����
	mysql_free_result(res);
	mysql_close(&mysql); // �ر�����
	//MessageBox(NULL, "��ѯ��¼�ɹ�\n\n������һ��������Ϣ��", "��ʾ", MB_OK | MB_ICONINFORMATION);
	return true; // ��ѯ�ɹ�
}