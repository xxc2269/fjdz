#pragma once//用于防止头文件被多次包含
#include<stdio.h>//标准输入输出（将数据输出到字符串（sprintf）、从字符串中读取数据（sscanf）、文件的读写（fopen、fclose、fread、fwrite、fseek、ftell）等）
#include<stdlib.h>//一些实用函数（内存分配（malloc、calloc、realloc、free）、随机数生成（rand、srand）、字符串转换（atoi、atof、strtol、strtod）等）
#include<graphics.h>//图形绘制相关的函数（initgraph、closegraph、setbkcolor、setcolor、line、rectangle、circle、floodfill等）
#include<string>//C++中的字符串类（std::string）及其相关函数（append、find、substr、replace、length等）
#include<math.h>//数学函数（sin、cos、tan、sqrt、pow）等，此处用于生成随机数相关的函数（rand、srand）
#include<time.h>//时间相关的函数（time、clock、localtime、gmtime）等
#include<Winuser.h>//音乐播放、键盘输入、鼠标输入、窗口消息等
#include<mmstream.h>//多媒体流相关的函数和接口（IMultiMediaStream、IMediaStream、IStreamSample等）
#include"bass.h"//BASS音频库相关的函数和接口（用于音频播放、处理等）
#include"include/mysql.h"//MySQL数据库相关的函数和接口（用于数据库操作，如连接、查询、插入等）
//#include"ReadMouseMessage.h"//读取鼠标输入相关的函数和接口（用于获取鼠标位置、按键状态等）

#pragma comment(lib,"winmm.lib")//音乐播放相关的库(因性能问题弃用，改为使用BASS库)
#pragma comment(lib,"bass.lib")//BASS音频库的链接库
#pragma comment(lib,"libmysql.lib")//MySQL数据库的链接库