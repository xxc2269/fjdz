#pragma once//����
#include"includes.h"

#define SCREEN_WIDTH 512 //��Ļ���
#define SCREEN_HEIGHT 720 //��Ļ�߶�
#define PLANE_SIZE 50 //�ɻ���С
#define PLANE_SPEED 1.0 //�ɻ��ƶ��ٶ�
#define ENEMY_MAX_NUM 20 //�л��������
#define BULLET_NUM 50 //�ӵ�����

typedef struct {
	float x; //x����
	float y; //y����
} POS; //λ�ýṹ��

//��ҷɻ���״̬������������������С�������ɡ���˫״̬
enum {
	PLANE_STATE_NORMAL = 0, //����״̬
	PLANE_STATE_SHOOTING, //���״̬
	PLANE_STATE_CHARGING, //������״̬
	PLANE_STATE_CHARGED, //�������״̬
	PLANE_STATE_MEGA //��˫״̬
}; //��ҷɻ�״̬ö��

//�л����ͣ���ͨ�л�����Ӣ�л���BOSS�л�
enum {
	ENEMY_TYPE_NORMAL = 0, //��ͨ�л�
	ENEMY_TYPE_ELITE, //��Ӣ�л�
	ENEMY_TYPE_BOSS //BOSS�л�
}; //�л�����ö��


typedef struct {
	POS plane_pos; //�ɻ�λ��
	POS start_pos; //�ɻ���ʼλ��
	POS bullet_pos[BULLET_NUM]; //�ӵ�λ��
	float speed; //�ɻ����ٶ�
	int bullet_num; //�ӵ�����
	float bullet_speed; //�ӵ��ٶ�
	float maxlife; //�ɻ��������ֵ
	float life; //�ɻ�����ֵ
	float power; //�ɻ�����(��������ҷɻ�)
	float endurance; //�ɻ��;öȣ���������ҷɻ���
	int plane_state; //�ɻ�״̬��0-������1-�����2-�����У�3-������ɣ�4-��˫״̬��(��������ҷɻ�)
	bool is_alive; //�ɻ��Ƿ���(�����ڵл�)
	int plane_type; //�ɻ����ͣ�0-��ͨ�л���1-��Ӣ�л���2-BOSS�л���
	time_t generate_time; //����ʱ��(�����ڵл�)
} PLANE; //�ɻ��ṹ��
//�ɻ��ṹ�壬�����ɻ�λ�á��ӵ�λ�á��ٶȺ��ӵ���������Ϣ

enum {
	BULLET_TYPE_NORMAL = 0, //��ͨ�ӵ�
	BULLET_TYPE_MEGA, //��˫�ӵ�
	BULLET_TYPE_LASER //����
}; //�ӵ�����ö��
typedef struct {
	POS bullet_pos; //�ӵ�λ��
	POS start_pos; //�ӵ���ʼλ��
	int bullet_num; //�ӵ�����
	float bullet_speed; //�ӵ��ٶ�
	bool is_active; //�ӵ��Ƿ񼤻�
	int bullet_type; //�ӵ�����
	int bullet_damage; //�ӵ��˺�
	int bullet_size; //�ӵ���С
	int bullet_color; //�ӵ���ɫ
	int byllet_type; //�ӵ����ͣ�0-��ͨ�ӵ���1-��˫�ӵ���2-���⣩
	time_t generate_time; //����ʱ��
} BULLET; //�ӵ��ṹ��
//�ӵ��ṹ�壬�����ӵ�λ�á��������ٶȵ���Ϣ

// ������Ϸ�е�ȫ�ֱ����ͳ���
//static���ڶ���ȫ�ֱ�������Щ���������������ж����Է���
static PLANE my_plane; //����һ��ȫ�ֱ���my_plane����ʾ�ɻ�
static PLANE enemy_plane[ENEMY_MAX_NUM]; //����һ��ȫ�ֱ���enemy_plane����ʾ�л�
static BULLET bullet[BULLET_NUM]; //����һ��ȫ�ֱ���bullet����ʾ�ӵ�
static BULLET mega_bullet[2]; //����һ��ȫ�ֱ���mega_bullet����ʾ�����ӵ�
static BULLET enemy_bullet[ENEMY_MAX_NUM]; //����һ��ȫ�ֱ���enemy_bullet����ʾ�л��ӵ�
static BULLET laser_bullet[ENEMY_MAX_NUM]; //����һ��ȫ�ֱ���laser_bullet����ʾ����

static int enemy_num = 0; //�л�����
static time_t start_time; //��¼��Ϸ��ʼʱ��
static time_t end_time; //��¼��Ϸ����ʱ��
static time_t last_shoot_time = clock(); //��¼�ϴ����ʱ��
static time_t last_generate_enemy_time = clock(); //��¼�ϴ����ɵл�ʱ��
static time_t last_added_time = clock(); //��¼�ϴ�����;õ�ʱ��
static IMAGE bg[5]; //����ͼƬ

static IMAGE plane[6]; //�ɻ�ͼƬ
static IMAGE enemy[3]; //�л�ͼƬ
static IMAGE elite[3]; //��Ӣ�л�ͼƬ
static IMAGE boss[2]; //BOSSͼƬ
static IMAGE bullet_image[6]; //�ӵ�ͼƬ
static IMAGE mega_bullet_image[6]; //�����ӵ�ͼƬ
static IMAGE mega_time; //��˫ʱ��ͼƬ
static IMAGE enemy_bullet_image[4]; //�л��ӵ�ͼƬ
static IMAGE laser_image[4]; //����ͼƬ

static int score = 0; //����
static int level = 1; //��Ϸ�ȼ�
static int game_state = 0; //��Ϸ״̬��0-δ��ʼ��1-�����У�2-������

//��Ч��ر���
static HSTREAM bullet_sound; //�ӵ���Ч
static HSTREAM enemy_down_sound; //�л���������Ч
static HSTREAM elite_down_sound; //��Ӣ�л���������Ч
static HSTREAM boss_down_sound; //BOSS��������Ч
static HSTREAM bullet_hit_sound; //�ӵ�������Ч

