#pragma once
#include <string>	
#include "include/mysql.h"
#include "connect_db.h"
#include"defines.h"// 包含宏定义头文件(已包含了标准头文件)

static bool add_score() {

	MYSQL mysql;
	// 连接到数据库
	if (!connect_db(mysql)) {
		char error_msg[256];
		sprintf(error_msg, "插入分数失败，你的成绩将不会被保存");
		MessageBox(NULL, error_msg, "错误", MB_ICONWARNING);
		return false; // 连接失败
	}
	// 设置字符集
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	
	
	// 准备 SQL 语句
	char sql[256];
	sprintf(sql, "INSERT INTO record (username, score) VALUES (' %s ', ' %d' )", USER.username, score);
	//std::string sql = "INSERT INTO scores (username, score) VALUES ('" + rec.username + "', " + std::to_string(rec.score) + ")";
	
	// 执行 SQL 语句
	if (mysql_query(&mysql, sql)) {
		char error_msg[256];
		sprintf(error_msg, "插入分数失败，你的成绩将不会被保存\n\n %s", mysql_error(&mysql));
		MessageBox(NULL, error_msg, "错误", MB_ICONWARNING);
		//printf( "插入记录失败 %s\n", mysql_error(&mysql));
		return false; // 插入失败
	}
	
	//MessageBox(NULL, "插入分数成功！\n（这是一条调试信息）", "通知", MB_ICONASTERISK);
	return true; // 插入成功
}