#pragma once
#include <string>	
#include "include/mysql.h"
#include "connect_db.h"
#include"defines.h"// �����궨��ͷ�ļ�(�Ѱ����˱�׼ͷ�ļ�)

static bool add_score() {

	MYSQL mysql;
	// ���ӵ����ݿ�
	if (!connect_db(mysql)) {
		char error_msg[256];
		sprintf(error_msg, "�������ʧ�ܣ���ĳɼ������ᱻ����");
		MessageBox(NULL, error_msg, "����", MB_ICONWARNING);
		return false; // ����ʧ��
	}
	// �����ַ���
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	
	
	// ׼�� SQL ���
	char sql[256];
	sprintf(sql, "INSERT INTO record (username, score) VALUES (' %s ', ' %d' )", USER.username, score);
	//std::string sql = "INSERT INTO scores (username, score) VALUES ('" + rec.username + "', " + std::to_string(rec.score) + ")";
	
	// ִ�� SQL ���
	if (mysql_query(&mysql, sql)) {
		char error_msg[256];
		sprintf(error_msg, "�������ʧ�ܣ���ĳɼ������ᱻ����\n\n %s", mysql_error(&mysql));
		MessageBox(NULL, error_msg, "����", MB_ICONWARNING);
		//printf( "�����¼ʧ�� %s\n", mysql_error(&mysql));
		return false; // ����ʧ��
	}
	
	//MessageBox(NULL, "��������ɹ���\n������һ��������Ϣ��", "֪ͨ", MB_ICONASTERISK);
	return true; // ����ɹ�
}