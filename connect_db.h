#pragma once
#include "include/mysql.h"
#include <stdio.h>
#include <iostream>
using namespace std;

bool connect_db(MYSQL& mysql) {
    // 初始化 MySQL 连接
    mysql_init(&mysql);
    // 设置字符集
    mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
    // 连接到数据库
    if (mysql_real_connect(&mysql, "localhost", "manager", "123456", "game", 0, NULL, 0) == NULL) {
		char error_msg[256];
        sprintf(error_msg, "数据库连接失败\n\n %s", mysql_error(&mysql));
        MessageBox(NULL, error_msg, "错误", MB_ICONWARNING);
        return false; // 连接失败
    }
    return true;
}

static bool fetch_user_info(char* username, char* password) {
    MYSQL mysql;
    char sql[256];
    bool ret = false;
    MYSQL_RES* result;
    MYSQL_ROW row;
    // 1. 连接到数据库
    if (!connect_db(mysql)) {
        return false; // 连接失败
    }
    // 2. 执行查询
    snprintf(sql, 256, "SELECT * FROM users WHERE username = '%s' AND password = '%s'; ", username, password);
    ret = mysql_query(&mysql, sql); // 成功返回 0，失败返回非 0
    if (ret) {
        char error_msg[256];
        sprintf(error_msg, "查询失败\n\n%s", mysql_error(&mysql));
        MessageBox(NULL, _T(error_msg), _T("错误"), MB_ICONWARNING);
        //printf("查询失败,%s 失败原因: %s\n", sql, mysql_error(&mysql));
        mysql_close(&mysql); // 关闭连接
        return false; // 查询失败
    }
    // 3. 获取结果
    result = mysql_store_result(&mysql);
    row = mysql_fetch_row(result);
    if (row == NULL) { // 没有找到记录
        mysql_free_result(result);
        mysql_close(&mysql);
        return false;
    }
    // 4. 返回结果
    return true;
    // user.username=atoi(row[0]);
    // user.password=atoi(row[1]); 如果需要获取其他信息
}