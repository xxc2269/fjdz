#pragma once//���ڷ�ֹͷ�ļ�����ΰ���
#include<stdio.h>//��׼���������������������ַ�����sprintf�������ַ����ж�ȡ���ݣ�sscanf�����ļ��Ķ�д��fopen��fclose��fread��fwrite��fseek��ftell���ȣ�
#include<stdlib.h>//һЩʵ�ú������ڴ���䣨malloc��calloc��realloc��free������������ɣ�rand��srand�����ַ���ת����atoi��atof��strtol��strtod���ȣ�
#include<graphics.h>//ͼ�λ�����صĺ�����initgraph��closegraph��setbkcolor��setcolor��line��rectangle��circle��floodfill�ȣ�
#include<string>//C++�е��ַ����ࣨstd::string��������غ�����append��find��substr��replace��length�ȣ�
#include<math.h>//��ѧ������sin��cos��tan��sqrt��pow���ȣ��˴����������������صĺ�����rand��srand��
#include<time.h>//ʱ����صĺ�����time��clock��localtime��gmtime����
#include<Winuser.h>//���ֲ��š��������롢������롢������Ϣ��
#include<mmstream.h>//��ý������صĺ����ͽӿڣ�IMultiMediaStream��IMediaStream��IStreamSample�ȣ�
#include"bass.h"//BASS��Ƶ����صĺ����ͽӿڣ�������Ƶ���š�����ȣ�
#include"include/mysql.h"//MySQL���ݿ���صĺ����ͽӿڣ��������ݿ�����������ӡ���ѯ������ȣ�
//#include"ReadMouseMessage.h"//��ȡ���������صĺ����ͽӿڣ����ڻ�ȡ���λ�á�����״̬�ȣ�

#pragma comment(lib,"winmm.lib")//���ֲ�����صĿ�(�������������ã���Ϊʹ��BASS��)
#pragma comment(lib,"bass.lib")//BASS��Ƶ������ӿ�
#pragma comment(lib,"libmysql.lib")//MySQL���ݿ�����ӿ�