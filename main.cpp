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
#include"menu.h"//�Զ����ͷ�ļ��������˲˵�����������
#include"pause.h"//�Զ����ͷ�ļ�����������ͣ����������
#include"gameover.h"//�Զ����ͷ�ļ�����������Ϸ��������������
//#include"accountmanager.h"//�Զ����ͷ�ļ���������ע�ắ��������
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

	char welcometext[] = "��ӭ�����ɻ���ս��Ϸ��\n\n�л�������ռ��Ƭ��գ��㽫����һ��Ӣ�۷ɻ���������ӿ�����ĵл��˳����ػ�һ����ƽ���㽫��Զ����棬��������ڲ�����Ը�Ϊ���ҵĹ��ƣ�ֱ��л�ͷĿ���㣬׼��������\n\n�ƶ���꣬���Ʒɻ�\n\n���������������ˣ���������\n\n����Ҽ����ľ����ƣ��������һ�����ɳ�������\n\n����ʱ����ɻ�������ֵ������ֵ�������ľ����޷������������ľ�����Ϸ����\n\n��Ϸ�п���ʱ����ESC����ͣ"; //���延ӭ�ı�

	char accounttext[] = "�����˺�ϵͳ��ʹ�ã�\n\n��������˺�ϵͳ����MySQL���ݿ�ʵ�֣�ʹ��ǰ�밲װMySQL Server���ֶ�����λ�ڳ���Ŀ¼�µ�mysql.sql�ļ��Դ�����Ϸ���ݿ⼰�����Ա�˻��������޷���¼����"; //�����˺Ź����ı�

	if ((record_file = fopen("_RECORD_", "r"))==NULL) { //����Ҳ�����¼�ļ����򴴽�һ���µļ�¼�ļ�
		MessageBox(NULL, welcometext, TEXT("��ʾ"), MB_ICONINFORMATION); //������Ϣ���ڣ���ʾ��ӭ��Ϣ
		MessageBox(NULL, accounttext, TEXT("��ʾ"), MB_ICONINFORMATION); //������Ϣ���ڣ���ʾ�˺�ϵͳʹ��˵��
		record_file = fopen("_RECORD_", "w+"); //���Դ�����¼�ļ�
	}

	//accountmanager( hInstance,
	//	hPrevInstance,
	//	lpCmdLine,
	//	nShowCmd); //����ע�ắ���������û�ע���߼�
	loadimages(); //���ü���ͼƬ����������������Ҫ��ͼƬ��Դ
	loadSounds(); //���ü�����Ч����������������Ҫ����Ч��Դ


	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);//��ʼ��ͼ�δ��ڣ����ô��ڴ�С
	//MessageBox(NULL, TEXT("һ���򵥵�Win32Ӧ�ó���"), TEXT("��Ϣ����"), MB_OK);//����һ����Ϣ���ڣ���ʾ��һ���򵥵�Win32Ӧ�ó���(����)
	init_game(); //���ó�ʼ����Ϸ����
	while(1){
		switch (game_state) { //������Ϸ״̬���д���
			case GAME_STATE_MAIN_MENU: //�����Ϸ״̬Ϊ������
				menu(); //���ò˵�����������������
				break;
			case GAME_STATE_READY://�����Ϸ״̬Ϊ׼��
				init_game(); //���ó�ʼ����Ϸ���������³�ʼ����Ϸ
				game_state = GAME_STATE_PLAYING; //����Ϸ״̬����Ϊ������
				break;
			case GAME_STATE_PLAYING: //�����Ϸ״̬Ϊ������
				UpdateGame(); //���ø�����Ϸ״̬������������Ϸ״̬
				break;
			case GAME_STATE_PAUSED:
				pause();
				break;
			case GAME_STATE_GAME_OVER: //�����Ϸ״̬Ϊ��Ϸ����
				gameover(); //������Ϸ����������������Ϸ�����߼�
				break;


		}
		
		DrawGame(); //���û�����Ϸ���溯����������Ϸ����
		//Sleep(1); //��ʱ1���룬������Ϸ֡�ʣ����ã�
	}


	
	return 0;//����ֵΪ0��ʾ������������

}