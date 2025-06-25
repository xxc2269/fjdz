#pragma once//����
#include"includes.h"

#define SCREEN_WIDTH 512 //��Ļ���
#define SCREEN_HEIGHT 720 //��Ļ�߶�
#define PLANE_SIZE 50 //�ɻ���С
#define PLANE_ELITE_SIZE 102//��Ӣ�л���С
#define BOSS_SIZE 200 //BOSS��С
#define MEGA_SIZE 273 //��˫�ӵ���С
#define BOSS_HEIGHT 140 //BOSS�߶�
#define PLANE_SPEED 1.0 //�ɻ��ƶ��ٶ�
#define ENEMY_MAX_NUM 20 //�л��������
#define BULLET_NUM 50 //�ӵ�����
#define ITEM_NUM 10//�ռ�������

#define ENEMY_LIFE 50 //�л�����ֵ
#define ELITE_ENEMY_LIFE 200 //��Ӣ�л�����ֵ
#define BOSS_LIFE 2000 //BOSS����ֵ

#define GRADE1_SCORE 100 //һ�����Ʒ���
#define GRADE2_SCORE 110 //�������Ʒ���
#define GRADE3_SCORE 120 //�������Ʒ���
#define GRADE4_SCORE 150 //�ļ����Ʒ���
#define GRADE5_SCORE 400 //�弶���Ʒ���

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
	PLANE_STATE_MEGA_NORMAL, //��˫״̬
	PLANE_STATE_MEGA_SHOOTING, //��˫���״̬
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
	int grade; //�ɻ����Ƶȼ�(��������ҷɻ�)
	int size; //�ɻ���С
	int height; //�ɻ��߶�
	float endurance; //�ɻ��;öȣ���������ҷɻ���
	float max_endurance; //�ɻ�����;öȣ���������ҷɻ���
	int plane_state; //�ɻ�״̬��0-������1-�����2-�����У�3-������ɣ�4-��˫״̬��(��������ҷɻ�)
	bool is_alive; //�ɻ��Ƿ���(�����ڵл�)
	bool is_hitted_by_mega; //�Ƿ��ػ��ӵ�����(�����ڵл�)
	int plane_type; //�ɻ����ͣ�0-��ͨ�л���1-��Ӣ�л���2-BOSS�л���
	time_t generate_time; //����ʱ��(�����ڵл�)
	time_t last_shoot_time; //�ϴ����ʱ��
	int style; //�ɻ���ʽ

	
} PLANE; //�ɻ��ṹ��
//�ɻ��ṹ�壬�����ɻ�λ�á��ӵ�λ�á��ٶȺ��ӵ���������Ϣ

enum {
	BULLET_TYPE_NORMAL = 0, //��ͨ�ӵ�
	BULLET_TYPE_BIG, //���ӵ�
	BULLET_TYPE_MEGA, //��˫�ӵ�
	BULLET_TYPE_LASER, //����
	BULLET_TYPE_TRACKING //׷���ӵ�
}; //�ӵ�����ö��
typedef struct {
	bool is_active; //�ӵ��Ƿ񼤻�
	POS bullet_pos; //�ӵ�λ��
	POS start_pos; //�ӵ���ʼλ��
	int bullet_num; //�ӵ�����
	float bullet_speed; //�ӵ��ٶ�
	POS aim_pos;//�ӵ�Ŀ��λ�ã�������׷���ӵ���
	int bullet_type; //�ӵ�����
	int bullet_grade; //��˫�ӵ��ȼ�
	int bullet_damage; //�ӵ��˺�
	int bullet_size; //�ӵ���С
	int bullet_color; //�ӵ���ɫ
	int byllet_type; //�ӵ����ͣ�0-��ͨ�ӵ���1-��˫�ӵ���2-���⣩
	time_t generate_time; //����ʱ��
} BULLET; //�ӵ��ṹ��
//�ӵ��ṹ�壬�����ӵ�λ�á��������ٶȵ���Ϣ

//�ռ���Ʒ���ͣ�С�����򡢴������򡢲����򡢴󲹸���
enum {
	ITEM_TYPE_SMALL_LIFE = 0, //С������
	ITEM_TYPE_BIG_LIFE = 1, //��������
	ITEM_TYPE_SUPPLY = 2, //������
	ITEM_TYPE_BIG_SUPPLY = 3 //�󲹸���
}; //�ռ���Ʒ����ö��
typedef struct {
	bool is_active; //��Ʒ�Ƿ񼤻�
	POS item_pos; //��Ʒλ��
	POS start_pos; //��Ʒ��ʼλ��
	int item_type; //��Ʒ���ͣ�0-С������1-��������2-������3-�󲹸���
	int item_size; //��Ʒ��С
	time_t generate_time; //����ʱ��
	float item_speed; //��Ʒ�ƶ��ٶ�
} ITEM; //�ռ���Ʒ�ṹ��;

// ������Ϸ�е�ȫ�ֱ����ͳ���
//static���ڶ���ȫ�ֱ�������Щ���������������ж����Է���
static ITEM drop_item[10]; //����һ��ȫ�ֱ���drop_item����ʾ������Ʒ
static int drop_item_num = 0; //������Ʒ����
static bool boss_is_alive = false; //BOSS�Ƿ���
static PLANE my_plane; //����һ��ȫ�ֱ���my_plane����ʾ�ɻ�
static PLANE enemy_plane[ENEMY_MAX_NUM]; //����һ��ȫ�ֱ���enemy_plane����ʾ�л�
static BULLET bullet[BULLET_NUM]; //����һ��ȫ�ֱ���bullet����ʾ����ӵ�
static BULLET mega_bullet[2]; //����һ��ȫ�ֱ���mega_bullet����ʾ�����ӵ�
static BULLET enemy_bullet[BULLET_NUM]; //����һ��ȫ�ֱ���enemy_bullet����ʾ�л��ӵ�
static BULLET laser_bullet[ENEMY_MAX_NUM]; //����һ��ȫ�ֱ���laser_bullet����ʾ����
static ITEM item[ITEM_NUM]; //����һ��ȫ�ֱ���item����ʾ�ռ���Ʒ

static int enemy_num = 0; //�л�����
static int  enemy_bullet_num; //�л��ӵ�����
static time_t start_time; //��¼��Ϸ��ʼʱ��
static time_t end_time; //��¼��Ϸ����ʱ��
static time_t last_complete_time = clock(); //��¼�ϴ�ͨ��ʱ��
static time_t last_shoot_time = clock(); //��¼�ϴ����ʱ��
static time_t last_generate_enemy_time = clock(); //��¼�ϴ����ɵл�ʱ��
static time_t last_added_time = clock(); //��¼�ϴ�����;õ�ʱ��
static time_t start_charge_time = clock(); //��¼��ʼ������ʱ��
static time_t charge_time = 0; //��¼����ʱ��
static time_t last_power_time; //��¼�ϴμ������Ƶ�ʱ��
static IMAGE bg[5]; //����ͼƬ

static IMAGE plane[6]; //�ɻ�ͼƬ
static IMAGE plane_mask[6]; //�ɻ�����ͼƬ
static IMAGE enemy[3]; //�л�ͼƬ
static IMAGE enemy_mask[3]; //�л�����ͼƬ
static IMAGE elite[3]; //��Ӣ�л�ͼƬ
static IMAGE elite_mask[3]; //��Ӣ�л�����ͼƬ
static IMAGE boss[2]; //BOSSͼƬ
static IMAGE boss_mask[2]; //BOSS����ͼƬ
static IMAGE bullet_image[6]; //�ӵ�ͼƬ
static IMAGE bullet_mask[6]; //�ӵ�����ͼƬ
static IMAGE mega_bullet_image[6]; //�����ӵ�ͼƬ
static IMAGE mega_bullet_mask[6]; //�����ӵ�����ͼƬ
static IMAGE mega_time; //��˫ʱ��ͼƬ
static IMAGE mega_time_mask; //��˫ʱ������ͼƬ
static IMAGE enemy_bullet_image[4]; //�л��ӵ�ͼƬ
static IMAGE enemy_bullet_mask[4]; //�л��ӵ�����ͼƬ
static IMAGE laser_image[4]; //����ͼƬ
static IMAGE laser_mask[4]; //��������ͼƬ

static IMAGE life_image; //����ͼƬ
static IMAGE life_mask; //��������ͼƬ
static IMAGE mega_life_image; //������ͼƬ
static IMAGE mega_life_mask; //����������ͼƬ
static IMAGE power_image; //����ͼƬ
static IMAGE power_mask; //��������ͼƬ
static IMAGE mega_power_image; //������ͼƬ
static IMAGE mega_power_mask; //����������ͼƬ

static int score = 0; //����
static int level = 1; //��Ϸ�ȼ�
static int game_state = 0; //��Ϸ״̬��0-δ��ʼ��1-�����У�2-������

//��������
static HSAMPLE bgm1; //��������1
static HSTREAM bgm2; //��������2
static HSTREAM bgm3; //��������3
static HSTREAM bgm4; //��������4
static HSTREAM bgm5; //��������5
static HSTREAM over; //��Ϸ��������

static HCHANNEL BGM; //��������ͨ��

//��Ч��ر���
static HSTREAM bullet_sound; //�ӵ���Ч
static HSTREAM mega_bullet_sound; //�����ӵ���Ч
static HSTREAM enemy_down_sound; //�л���������Ч
static HSTREAM elite_down_sound; //��Ӣ�л���������Ч
static HSTREAM boss_down_sound; //BOSS��������Ч
static HSTREAM bullet_hit_sound; //�ӵ�������Ч
static HSTREAM mega_bullet_hit_sound; //�����ӵ�������Ч

static HSTREAM grade1_sound; //һ����Ч
static HSTREAM grade2_sound; //������Ч
static HSTREAM grade3_sound; //������Ч
static HSTREAM grade4_sound; //�ļ���Ч
static HSTREAM grade5_sound; //�弶��Ч