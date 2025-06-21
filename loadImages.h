#pragma once//用于防止头文件被多次包含
#include"defines.h"//包含宏定义头文件(已包含了标准头文件)

//加载图片
void loadimages() {

	//加载背景图片
	loadimage(&bg[0], "src/ColorImages/bg/bg1.jpg"); //加载背景图片1
	loadimage(&bg[1], "src/ColorImages/bg/bg2.jpg"); //加载背景图片2
	loadimage(&bg[2], "src/ColorImages/bg/bg3.jpg"); //加载背景图片3
	loadimage(&bg[3], "src/ColorImages/bg/bg4.jpg"); //加载背景图片4
	loadimage(&bg[4], "src/ColorImages/bg/bg5.jpg"); //加载背景图片5

	//加载飞机图片
	loadimage(&plane[0], "src/ColorImages/plane/hero0.png", PLANE_SIZE, PLANE_SIZE); //加载飞机图片1
	loadimage(&plane[1], "src/ColorImages/plane/hero1.png", PLANE_SIZE, PLANE_SIZE); //加载飞机图片2
	loadimage(&plane[2], "src/ColorImages/plane/hero2.png", PLANE_SIZE, PLANE_SIZE); //加载飞机图片3
	loadimage(&plane[3], "src/ColorImages/plane/hero3.png", PLANE_SIZE, PLANE_SIZE); //加载飞机图片4
	loadimage(&plane[4], "src/ColorImages/plane/hero4.png", PLANE_SIZE, PLANE_SIZE); //加载飞机图片5
	loadimage(&plane[5], "/src/ColorImages/plane/hero5.png", PLANE_SIZE, PLANE_SIZE); //加载飞机图片6

	//加载敌机图片
	loadimage(&enemy[0], "src/ColorImages/plane/enemy1.png", PLANE_SIZE, PLANE_SIZE); //加载敌机图片1
	loadimage(&enemy[1], "src/ColorImages/plane/enemy2.png", PLANE_SIZE, PLANE_SIZE); //加载敌机图片2
	loadimage(&enemy[2], "src/ColorImages/plane/enemy3.png", PLANE_SIZE, PLANE_SIZE); //加载敌机图片3



	//加载精英敌机图片
	loadimage(&elite[1], "src/ColorImages/plane/elite2.png"); //加载精英敌机图片2
	loadimage(&elite[2], "src/ColorImages/plane/elite3.png"); //加载精英敌机图片3

	//加载BOSS图片
	loadimage(&boss[0], "src/ColorImages/plane/boss.png"); //加载BOSS图片1
	loadimage(&boss[1], "src/ColorImages/plane/boss2.png"); //加载BOSS图片2

	//加载子弹图片
	loadimage(&bullet_image[0], "src/ColorImages/bullet/0.png"); //加载子弹图片
	loadimage(&bullet_image[1], "src/ColorImages/bullet/1.png"); //加载子弹图片2
	loadimage(&bullet_image[2], "src/ColorImages/bullet/2.png"); //加载子弹图片3
	loadimage(&bullet_image[3], "src/ColorImages/bullet/3.png"); //加载子弹图片4
	loadimage(&bullet_image[4], "src/ColorImages/bullet/4.png"); //加载子弹图片5
	loadimage(&bullet_image[5], "src/ColorImages/bullet/5.png"); //加载子弹图片6

	//加载超级子弹图片
	loadimage(&mega_bullet_image[0], "src/ColorImages/bullet/mega0.png"); //加载超级子弹图片1
	loadimage(&mega_bullet_image[1], "src/ColorImages/bullet/mega1.png"); //加载超级子弹图片2
	loadimage(&mega_bullet_image[2], "src/ColorImages/bullet/mega2.png"); //加载超级子弹图片3
	loadimage(&mega_bullet_image[3], "src/ColorImages/bullet/mega3.png"); //加载超级子弹图片4
	loadimage(&mega_bullet_image[4], "src/ColorImages/bullet/mega4.png"); //加载超级子弹图片5
	loadimage(&mega_bullet_image[5], "src/ColorImages/bullet/mega5.png"); //加载超级子弹图片6

	//加载无双时间时子弹的图片
	loadimage(&mega_time, "src/ColorImages/bullet/mega_time.png"); //加载无双时间时子弹的图片

	//加载敌机子弹图片
	loadimage(&enemy_bullet_image[0], "src/ColorImages/bullet/enemy_bullet0.png"); //加载敌机子弹图片1
	loadimage(&enemy_bullet_image[1], "src/ColorImages/bullet/enemy_bullet1.png"); //加载敌机子弹图片2
	loadimage(&enemy_bullet_image[2], "src/ColorImages/bullet/enemy_bullet2.png"); //加载敌机子弹图片3
	loadimage(&enemy_bullet_image[3], "src/ColorImages/bullet/enemy_bullet3.png"); //加载敌机子弹图片4


	//加载激光图片
	loadimage(&laser_image[0], "src/ColorImages/bullet/laser.png"); //加载激光图片1
	loadimage(&laser_image[1], "src/ColorImages/bullet/laser1.png"); //加载激光图片2
	loadimage(&laser_image[2], "src/ColorImages/bullet/laser2.png"); //加载激光图片3
	loadimage(&laser_image[3], "src/ColorImages/bullet/laser3.png"); //加载激光图片4

}
