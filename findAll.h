#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "defines.h"
#include "include/mysql.h"
#include "connect_db.h"


static bool findAll() {
	MYSQL mysql;
	// 连接到数据库
	if (!connect_db(mysql)) {
		return false; // 连接失败
	}
	
	// 设置字符集
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	
	// 准备 SQL 查询语句
	string sql = "SELECT * FROM record ORDER BY score DESC;";
	
	// 执行查询
	if (mysql_query(&mysql, sql.c_str())) {
		char error_msg[256];
		sprintf(error_msg, "查询记录失败\n\n %s", mysql_error(&mysql));
		MessageBox(NULL, error_msg, "错误", MB_ICONWARNING);
		//printf( "查询记录失败: %s\n", mysql_error(&mysql));
		mysql_close(&mysql); // 关闭连接
		return false; // 查询失败
	}
	
	// 获取结果集
	MYSQL_RES* res = mysql_store_result(&mysql);
	if (res == NULL) {
		char error_msg[256];
		sprintf(error_msg, "获取结果集失败\n\n %s", mysql_error(&mysql));
		MessageBox(NULL, error_msg, "错误", MB_ICONWARNING);
		//printf( "获取结果集失败: %s\n", mysql_error(&mysql));
		mysql_close(&mysql); // 关闭连接
		return false; // 获取结果集失败
	}
	


	// 遍历结果集并输出记录
	MYSQL_ROW row;
	//创建整数数组
	record records1[100]; // 假设最多存储100条记录
	int i = 0; // 记录索引
	while ((row = mysql_fetch_row(res)) != NULL) {
		if (row[1] != NULL && row[2] != NULL) {
			// 将查询结果存储到记录数组中
			record rec;
			sprintf(rec.username, "%s", row[1]); // 假设 username 是字符串类型
			//rec.username = row[1];
			sscanf_s(row[2], "%d", &rec.score); // 假设 score 是整数类型
			//rec.score = row[2];
			records1[i] = rec; // 假设 i 是当前记录的索引
			i++;
		}
	}

 
	//对 records1进行从大到小排序

	//int j, temp;
	//int n = 100;
	//for (i = 0; i < n - 1; i++) {
	//	for (j = 0; j < n - i - 1; j++) {
	//		// 如果当前元素小于下一个元素，则交换它们
	//		if (records1[j].score < records1[j + 1].score) {
	//			temp = records1[j].score;
	//			records1[j] = records1[j + 1];
	//			records1[j + 1].score = temp;
	//		}
	//	}
	//}
	
	//将records1中的数据复制到records中
	for (int k = 0; k < i; k++) {
		records[k] = records1[k];
	}

	//输出records前五个
	for (int k = 0; k < i && k < 5; k++) {
		sprintf(outputrecord[k].username, "%s", records[k].username);// 将用户名复制到输出记录中
		outputrecord[k].score = records[k].score;// 将分数复制到输出记录中
	}
	
	
	// 释放结果集
	mysql_free_result(res);
	mysql_close(&mysql); // 关闭连接
	//MessageBox(NULL, "查询记录成功\n\n（这是一条调试信息）", "提示", MB_OK | MB_ICONINFORMATION);
	return true; // 查询成功
}