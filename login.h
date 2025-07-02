#pragma once
#include"defines.h"// �����궨��ͷ�ļ�(�Ѱ����˱�׼ͷ�ļ�)
#include"connect_db.h"// �����������ݿ�ͷ�ļ�
#include<string.h>// �����ַ�������ͷ�ļ�������ʹ���ַ�����صĺ�������strcmp��strcpy��
#include<string>// ����C++�ַ�����ͷ�ļ�������ʹ��std::string�����غ���

void userlogin() {// �û���¼����
	// �˴���������û���¼���߼���������֤�û���������
	// ���磬ʹ��������ȡ�û��������룬Ȼ�������ݿ��еļ�¼���бȶ�
	// �����֤�ɹ����������Ϸ�����棬������ʾ������Ϣ
	// �������ʹ��MessageBox��������ʽ��ʾ�û���¼���
	//MessageBox(NULL, "�û���¼������δʵ��", "��ʾ", MB_OK | MB_ICONINFORMATION);
	MYSQL mysql;
	// ���ӵ����ݿ�
	if (!connect_db(mysql)) {
		char error_msg[256];
		sprintf(error_msg, "���ݿ�����ʧ��\n\n %s", mysql_error(&mysql));
		MessageBox(NULL, error_msg, "����", MB_ICONWARNING);
		return; // ����ʧ��
	}

	// �����ַ���
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");

	char username[45]; // �����û�������
	char password[45]; // ������������


	InputBox(username, 45, "�������û���"); // ��ȡ�û���
	InputBox(password, 45, "����������"); // ��ȡ����

	if (strcmp(username, "") == 0 || strcmp(password, "") == 0) {
		char error_msg[256];
		MessageBox(NULL, "�û��������벻��Ϊ��", "����", MB_ICONWARNING);
		return;
	}

	if (!fetch_user_info(username, password)) {
		MessageBox(NULL, _T("�û������������"), _T("����"), MB_ICONWARNING);
		return;
	}
	else {
		TCHAR msg[200];
		sprintf(msg, "��ӭ����, %s!", username);
		MessageBox(NULL, msg, _T("��¼�ɹ�"), MB_ICONINFORMATION);
		is_login = true; // ���õ�¼״̬Ϊtrue
		is_auto_login = 1; // �����Զ���¼״̬Ϊtrue
		sprintf(USER.username, "%s", username); // �����¼�û���
		sprintf(USER.password, "%s", password); // �����¼����
		button[LOGIN].state = BUTTON_STATE_DISABLED; // ��¼�󽫵�¼��ť״̬����Ϊ����
		button[REGISTER].state = BUTTON_STATE_DISABLED; // ��¼��ע�ᰴť״̬����Ϊ����
		button[LOGOFF].state = BUTTON_STATE_UP; // �˳���¼��ť����Ϊ����״̬
		record_file = fopen("_RECORD_", "w+"); // �򿪼�¼�ļ�
		fprintf(record_file, "%d %s %s", is_auto_login, USER.username, USER.password); // д���Զ���¼״̬���û�������
		fclose(record_file); // �رռ�¼�ļ�
	}
}