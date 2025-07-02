#pragma once
#define _CRT_SECURE_NO_WARNINGS // ���ð�ȫ����,�����������ʾʹ�ò���ȫ�ĺ�����strcpy��sprintf��
#include"defines.h"// �����궨��ͷ�ļ�(�Ѱ����˱�׼ͷ�ļ�)
#include"include/mysql.h"// ����MySQL���ݿ�ͷ�ļ�
#include"connect_db.h"// �����������ݿ�ͷ�ļ�

void auto_login() {//�Զ���¼
	MYSQL mysql;
	// ���ӵ����ݿ�
	if (!connect_db(mysql)) {
		char error_msg[256];
		sprintf(error_msg, "�޷����ӵ����ݿ⣬�Զ���¼ʧ��\n\n %s", mysql_error(&mysql));
		MessageBox(NULL, error_msg, "����", MB_ICONWARNING);
		return; // ����ʧ��
	}
	// �����ַ���
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	// ����Զ���¼״̬
	if (is_auto_login) {
		if (!fetch_user_info(auto_username, auto_password)) {
			MessageBox(NULL, _T("�Զ���¼ʧ�ܣ��û������������"), _T("����"), MB_ICONWARNING);
			return;
		} else {
			/*TCHAR msg[200];
			sprintf(msg, "���Զ���¼��%s", auto_username);
			MessageBox(NULL, msg, _T("��¼�ɹ�"), MB_ICONINFORMATION);*/
			is_login = true; // ���õ�¼״̬Ϊtrue
			sprintf(USER.username, "%s", auto_username); // �����¼�û���
			sprintf(USER.password, "%s", auto_password); // �����¼����
			button[LOGIN].state = BUTTON_STATE_DISABLED; // ��¼�󽫵�¼��ť״̬����Ϊ����
			button[REGISTER].state = BUTTON_STATE_DISABLED; // ��¼��ע�ᰴť״̬����Ϊ����
			button[LOGOFF].state = BUTTON_STATE_UP; // �˳���¼��ť����Ϊ����״̬
		}
	} 

}