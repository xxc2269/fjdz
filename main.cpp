#define _CRT_SECURE_NO_WARNINGS//���ð�ȫ����,�����������ʾʹ�ò���ȫ�ĺ�����strcpy��sprintf��

//�����׼ͷ�ļ�
//#include"includes.h"

//�궨��(�ں���׼ͷ�ļ�)
#include"defines.h"

//�˴������Զ����ͷ�ļ�
//#include"helloworld.h"//�Զ����ͷ�ļ���������helloworld����������(����)
#include"loadImages.h"//�Զ����ͷ�ļ��������˼���ͼƬ����������
#include"DrawGames.h"//�Զ����ͷ�ļ��������˻�����Ϸ���溯��������
#include"InitGame.h"//�Զ����ͷ�ļ��������˳�ʼ����Ϸ����������
#include"UpdateGame.h"//�Զ����ͷ�ļ��������˸�����Ϸ״̬����������
#include"loadSounds.h"//�Զ����ͷ�ļ��������˼�����Ч����������

//��������

//��ʼ����Ϸ����
void init_game(); 
//����ͼƬ����
void loadimages();
//������Ϸ���溯��
void DrawGame();
//������Ϸ״̬����
void UpdateGame(); 

//��������


//��������ڵ㣬ʹ��win32���򣬲��ᵯ������̨����
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
	int nShowCmd)
{
	//helloworld();//�����Զ����helloworld���������Hello World!�����ԣ�


	loadimages(); //���ü���ͼƬ����������������Ҫ��ͼƬ��Դ
	loadSounds(); //���ü�����Ч����������������Ҫ����Ч��Դ


	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);//��ʼ��ͼ�δ��ڣ����ô��ڴ�С
	//MessageBox(NULL, TEXT("һ���򵥵�Win32Ӧ�ó���"), TEXT("��Ϣ����"), MB_OK);//����һ����Ϣ���ڣ���ʾ��һ���򵥵�Win32Ӧ�ó���(����)
	init_game(); //���ó�ʼ����Ϸ����
	while(1){
		UpdateGame(); //���ø�����Ϸ״̬������������Ϸ״̬
		DrawGame(); //���û�����Ϸ���溯����������Ϸ����
		//Sleep(1); //��ʱ1���룬������Ϸ֡�ʣ����ã�
	}


	
	return 0;//����ֵΪ0��ʾ������������

}