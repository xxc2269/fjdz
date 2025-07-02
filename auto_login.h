#pragma once
#define _CRT_SECURE_NO_WARNINGS // 禁用安全警告,以免编译器提示使用不安全的函数如strcpy、sprintf等
#include"defines.h"// 包含宏定义头文件(已包含了标准头文件)
#include"include/mysql.h"// 包含MySQL数据库头文件
#include"connect_db.h"// 包含连接数据库头文件

void auto_login() {//自动登录
	MYSQL mysql;
	// 连接到数据库
	if (!connect_db(mysql)) {
		char error_msg[256];
		sprintf(error_msg, "无法连接到数据库，自动登录失败\n\n %s", mysql_error(&mysql));
		MessageBox(NULL, error_msg, "错误", MB_ICONWARNING);
		return; // 连接失败
	}
	// 设置字符集
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	// 检查自动登录状态
	if (is_auto_login) {
		if (!fetch_user_info(auto_username, auto_password)) {
			MessageBox(NULL, _T("自动登录失败，用户名或密码错误"), _T("错误"), MB_ICONWARNING);
			return;
		} else {
			/*TCHAR msg[200];
			sprintf(msg, "已自动登录：%s", auto_username);
			MessageBox(NULL, msg, _T("登录成功"), MB_ICONINFORMATION);*/
			is_login = true; // 设置登录状态为true
			sprintf(USER.username, "%s", auto_username); // 保存登录用户名
			sprintf(USER.password, "%s", auto_password); // 保存登录密码
			button[LOGIN].state = BUTTON_STATE_DISABLED; // 登录后将登录按钮状态设置为禁用
			button[REGISTER].state = BUTTON_STATE_DISABLED; // 登录后将注册按钮状态设置为禁用
			button[LOGOFF].state = BUTTON_STATE_UP; // 退出登录按钮设置为激活状态
		}
	} 

}