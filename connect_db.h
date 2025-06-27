#pragma once
#include "include/mysql.h"
#include <stdio.h>
#include <iostream>
using namespace std;

bool connect_db(MYSQL& mysql) {
    // ��ʼ�� MySQL ����
    mysql_init(&mysql);
    // �����ַ���
    mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
    // ���ӵ����ݿ�
    if (mysql_real_connect(&mysql, "localhost", "manager", "123456", "game", 0, NULL, 0) == NULL) {
		char error_msg[256];
        sprintf(error_msg, "���ݿ�����ʧ��\n\n %s", mysql_error(&mysql));
        MessageBox(NULL, error_msg, "����", MB_ICONWARNING);
        return false; // ����ʧ��
    }
    return true;
}

static bool fetch_user_info(char* username, char* password) {
    MYSQL mysql;
    char sql[256];
    bool ret = false;
    MYSQL_RES* result;
    MYSQL_ROW row;
    // 1. ���ӵ����ݿ�
    if (!connect_db(mysql)) {
        return false; // ����ʧ��
    }
    // 2. ִ�в�ѯ
    snprintf(sql, 256, "SELECT * FROM users WHERE username = '%s' AND password = '%s'; ", username, password);
    ret = mysql_query(&mysql, sql); // �ɹ����� 0��ʧ�ܷ��ط� 0
    if (ret) {
        char error_msg[256];
        sprintf(error_msg, "��ѯʧ��\n\n%s", mysql_error(&mysql));
        MessageBox(NULL, _T(error_msg), _T("����"), MB_ICONWARNING);
        //printf("��ѯʧ��,%s ʧ��ԭ��: %s\n", sql, mysql_error(&mysql));
        mysql_close(&mysql); // �ر�����
        return false; // ��ѯʧ��
    }
    // 3. ��ȡ���
    result = mysql_store_result(&mysql);
    row = mysql_fetch_row(result);
    if (row == NULL) { // û���ҵ���¼
        mysql_free_result(result);
        mysql_close(&mysql);
        return false;
    }
    // 4. ���ؽ��
    return true;
    // user.username=atoi(row[0]);
    // user.password=atoi(row[1]); �����Ҫ��ȡ������Ϣ
}