#pragma once
#include "defines.h" // 包含宏定义头文件(已包含了标准头文件)
#include"connect_db.h" // 包含连接数据库头文件
#include<string.h> // 包含字符串处理头文件，可以使用字符串相关的函数，如strcmp、strcpy等
#include<string> // 包含C++字符串类头文件，可以使用std::string类和相关函数

void userregister() {// 用户注册函数
	// 此处可以添加用户注册的逻辑，例如获取用户名和密码，然后将其存储到数据库中
	// 例如，使用输入框获取用户名和密码，然后将其插入到数据库的用户表中
	// 如果注册成功，则提示用户注册成功，否则提示错误信息
	// 这里可以使用MessageBox或其他方式提示用户注册结果
	//MessageBox(NULL, "用户注册功能尚未实现", "提示", MB_OK | MB_ICONINFORMATION);
	MYSQL mysql;
	// 连接到数据库
	if (!connect_db(mysql)) {
		char error_msg[256];
		sprintf(error_msg, "数据库连接失败\n\n %s", mysql_error(&mysql));
		MessageBox(NULL, error_msg, "错误", MB_ICONWARNING);
		return ; // 连接失败
	}

	// 设置字符集
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");

	char username[45]; // 定义用户名数组
	char password[45]; // 定义密码数组
	char comfirm_password[45]; // 定义确认密码数组

	InputBox(username, 45, "请输入用户名"); // 获取用户名
	InputBox(password, 45, "请输入密码"); // 获取密码
	InputBox(comfirm_password, 45, "请确认密码"); // 获取确认密码
	if (strcmp(username, "") == 0 || strcmp(password, "") == 0) {
		char error_msg[256];
		MessageBox(NULL, "用户名或密码不能为空", "错误", MB_ICONWARNING);
		mysql_close(&mysql); // 关闭连接
		return;
	}
	if (strcmp(password, comfirm_password) != 0) {
		char error_msg[256];
		MessageBox(NULL, "两次密码不一致", "错误", MB_ICONWARNING);
		mysql_close(&mysql); // 关闭连接
		return;
	}

	// 准备 SQL 插入语句
	char sql[256] ;
	sprintf(sql,  "INSERT INTO users (username, password) VALUES ('%s', '%s');", username, password);
	// 执行插入语句
	if (mysql_query(&mysql, sql)) {
		char error_msg[256];
		sprintf(error_msg, "插入用户失败\n\n %s", mysql_error(&mysql));
		MessageBox(NULL, error_msg, "错误", MB_ICONWARNING);
		//printf("插入失败: %s\n", mysql_error(&mysql));
		mysql_close(&mysql); // 关闭连接
		return; // 插入失败
	}

	TCHAR msg[200];
	sprintf(msg, "注册成功!\n用户名: %s", username);
	MessageBox(NULL, msg, "注册成功", MB_ICONINFORMATION);
	mysql_close(&mysql); // 关闭连接
	return;
}