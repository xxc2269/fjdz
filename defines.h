#pragma once//用于
#include"includes.h"

#define SCREEN_WIDTH 512 //屏幕宽度
#define SCREEN_HEIGHT 720 //屏幕高度
#define PLANE_SIZE 50 //飞机大小
#define PLANE_SPEED 1.0 //飞机移动速度
#define ENEMY_MAX_NUM 20 //敌机最大数量
#define BULLET_NUM 50 //子弹数量

typedef struct {
	float x; //x坐标
	float y; //y坐标
} POS; //位置结构体

//玩家飞机的状态：正常、射击、蓄力中、蓄力完成、无双状态
enum {
	PLANE_STATE_NORMAL = 0, //正常状态
	PLANE_STATE_SHOOTING, //射击状态
	PLANE_STATE_CHARGING, //蓄力中状态
	PLANE_STATE_CHARGED, //蓄力完成状态
	PLANE_STATE_MEGA //无双状态
}; //玩家飞机状态枚举

//敌机类型：普通敌机、精英敌机、BOSS敌机
enum {
	ENEMY_TYPE_NORMAL = 0, //普通敌机
	ENEMY_TYPE_ELITE, //精英敌机
	ENEMY_TYPE_BOSS //BOSS敌机
}; //敌机类型枚举


typedef struct {
	POS plane_pos; //飞机位置
	POS start_pos; //飞机起始位置
	POS bullet_pos[BULLET_NUM]; //子弹位置
	float speed; //飞机的速度
	int bullet_num; //子弹数量
	float bullet_speed; //子弹速度
	float maxlife; //飞机最大生命值
	float life; //飞机生命值
	float power; //飞机火力(仅用于玩家飞机)
	float endurance; //飞机耐久度（仅用于玩家飞机）
	int plane_state; //飞机状态（0-正常，1-射击，2-蓄力中，3-蓄力完成，4-无双状态）(仅用于玩家飞机)
	bool is_alive; //飞机是否存活(仅用于敌机)
	int plane_type; //飞机类型（0-普通敌机，1-精英敌机，2-BOSS敌机）
	time_t generate_time; //生成时间(仅用于敌机)
} PLANE; //飞机结构体
//飞机结构体，包含飞机位置、子弹位置、速度和子弹数量等信息

enum {
	BULLET_TYPE_NORMAL = 0, //普通子弹
	BULLET_TYPE_MEGA, //无双子弹
	BULLET_TYPE_LASER //激光
}; //子弹类型枚举
typedef struct {
	POS bullet_pos; //子弹位置
	POS start_pos; //子弹起始位置
	int bullet_num; //子弹数量
	float bullet_speed; //子弹速度
	bool is_active; //子弹是否激活
	int bullet_type; //子弹类型
	int bullet_damage; //子弹伤害
	int bullet_size; //子弹大小
	int bullet_color; //子弹颜色
	int byllet_type; //子弹类型（0-普通子弹，1-无双子弹，2-激光）
	time_t generate_time; //生成时间
} BULLET; //子弹结构体
//子弹结构体，包含子弹位置、数量、速度等信息

// 定义游戏中的全局变量和常量
//static用于定义全局变量，这些变量在整个程序中都可以访问
static PLANE my_plane; //定义一个全局变量my_plane，表示飞机
static PLANE enemy_plane[ENEMY_MAX_NUM]; //定义一个全局变量enemy_plane，表示敌机
static BULLET bullet[BULLET_NUM]; //定义一个全局变量bullet，表示子弹
static BULLET mega_bullet[2]; //定义一个全局变量mega_bullet，表示超级子弹
static BULLET enemy_bullet[ENEMY_MAX_NUM]; //定义一个全局变量enemy_bullet，表示敌机子弹
static BULLET laser_bullet[ENEMY_MAX_NUM]; //定义一个全局变量laser_bullet，表示激光

static int enemy_num = 0; //敌机数量
static time_t start_time; //记录游戏开始时间
static time_t end_time; //记录游戏结束时间
static time_t last_shoot_time = clock(); //记录上次射击时间
static time_t last_generate_enemy_time = clock(); //记录上次生成敌机时间
static time_t last_added_time = clock(); //记录上次添加耐久的时间
static IMAGE bg[5]; //背景图片

static IMAGE plane[6]; //飞机图片
static IMAGE enemy[3]; //敌机图片
static IMAGE elite[3]; //精英敌机图片
static IMAGE boss[2]; //BOSS图片
static IMAGE bullet_image[6]; //子弹图片
static IMAGE mega_bullet_image[6]; //超级子弹图片
static IMAGE mega_time; //无双时间图片
static IMAGE enemy_bullet_image[4]; //敌机子弹图片
static IMAGE laser_image[4]; //激光图片

static int score = 0; //分数
static int level = 1; //游戏等级
static int game_state = 0; //游戏状态（0-未开始，1-进行中，2-结束）

//音效相关变量
static HSTREAM bullet_sound; //子弹音效
static HSTREAM enemy_down_sound; //敌机被击落音效
static HSTREAM elite_down_sound; //精英敌机被击落音效
static HSTREAM boss_down_sound; //BOSS被击落音效
static HSTREAM bullet_hit_sound; //子弹击中音效

