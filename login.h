#pragma once
#include"defines.h"// 包含宏定义头文件(已包含了标准头文件)
#include"connect_db.h"// 包含连接数据库头文件
#include<string.h>// 包含字符串处理头文件，可以使用字符串相关的函数，如strcmp、strcpy等
#include<string>// 包含C++字符串类头文件，可以使用std::string类和相关函数

void userlogin() {// 用户登录函数
	// 此处可以添加用户登录的逻辑，例如验证用户名和密码
	// 例如，使用输入框获取用户名和密码，然后与数据库中的记录进行比对
	// 如果验证成功，则进入游戏主界面，否则提示错误信息
	// 这里可以使用MessageBox或其他方式提示用户登录结果
	//MessageBox(NULL, "用户登录功能尚未实现", "提示", MB_OK | MB_ICONINFORMATION);
	MYSQL mysql;
	// 连接到数据库
	if (!connect_db(mysql)) {
		char error_msg[256];
		sprintf(error_msg, "数据库连接失败\n\n %s", mysql_error(&mysql));
		MessageBox(NULL, error_msg, "错误", MB_ICONWARNING);
		return; // 连接失败
	}

	// 设置字符集
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");

	char username[45]; // 定义用户名数组
	char password[45]; // 定义密码数组


	InputBox(username, 45, "请输入用户名"); // 获取用户名
	InputBox(password, 45, "请输入密码"); // 获取密码

	if (strcmp(username, "") == 0 || strcmp(password, "") == 0) {
		char error_msg[256];
		MessageBox(NULL, "用户名或密码不能为空", "错误", MB_ICONWARNING);
		return;
	}

	if (!fetch_user_info(username, password)) {
		MessageBox(NULL, _T("用户名或密码错误"), _T("错误"), MB_ICONWARNING);
		return;
	}
	else {
		TCHAR msg[200];
		sprintf(msg, "欢迎回来, %s!", username);
		MessageBox(NULL, msg, _T("登录成功"), MB_ICONINFORMATION);
		is_login = true; // 设置登录状态为true
		is_auto_login = 1; // 设置自动登录状态为true
		sprintf(USER.username, "%s", username); // 保存登录用户名
		sprintf(USER.password, "%s", password); // 保存登录密码
		button[LOGIN].state = BUTTON_STATE_DISABLED; // 登录后将登录按钮状态设置为禁用
		button[REGISTER].state = BUTTON_STATE_DISABLED; // 登录后将注册按钮状态设置为禁用
		button[LOGOFF].state = BUTTON_STATE_UP; // 退出登录按钮设置为激活状态
		record_file = fopen("_RECORD_", "w+"); // 打开记录文件
		fprintf(record_file, "%d %s %s", is_auto_login, USER.username, USER.password); // 写入自动登录状态和用户名密码
		fclose(record_file); // 关闭记录文件
	}
}