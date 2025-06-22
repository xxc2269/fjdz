#pragma once//���ڷ�ֹͷ�ļ�����ΰ���
#include"defines.h"//�����궨��ͷ�ļ�(�Ѱ����˱�׼ͷ�ļ�)

//�ϳ�͸��ͼƬ
void putTransparentImage(int x, int y, IMAGE* image, IMAGE* mask) {
	putimage(x, y, mask, SRCAND); // ʹ��SRCANDģʽ��������
	putimage(x, y, image, SRCPAINT); // ʹ��SRCPAINTģʽ����ͼƬ
}

//����ͼƬ
void loadimages() {

	//���ر���ͼƬ
	loadimage(&bg[0], "src/ColorImages/bg/bg1.jpg"); //���ر���ͼƬ1
	loadimage(&bg[1], "src/ColorImages/bg/bg2.jpg"); //���ر���ͼƬ2
	loadimage(&bg[2], "src/ColorImages/bg/bg3.jpg"); //���ر���ͼƬ3
	loadimage(&bg[3], "src/ColorImages/bg/bg4.jpg"); //���ر���ͼƬ4
	loadimage(&bg[4], "src/ColorImages/bg/bg5.jpg"); //���ر���ͼƬ5

	//���طɻ�ͼƬ
	loadimage(&plane[0], "src/ColorImages/plane/hero0.png", PLANE_SIZE, PLANE_SIZE); //���طɻ�ͼƬ1
	loadimage(&plane[1], "src/ColorImages/plane/hero1.png", PLANE_SIZE, PLANE_SIZE); //���طɻ�ͼƬ2
	loadimage(&plane[2], "src/ColorImages/plane/hero2.png", PLANE_SIZE, PLANE_SIZE); //���طɻ�ͼƬ3
	loadimage(&plane[3], "src/ColorImages/plane/hero3.png", PLANE_SIZE, PLANE_SIZE); //���طɻ�ͼƬ4
	loadimage(&plane[4], "src/ColorImages/plane/hero4.png", PLANE_SIZE, PLANE_SIZE); //���طɻ�ͼƬ5
	loadimage(&plane[5], "/src/ColorImages/plane/hero5.png", PLANE_SIZE, PLANE_SIZE); //���طɻ�ͼƬ6

	//���طɻ�����ͼƬ
	loadimage(&plane_mask[0], "src/ColorImages/plane/hero0.bmp", PLANE_SIZE, PLANE_SIZE); //���طɻ�����ͼƬ1
	loadimage(&plane_mask[1], "src/ColorImages/plane/hero1.bmp", PLANE_SIZE, PLANE_SIZE); //���طɻ�����ͼƬ2
	loadimage(&plane_mask[2], "src/ColorImages/plane/hero2.bmp", PLANE_SIZE, PLANE_SIZE); //���طɻ�����ͼƬ3
	loadimage(&plane_mask[3], "src/ColorImages/plane/hero3.bmp", PLANE_SIZE, PLANE_SIZE); //���طɻ�����ͼƬ4
	loadimage(&plane_mask[4], "src/ColorImages/plane/hero4.bmp", PLANE_SIZE, PLANE_SIZE); //���طɻ�����ͼƬ5
	loadimage(&plane_mask[5], "src/ColorImages/plane/hero5.bmp", PLANE_SIZE, PLANE_SIZE); //���طɻ�����ͼƬ6


	//���صл�ͼƬ
	loadimage(&enemy[0], "src/ColorImages/plane/enemy1.png", PLANE_SIZE, PLANE_SIZE); //���صл�ͼƬ1
	loadimage(&enemy[1], "src/ColorImages/plane/enemy2.png", PLANE_SIZE, PLANE_SIZE); //���صл�ͼƬ2
	loadimage(&enemy[2], "src/ColorImages/plane/enemy3.png", PLANE_SIZE, PLANE_SIZE); //���صл�ͼƬ3
	//���صл�����ͼƬ
	loadimage(&enemy_mask[0], "src/ColorImages/plane/enemy1.bmp", PLANE_SIZE, PLANE_SIZE); //���صл�����ͼƬ1
	loadimage(&enemy_mask[1], "src/ColorImages/plane/enemy2.bmp", PLANE_SIZE, PLANE_SIZE); //���صл�����ͼƬ2
	loadimage(&enemy_mask[2], "src/ColorImages/plane/enemy3.bmp", PLANE_SIZE, PLANE_SIZE); //���صл�����ͼƬ3




	//���ؾ�Ӣ�л�ͼƬ
	loadimage(&elite[0], "src/ColorImages/plane/elite1.png"); //���ؾ�Ӣ�л�ͼƬ1
	loadimage(&elite[1], "src/ColorImages/plane/elite2.png"); //���ؾ�Ӣ�л�ͼƬ2
	loadimage(&elite[2], "src/ColorImages/plane/elite3.png"); //���ؾ�Ӣ�л�ͼƬ3
	//���ؾ�Ӣ�л�����ͼƬ
	loadimage(&elite_mask[0], "src/ColorImages/plane/elite1.bmp"); //���ؾ�Ӣ�л�����ͼƬ1
	loadimage(&elite_mask[1], "src/ColorImages/plane/elite2.bmp"); //���ؾ�Ӣ�л�����ͼƬ2
	loadimage(&elite_mask[2], "src/ColorImages/plane/elite3.bmp"); //���ؾ�Ӣ�л�����ͼƬ3

	//����BOSSͼƬ
	loadimage(&boss[0], "src/ColorImages/plane/boss.png"); //����BOSSͼƬ1
	loadimage(&boss[1], "src/ColorImages/plane/boss2.png"); //����BOSSͼƬ2
	//����BOSS����ͼƬ
	loadimage(&boss_mask[0], "src/ColorImages/plane/boss.bmp"); //����BOSS����ͼƬ1
	loadimage(&boss_mask[1], "src/ColorImages/plane/boss2.bmp"); //����BOSS����ͼƬ2


	//�����ӵ�ͼƬ
	loadimage(&bullet_image[0], "src/ColorImages/bullet/0.png"); //�����ӵ�ͼƬ
	loadimage(&bullet_image[1], "src/ColorImages/bullet/1.png"); //�����ӵ�ͼƬ2
	loadimage(&bullet_image[2], "src/ColorImages/bullet/2.png"); //�����ӵ�ͼƬ3
	loadimage(&bullet_image[3], "src/ColorImages/bullet/3.png"); //�����ӵ�ͼƬ4
	loadimage(&bullet_image[4], "src/ColorImages/bullet/4.png"); //�����ӵ�ͼƬ5
	loadimage(&bullet_image[5], "src/ColorImages/bullet/5.png"); //�����ӵ�ͼƬ6
	//�����ӵ�����ͼƬ
	loadimage(&bullet_mask[0], "src/ColorImages/bullet/0.bmp"); //�����ӵ�����ͼƬ1
	loadimage(&bullet_mask[1], "src/ColorImages/bullet/1.bmp"); //�����ӵ�����ͼƬ2
	loadimage(&bullet_mask[2], "src/ColorImages/bullet/2.bmp"); //�����ӵ�����ͼƬ3
	loadimage(&bullet_mask[3], "src/ColorImages/bullet/3.bmp"); //�����ӵ�����ͼƬ4
	loadimage(&bullet_mask[4], "src/ColorImages/bullet/4.bmp"); //�����ӵ�����ͼƬ5
	loadimage(&bullet_mask[5], "src/ColorImages/bullet/5.bmp"); //�����ӵ�����ͼƬ6


	//���س����ӵ�ͼƬ
	loadimage(&mega_bullet_image[0], "src/ColorImages/bullet/mega0.png"); //���س����ӵ�ͼƬ1
	loadimage(&mega_bullet_image[1], "src/ColorImages/bullet/mega1.png"); //���س����ӵ�ͼƬ2
	loadimage(&mega_bullet_image[2], "src/ColorImages/bullet/mega2.png"); //���س����ӵ�ͼƬ3
	loadimage(&mega_bullet_image[3], "src/ColorImages/bullet/mega3.png"); //���س����ӵ�ͼƬ4
	loadimage(&mega_bullet_image[4], "src/ColorImages/bullet/mega4.png"); //���س����ӵ�ͼƬ5
	loadimage(&mega_bullet_image[5], "src/ColorImages/bullet/mega5.png"); //���س����ӵ�ͼƬ6
	//���س����ӵ�����ͼƬ
	loadimage(&mega_bullet_mask[0], "src/ColorImages/bullet/mega0.bmp"); //���س����ӵ�����ͼƬ1
	loadimage(&mega_bullet_mask[1], "src/ColorImages/bullet/mega1.bmp"); //���س����ӵ�����ͼƬ2
	loadimage(&mega_bullet_mask[2], "src/ColorImages/bullet/mega2.bmp"); //���س����ӵ�����ͼƬ3
	loadimage(&mega_bullet_mask[3], "src/ColorImages/bullet/mega3.bmp"); //���س����ӵ�����ͼƬ4
	loadimage(&mega_bullet_mask[4], "src/ColorImages/bullet/mega4.bmp"); //���س����ӵ�����ͼƬ5
	loadimage(&mega_bullet_mask[5], "src/ColorImages/bullet/mega5.bmp"); //���س����ӵ�����ͼƬ6


	//������˫ʱ��ʱ�ӵ���ͼƬ
	loadimage(&mega_time, "src/ColorImages/bullet/mega_time.png"); //������˫ʱ��ʱ�ӵ���ͼƬ
	//������˫�ӵ�����ͼƬ
	loadimage(&mega_time_mask, "src/ColorImages/bullet/mega_time.bmp"); //������˫ʱ��ʱ�ӵ�������ͼƬ

	//���صл��ӵ�ͼƬ
	loadimage(&enemy_bullet_image[0], "src/ColorImages/bullet/enemy_bullet0.png"); //���صл��ӵ�ͼƬ1
	loadimage(&enemy_bullet_image[1], "src/ColorImages/bullet/enemy_bullet1.png"); //���صл��ӵ�ͼƬ2
	loadimage(&enemy_bullet_image[2], "src/ColorImages/bullet/enemy_bullet2.png"); //���صл��ӵ�ͼƬ3
	loadimage(&enemy_bullet_image[3], "src/ColorImages/bullet/enemy_bullet3.png"); //���صл��ӵ�ͼƬ4
	//���صл��ӵ�����ͼƬ
	loadimage(&enemy_bullet_mask[0], "src/ColorImages/bullet/enemy_bullet0.bmp"); //���صл��ӵ�����ͼƬ1
	loadimage(&enemy_bullet_mask[1], "src/ColorImages/bullet/enemy_bullet1.bmp"); //���صл��ӵ�����ͼƬ2
	loadimage(&enemy_bullet_mask[2], "src/ColorImages/bullet/enemy_bullet2.bmp"); //���صл��ӵ�����ͼƬ3
	loadimage(&enemy_bullet_mask[3], "src/ColorImages/bullet/enemy_bullet3.bmp"); //���صл��ӵ�����ͼƬ4



	//���ؼ���ͼƬ
	loadimage(&laser_image[0], "src/ColorImages/bullet/laser.png"); //���ؼ���ͼƬ1
	loadimage(&laser_image[1], "src/ColorImages/bullet/laser1.png"); //���ؼ���ͼƬ2
	loadimage(&laser_image[2], "src/ColorImages/bullet/laser2.png"); //���ؼ���ͼƬ3
	loadimage(&laser_image[3], "src/ColorImages/bullet/laser3.png"); //���ؼ���ͼƬ4
	//���ؼ�������ͼƬ
	loadimage(&laser_mask[0], "src/ColorImages/bullet/laser.bmp"); //���ؼ�������ͼƬ1
	loadimage(&laser_mask[1], "src/ColorImages/bullet/laser1.bmp"); //���ؼ�������ͼƬ2
	loadimage(&laser_mask[2], "src/ColorImages/bullet/laser2.bmp"); //���ؼ�������ͼƬ3
	loadimage(&laser_mask[3], "src/ColorImages/bullet/laser3.bmp"); //���ؼ�������ͼƬ4
	
	

}
