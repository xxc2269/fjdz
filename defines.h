#pragma once//用于
#include"includes.h"

#define SCREEN_WIDTH 512 //屏幕宽度
#define SCREEN_HEIGHT 720 //屏幕高度
#define PLANE_SIZE 50 //飞机大小
#define PLANE_ELITE_SIZE 102//精英敌机大小
#define BOSS_SIZE 200 //BOSS大小
#define MEGA_SIZE 273 //无双子弹大小
#define BOSS_HEIGHT 140 //BOSS高度
#define PLANE_SPEED 1.0 //飞机移动速度
#define ENEMY_MAX_NUM 20 //敌机最大数量
#define BULLET_NUM 50 //子弹数量
#define ITEM_NUM 10//收集物数量

#define ENEMY_LIFE 50 //敌机生命值
#define ELITE_ENEMY_LIFE 200 //精英敌机生命值
#define BOSS_LIFE 2000 //BOSS生命值

#define GRADE1_SCORE 100 //一级气势分数
#define GRADE2_SCORE 110 //二级气势分数
#define GRADE3_SCORE 120 //三级气势分数
#define GRADE4_SCORE 150 //四级气势分数
#define GRADE5_SCORE 400 //五级气势分数

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
	PLANE_STATE_MEGA_NORMAL, //无双状态
	PLANE_STATE_MEGA_SHOOTING, //无双射击状态
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
	float power; //飞机气势(仅用于玩家飞机)
	int grade; //飞机气势等级(仅用于玩家飞机)
	int size; //飞机大小
	int height; //飞机高度
	float endurance; //飞机耐久度（仅用于玩家飞机）
	float max_endurance; //飞机最大耐久度（仅用于玩家飞机）
	int plane_state; //飞机状态（0-正常，1-射击，2-蓄力中，3-蓄力完成，4-无双状态）(仅用于玩家飞机)
	bool is_alive; //飞机是否存活(仅用于敌机)
	bool is_hitted_by_mega; //是否被重击子弹击中(仅用于敌机)
	int plane_type; //飞机类型（0-普通敌机，1-精英敌机，2-BOSS敌机）
	time_t generate_time; //生成时间(仅用于敌机)
	time_t last_shoot_time; //上次射击时间
	int style; //飞机样式

	
} PLANE; //飞机结构体
//飞机结构体，包含飞机位置、子弹位置、速度和子弹数量等信息

enum {
	BULLET_TYPE_NORMAL = 0, //普通子弹
	BULLET_TYPE_BIG, //大子弹
	BULLET_TYPE_MEGA, //无双子弹
	BULLET_TYPE_LASER, //激光
	BULLET_TYPE_TRACKING //追踪子弹
}; //子弹类型枚举
typedef struct {
	bool is_active; //子弹是否激活
	POS bullet_pos; //子弹位置
	POS start_pos; //子弹起始位置
	int bullet_num; //子弹数量
	float bullet_speed; //子弹速度
	POS aim_pos;//子弹目标位置（仅用于追踪子弹）
	int bullet_type; //子弹类型
	int bullet_grade; //无双子弹等级
	int bullet_damage; //子弹伤害
	int bullet_size; //子弹大小
	int bullet_color; //子弹颜色
	int byllet_type; //子弹类型（0-普通子弹，1-无双子弹，2-激光）
	time_t generate_time; //生成时间
} BULLET; //子弹结构体
//子弹结构体，包含子弹位置、数量、速度等信息

//收集物品类型：小生命球、大生命球、补给球、大补给球
enum {
	ITEM_TYPE_SMALL_LIFE = 0, //小生命球
	ITEM_TYPE_BIG_LIFE = 1, //大生命球
	ITEM_TYPE_SUPPLY = 2, //补给球
	ITEM_TYPE_BIG_SUPPLY = 3 //大补给球
}; //收集物品类型枚举
typedef struct {
	bool is_active; //物品是否激活
	POS item_pos; //物品位置
	POS start_pos; //物品起始位置
	int item_type; //物品类型（0-小生命球，1-大生命球，2-补给球，3-大补给球）
	int item_size; //物品大小
	time_t generate_time; //生成时间
	float item_speed; //物品移动速度
} ITEM; //收集物品结构体;

// 定义游戏中的全局变量和常量
//static用于定义全局变量，这些变量在整个程序中都可以访问
static ITEM drop_item[10]; //定义一个全局变量drop_item，表示掉落物品
static int drop_item_num = 0; //掉落物品数量
static bool boss_is_alive = false; //BOSS是否存活
static PLANE my_plane; //定义一个全局变量my_plane，表示飞机
static PLANE enemy_plane[ENEMY_MAX_NUM]; //定义一个全局变量enemy_plane，表示敌机
static BULLET bullet[BULLET_NUM]; //定义一个全局变量bullet，表示玩家子弹
static BULLET mega_bullet[2]; //定义一个全局变量mega_bullet，表示超级子弹
static BULLET enemy_bullet[BULLET_NUM]; //定义一个全局变量enemy_bullet，表示敌机子弹
static BULLET laser_bullet[ENEMY_MAX_NUM]; //定义一个全局变量laser_bullet，表示激光
static ITEM item[ITEM_NUM]; //定义一个全局变量item，表示收集物品

static int enemy_num = 0; //敌机数量
static int  enemy_bullet_num; //敌机子弹数量
static time_t start_time; //记录游戏开始时间
static time_t end_time; //记录游戏结束时间
static time_t last_complete_time = clock(); //记录上次通关时间
static time_t last_shoot_time = clock(); //记录上次射击时间
static time_t last_generate_enemy_time = clock(); //记录上次生成敌机时间
static time_t last_added_time = clock(); //记录上次添加耐久的时间
static time_t start_charge_time = clock(); //记录开始蓄力的时间
static time_t charge_time = 0; //记录蓄力时间
static time_t last_power_time; //记录上次减少气势的时间
static IMAGE bg[5]; //背景图片

static IMAGE plane[6]; //飞机图片
static IMAGE plane_mask[6]; //飞机掩码图片
static IMAGE enemy[3]; //敌机图片
static IMAGE enemy_mask[3]; //敌机掩码图片
static IMAGE elite[3]; //精英敌机图片
static IMAGE elite_mask[3]; //精英敌机掩码图片
static IMAGE boss[2]; //BOSS图片
static IMAGE boss_mask[2]; //BOSS掩码图片
static IMAGE bullet_image[6]; //子弹图片
static IMAGE bullet_mask[6]; //子弹掩码图片
static IMAGE mega_bullet_image[6]; //超级子弹图片
static IMAGE mega_bullet_mask[6]; //超级子弹掩码图片
static IMAGE mega_time; //无双时间图片
static IMAGE mega_time_mask; //无双时间掩码图片
static IMAGE enemy_bullet_image[4]; //敌机子弹图片
static IMAGE enemy_bullet_mask[4]; //敌机子弹掩码图片
static IMAGE laser_image[4]; //激光图片
static IMAGE laser_mask[4]; //激光掩码图片

static IMAGE life_image; //生命图片
static IMAGE life_mask; //生命掩码图片
static IMAGE mega_life_image; //大生命图片
static IMAGE mega_life_mask; //大生命掩码图片
static IMAGE power_image; //气势图片
static IMAGE power_mask; //气势掩码图片
static IMAGE mega_power_image; //大气势图片
static IMAGE mega_power_mask; //大气势掩码图片

static int score = 0; //分数
static int level = 1; //游戏等级
static int game_state = 0; //游戏状态（0-未开始，1-进行中，2-结束）

//背景音乐
static HSAMPLE bgm1; //背景音乐1
static HSTREAM bgm2; //背景音乐2
static HSTREAM bgm3; //背景音乐3
static HSTREAM bgm4; //背景音乐4
static HSTREAM bgm5; //背景音乐5
static HSTREAM over; //游戏结束音乐

static HCHANNEL BGM; //背景音乐通道

//音效相关变量
static HSTREAM bullet_sound; //子弹音效
static HSTREAM mega_bullet_sound; //超级子弹音效
static HSTREAM enemy_down_sound; //敌机被击落音效
static HSTREAM elite_down_sound; //精英敌机被击落音效
static HSTREAM boss_down_sound; //BOSS被击落音效
static HSTREAM bullet_hit_sound; //子弹击中音效
static HSTREAM mega_bullet_hit_sound; //超级子弹击中音效

static HSTREAM grade1_sound; //一级音效
static HSTREAM grade2_sound; //二级音效
static HSTREAM grade3_sound; //三级音效
static HSTREAM grade4_sound; //四级音效
static HSTREAM grade5_sound; //五级音效