#pragma once
#include "defines.h" // �����궨��ͷ�ļ�(�Ѱ����˱�׼ͷ�ļ�)
#include"connect_db.h" // �����������ݿ�ͷ�ļ�
#include<string.h> // �����ַ�������ͷ�ļ�������ʹ���ַ�����صĺ�������strcmp��strcpy��
#include<string> // ����C++�ַ�����ͷ�ļ�������ʹ��std::string�����غ���

void userregister() {// �û�ע�ắ��
	// �˴���������û�ע����߼��������ȡ�û��������룬Ȼ����洢�����ݿ���
	// ���磬ʹ��������ȡ�û��������룬Ȼ������뵽���ݿ���û�����
	// ���ע��ɹ�������ʾ�û�ע��ɹ���������ʾ������Ϣ
	// �������ʹ��MessageBox��������ʽ��ʾ�û�ע����
	//MessageBox(NULL, "�û�ע�Ṧ����δʵ��", "��ʾ", MB_OK | MB_ICONINFORMATION);
	MYSQL mysql;
	// ���ӵ����ݿ�
	if (!connect_db(mysql)) {
		char error_msg[256];
		sprintf(error_msg, "���ݿ�����ʧ��\n\n %s", mysql_error(&mysql));
		MessageBox(NULL, error_msg, "����", MB_ICONWARNING);
		return ; // ����ʧ��
	}

	// �����ַ���
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");

	char username[45]; // �����û�������
	char password[45]; // ������������
	char comfirm_password[45]; // ����ȷ����������

	InputBox(username, 45, "�������û���"); // ��ȡ�û���
	InputBox(password, 45, "����������"); // ��ȡ����
	InputBox(comfirm_password, 45, "��ȷ������"); // ��ȡȷ������
	if (strcmp(username, "") == 0 || strcmp(password, "") == 0) {
		char error_msg[256];
		MessageBox(NULL, "�û��������벻��Ϊ��", "����", MB_ICONWARNING);
		mysql_close(&mysql); // �ر�����
		return;
	}
	if (strcmp(password, comfirm_password) != 0) {
		char error_msg[256];
		MessageBox(NULL, "�������벻һ��", "����", MB_ICONWARNING);
		mysql_close(&mysql); // �ر�����
		return;
	}

	// ׼�� SQL �������
	char sql[256] ;
	sprintf(sql,  "INSERT INTO users (username, password) VALUES ('%s', '%s');", username, password);
	// ִ�в������
	if (mysql_query(&mysql, sql)) {
		char error_msg[256];
		sprintf(error_msg, "�����û�ʧ��\n\n %s", mysql_error(&mysql));
		MessageBox(NULL, error_msg, "����", MB_ICONWARNING);
		//printf("����ʧ��: %s\n", mysql_error(&mysql));
		mysql_close(&mysql); // �ر�����
		return; // ����ʧ��
	}

	TCHAR msg[200];
	sprintf(msg, "ע��ɹ�!\n�û���: %s", username);
	MessageBox(NULL, msg, "ע��ɹ�", MB_ICONINFORMATION);
	mysql_close(&mysql); // �ر�����
	return;
}