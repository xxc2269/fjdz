#pragma once//���ڷ�ֹͷ�ļ�����ΰ���
#include"defines.h"//�����궨��ͷ�ļ�(�Ѱ����˱�׼ͷ�ļ�)

//��������
void control_plane(); //���Ʒɻ�����
void check_plane_state(); //���ɻ�״̬����
void shoot_bullet(); //�����ӵ�����
void generate_enemy(); //���ɵл�����
void generate_boss(); //����BOSS����
void generate_drop_item(int plane_type,POS plan_pos); //������Ʒ����
void enemy_shoot_bullet(); //���ɵл��ӵ�����
//void generate_laser(); //���ɼ��⺯��
//void generate_mega_bullet(); //������˫�ӵ�����



//����
void control_plane() {
	// �˴�������Ӹ�����Ϸ״̬���߼������紦��ɻ��ƶ����ӵ����䡢�л����ɵ�
	// ����Ϊһ����ѡ�������ü���������Ʒɻ��ƶ�
	//���磬����ɻ��ƶ�
	//if (GetAsyncKeyState(VK_LEFT)) { // ����������
	//	my_plane.plane_pos.x -= my_plane.speed; // �����ƶ�
	//}
	//if (GetAsyncKeyState(VK_RIGHT)) { // ��������Ҽ�
	//	my_plane.plane_pos.x += my_plane.speed; // �����ƶ�
	//}
	//if (GetAsyncKeyState(VK_UP)) { // ��������ϼ�
	//	my_plane.plane_pos.y -= my_plane.speed; // �����ƶ�
	//}
	//if (GetAsyncKeyState(VK_DOWN)) { // ��������¼�
	//	my_plane.plane_pos.y += my_plane.speed; // �����ƶ�
	//}
	//// ȷ���ɻ���������Ļ�߽�
	//if (my_plane.plane_pos.x < 0) {
	//	my_plane.plane_pos.x = 0;
	//}
	//if (my_plane.plane_pos.x > SCREEN_WIDTH - PLANE_SIZE) {
	//	my_plane.plane_pos.x = SCREEN_WIDTH - PLANE_SIZE;
	//}
	//if (my_plane.plane_pos.y < 0) {
	//	my_plane.plane_pos.y = 0;
	//}
	//if (my_plane.plane_pos.y > SCREEN_HEIGHT - PLANE_SIZE) {
	//	my_plane.plane_pos.y = SCREEN_HEIGHT - PLANE_SIZE;
	//}

	//��������һ��������ʹ�����������Ʒɻ��ƶ�
	ExMessage msg; // ����һ��ExMessage�ṹ�����msg�����ڴ洢�����Ϣ�����ڴ����������
	peekmessage(&msg, EM_MOUSE | EM_KEY); // ��ȡ�����Ϣ�ͼ�����Ϣ
	switch (msg.message) { // ������Ϣ���ͽ��д���
	case WM_MOUSEMOVE:
		// ����ƶ��¼�
		my_plane.plane_pos.x = msg.x; // ���÷ɻ�λ��Ϊ���λ��
		my_plane.plane_pos.y = msg.y; // ���÷ɻ�λ��Ϊ���λ��
		break;
	case WM_LBUTTONDOWN:
		// �����������¼�
		if (my_plane.plane_state == PLANE_STATE_NORMAL) { // ����ɻ�״̬Ϊ����
			my_plane.plane_state = PLANE_STATE_SHOOTING; // �л������״̬
		}
		else if (my_plane.plane_state == PLANE_STATE_MEGA_NORMAL) {
			my_plane.plane_state = PLANE_STATE_MEGA_SHOOTING;
		}
		break;
	case WM_LBUTTONUP:
		// �������ɿ��¼�
		if (my_plane.plane_state == PLANE_STATE_SHOOTING) { // ����ɻ�״̬Ϊ���
			my_plane.plane_state = PLANE_STATE_NORMAL; // �л�������״̬
		}
		else if (my_plane.plane_state == PLANE_STATE_MEGA_SHOOTING) {
			my_plane.plane_state = PLANE_STATE_MEGA_NORMAL;
		}
		break;

	case WM_RBUTTONDOWN:
		// ����Ҽ������¼�
		if (my_plane.plane_state == PLANE_STATE_NORMAL && !mega_bullet[0].is_active) { // ����ɻ�״̬Ϊ����
			start_charge_time = clock(); // ��¼��ʼ������ʱ��
			my_plane.plane_state = PLANE_STATE_CHARGING; // �л���������״̬
		}
		break;

	case WM_RBUTTONUP:
		// ����Ҽ��ɿ��¼�
		if (my_plane.plane_state == PLANE_STATE_CHARGING) { // ����ɻ�״̬Ϊ������״̬
			my_plane.plane_state = PLANE_STATE_CHARGED; // �л����������״̬
			charge_time = clock() - start_charge_time; // ��������ʱ��
		}
		break;
	}
}

//���ɻ�״̬Ϊ������״̬ʱ��ÿ����ٷɻ�5���;öȣ���ÿ�����ӷɻ�����100�㣬�����Ƶȼ����Ϊ3��
void check_plane_state() {
	if (my_plane.plane_state == PLANE_STATE_CHARGING && clock() - start_charge_time > 200  ) { // ����ɻ�״̬Ϊ������״̬
		if (my_plane.endurance > 0) {
			my_plane.endurance -= 1; // ÿ����ٷɻ�5���;ö�
			if(my_plane.grade <= 2){
				my_plane.power += 20; // ÿ�����ӷɻ�����100��
			}
			start_charge_time = clock(); // ���ÿ�ʼ������ʱ��
		}
		else {
			my_plane.endurance = 0; // ���;ö�����Ϊ0
			my_plane.plane_state = PLANE_STATE_CHARGED; // �л������״̬
		}
	}
}
	




//�����ӵ�
	void shoot_bullet(){
		if (my_plane.plane_state == PLANE_STATE_SHOOTING && my_plane.endurance > 0) {
			for (int i = 0; i <= my_plane.bullet_num; i++) {
				if (!bullet[i].is_active && clock() - my_plane.last_shoot_time > 200) { // ����ӵ�δ�����Ҿ����ϴ����ʱ�䳬��200����
					// �ӵ�������Ч
					if (bullet_sound) {
						DWORD chan = BASS_SampleGetChannel(bullet_sound, FALSE);
						BASS_ChannelPlay(chan, TRUE);
					}

					//���ݷɻ����Ƶȼ������ӵ����ͺ��˺�
					if (my_plane.grade == 0) { // һ������
						bullet[i].bullet_type = BULLET_TYPE_NORMAL; //
						bullet[i].bullet_damage = 10; // �����ӵ��˺�
					}

					else if (my_plane.grade == 1) { // ��������
						bullet[i].bullet_type = BULLET_TYPE_NORMAL; // 
						bullet[i].bullet_damage = 11; // �����ӵ��˺�
					}

					else if (my_plane.grade == 2) { // ��������
						bullet[i].bullet_type = BULLET_TYPE_NORMAL; // 
						bullet[i].bullet_damage = 12; // �����ӵ��˺�
					}

					else if (my_plane.grade == 3) { // �ļ�����������
						bullet[i].bullet_type = BULLET_TYPE_NORMAL; // 
						bullet[i].bullet_damage = 15; // �����ӵ��˺�
					}

					else if (my_plane.grade >= 4) { // �弶����������
						bullet[i].bullet_type = BULLET_TYPE_NORMAL; //
						bullet[i].bullet_damage = 20; // �����ӵ��˺�
					}

					bullet[i].is_active = true; // �����ӵ�
					bullet[i].start_pos.x = my_plane.plane_pos.x + PLANE_SIZE / 2; // �����ӵ�λ��Ϊ�ɻ�λ��
					bullet[i].bullet_pos.x = bullet[i].start_pos.x; // �����ӵ�λ��Ϊ��ʼλ��
					bullet[i].start_pos.y = my_plane.plane_pos.y - PLANE_SIZE / 2; // �����ӵ�λ��Ϊ�ɻ�λ��
					bullet[i].bullet_pos.y = bullet[i].start_pos.y; // �����ӵ�λ��Ϊ��ʼλ��
					bullet[i].bullet_speed = 0.3; // �����ӵ��ٶ�
					bullet[i].bullet_grade = my_plane.grade; // �����ӵ��ȼ�Ϊ�ɻ��ȼ�
					my_plane.endurance -= 1; // ���ٷɻ��;ö�
					bullet[i].generate_time = clock(); // ��¼�ӵ�����ʱ��
					my_plane.last_shoot_time = clock(); // ��¼���һ�����ʱ��
					if (my_plane.bullet_num < BULLET_NUM) { // ����ӵ�����С������ӵ�����
						my_plane.bullet_num++; // �����ӵ�����
					}
					break; // �˳�ѭ��
				}
			}
		}
		if (my_plane.plane_state == PLANE_STATE_CHARGED) {
			// �ӵ�������Ч
			if (my_plane.grade <= 2) {
				if (bullet_sound) {
					DWORD chan = BASS_SampleGetChannel(bullet_sound, FALSE);
					BASS_ChannelPlay(chan, TRUE);
				}
			}
			else {
				if (mega_bullet_sound) {
					DWORD chan = BASS_SampleGetChannel(mega_bullet_sound, FALSE);
					BASS_ChannelPlay(chan, TRUE);
				}
			}

			//���ݷɻ����Ƶȼ������ӵ����ͺ��˺�
			if (my_plane.grade == 0) { // һ������
				mega_bullet[0].bullet_type = BULLET_TYPE_BIG; //
				mega_bullet[0].bullet_damage = 30; // �����ӵ��˺�
			}

			else if (my_plane.grade == 1) { // ��������
				mega_bullet[0].bullet_type = BULLET_TYPE_BIG; // 
				mega_bullet[0].bullet_damage = 50; // �����ӵ��˺�
			}

			else if (my_plane.grade == 2) { // ��������
				mega_bullet[0].bullet_type = BULLET_TYPE_BIG; // 
				mega_bullet[0].bullet_damage = 100; // �����ӵ��˺�
			}

			else if (my_plane.grade == 3) { // �ļ�����������
				mega_bullet[0].bullet_type = BULLET_TYPE_BIG; // 
				mega_bullet[0].bullet_damage = 150; // �����ӵ��˺�
			}

			else if (my_plane.grade == 4) { // �弶����������
				mega_bullet[0].bullet_type = BULLET_TYPE_BIG; //
				mega_bullet[0].bullet_damage = 200; // �����ӵ��˺�
			}

			else if (my_plane.grade == 5) { // ����
				mega_bullet[0].bullet_type = BULLET_TYPE_BIG; //
				mega_bullet[0].bullet_damage = 400; // �����ӵ��˺�
			}

			mega_bullet[0].is_active = true; // �����ӵ�
			mega_bullet[0].bullet_grade = my_plane.grade; // �����ӵ��ȼ�Ϊ�ɻ��ȼ�
			mega_bullet[0].generate_time = clock();
			mega_bullet[0].start_pos.x = my_plane.plane_pos.x + PLANE_SIZE / 2; // �����ӵ�λ��Ϊ�ɻ�λ��
			mega_bullet[0].bullet_pos.x = mega_bullet[0].start_pos.x; // �����ӵ�λ��Ϊ��ʼλ��
			mega_bullet[0].start_pos.y = my_plane.plane_pos.y - PLANE_SIZE / 2; // �����ӵ�λ��Ϊ�ɻ�λ��
			mega_bullet[0].bullet_pos.y = mega_bullet[0].start_pos.y; // �����ӵ�λ��Ϊ��ʼλ��
			mega_bullet[0].bullet_speed = 0.7; // �����ӵ��ٶ�
			my_plane.endurance -= 10; // ���ٷɻ��;ö�
			bullet[++my_plane.bullet_num-1].generate_time = clock(); // ��¼�ӵ�����ʱ��
			bullet[my_plane.bullet_num-1] = mega_bullet[0];
			my_plane.last_shoot_time = clock(); // ��¼���һ�����ʱ��
			if (my_plane.bullet_num < BULLET_NUM) { // ����ӵ�����С������ӵ�����
				my_plane.bullet_num++; // �����ӵ�����
			}
			if (my_plane.grade == 5) {
				start_grade = clock(); // ��¼������˫״̬��ʱ��
				my_plane.plane_state = PLANE_STATE_MEGA_NORMAL; // �л�����˫���״̬
			}
			else {
				my_plane.plane_state = PLANE_STATE_NORMAL;
			}
			if(my_plane.grade != 5){
			my_plane.grade = 0; // ���÷ɻ��ȼ�
			my_plane.power = 0; // ���÷ɻ�����
			}
		}
		if (my_plane.plane_state == PLANE_STATE_MEGA_SHOOTING) {
			
			
				for (int i = 0; i <= my_plane.bullet_num; i++) {
					if (!bullet[i].is_active && clock() - my_plane.last_shoot_time > 100) { // ����ӵ�δ�����Ҿ����ϴ����ʱ�䳬��200����
						// �ӵ�������Ч
						if (bullet_sound) {
							DWORD chan = BASS_SampleGetChannel(bullet_sound, FALSE);
							BASS_ChannelPlay(chan, TRUE);
						}

						bullet[i].is_active = true; // �����ӵ�
						bullet[i].bullet_type = BULLET_TYPE_MEGA;
						bullet[i].start_pos.x = my_plane.plane_pos.x + PLANE_SIZE / 2; // �����ӵ�λ��Ϊ�ɻ�λ��
						bullet[i].bullet_pos.x = bullet[i].start_pos.x; // �����ӵ�λ��Ϊ��ʼλ��
						bullet[i].start_pos.y = my_plane.plane_pos.y - PLANE_SIZE / 2; // �����ӵ�λ��Ϊ�ɻ�λ��
						bullet[i].bullet_pos.y = bullet[i].start_pos.y; // �����ӵ�λ��Ϊ��ʼλ��
						bullet[i].bullet_speed = 0.3; // �����ӵ��ٶ�
						bullet[i].bullet_damage = 20; // �����ӵ��˺�
						bullet[i].generate_time = clock(); // ��¼�ӵ�����ʱ��
						my_plane.last_shoot_time = clock(); // ��¼���һ�����ʱ��
						if (my_plane.bullet_num < BULLET_NUM) { // ����ӵ�����С������ӵ�����
							my_plane.bullet_num++; // �����ӵ�����
						}
						break; // �˳�ѭ��
					}
				}
			}
		}
	
	

//�����ӵ�λ��
void bullet_move() {
	
		// �����ӵ�λ��
		for (int i = 0; i < BULLET_NUM; i++) {
			if (bullet[i].is_active) { // ����ӵ�����
				bullet[i].bullet_pos.y = bullet[i].start_pos.y - (clock() - bullet[i].generate_time) * bullet[i].bullet_speed; // �����ӵ�λ��
				if (bullet[i].bullet_pos.y < -150) { // ����ӵ�������Ļ�ϱ߽�
					bullet[i].is_active = false; // �����ӵ�
					if (bullet[i].bullet_type == BULLET_TYPE_BIG) {
						mega_bullet[0].is_active = false; // ���ô��ӵ�
						for(int j = 0;j < ENEMY_MAX_NUM;j++){
							enemy_plane[j].is_hitted_by_mega = false; // ���õл������ӵ����е�״̬
						}
					}
					char teststr[50];
					//sprintf(teststr, "bullet_num: %d", i);
					//MessageBox(NULL, teststr, "��ʾ", MB_OK); // ������ʾ����ʾ�ӵ�����(�ų�bug�ã�
					my_plane.bullet_num--; // �����ӵ�����
				}
			}
		}
	}


//���ɵл�
void generate_enemy() {
	if (enemy_num < ENEMY_MAX_NUM) { // ����л�����С�����л�����
		for (int i = 0; i < ENEMY_MAX_NUM; i++) {
			if (!enemy_plane[i].is_alive) { // ����л�δ����
				enemy_plane[i].is_alive = true; // ����л�
				//�������ɵл�����
				if (rand() % 100 < (level-1)*5) { // �������ɾ�Ӣ�л�
					enemy_plane[i].plane_type = ENEMY_TYPE_ELITE; // ���õл�����ΪBOSS�л�
					enemy_plane[i].maxlife = 200; // ���õл��������ֵ
					enemy_plane[i].life = 200; // ���õл�����ֵ
					enemy_plane[i].size = PLANE_ELITE_SIZE; // ���þ�Ӣ�л���С
					enemy_plane[i].height = 80; // ���þ�Ӣ�л��߶�
				}
				else {
					enemy_plane[i].plane_type = ENEMY_TYPE_NORMAL; // ���õл�����Ϊ��ͨ�л�
					enemy_plane[i].maxlife = 50; // ���õл��������ֵ
					enemy_plane[i].life = 50; // ���õл�����ֵ
					enemy_plane[i].size = PLANE_SIZE; // ������ͨ�л���С
					enemy_plane[i].height = PLANE_SIZE; // ������ͨ�л��߶�
				}
				
				//enemy_plane[i].size = PLANE_SIZE; // ���õл���С
				//enemy_plane[i].height = PLANE_SIZE; // ���õл��߶�
				enemy_plane[i].start_pos.x = rand() % (SCREEN_WIDTH - enemy_plane[i].size)+25; // ������ɵл�λ��
				enemy_plane[i].plane_pos.x = enemy_plane[i].start_pos.x; // ���õл�λ��Ϊ��ʼλ��
				enemy_plane[i].start_pos.y = -enemy_plane[i].height; // ���õл���ʼλ������Ļ�Ϸ�
				enemy_plane[i].plane_pos.y = enemy_plane[i].start_pos.y; // ���õл�λ��Ϊ��ʼλ��
				enemy_plane[i].speed = 0.1; // ���õл��ٶ�
				
				/*enemy_plane[i].plane_type = ENEMY_TYPE_NORMAL;*/ // ���õл�����Ϊ��ͨ�л�
				
				enemy_plane[i].generate_time = clock(); // ��¼�л�����ʱ��

				enemy_num++; // ���ӵл�����
				srand(time(NULL));
				enemy_plane[i].style = rand() % 3;  // 0, 1, 2
				break; // �˳�ѭ��
			}
		}
	}
}
// ���µл�λ��
void update_enemy() {
	for (int i = 0; i < ENEMY_MAX_NUM; i++) {
		if (enemy_plane[i].is_alive) { // ����л�����
			enemy_plane[i].plane_pos.y = enemy_plane[i].start_pos.y + (clock()-enemy_plane[i].generate_time)*enemy_plane[i].speed; // ���µл�λ��
			if (enemy_plane[i].plane_type == ENEMY_TYPE_BOSS && enemy_plane[i].plane_pos.y > 200) {
				enemy_plane[i].plane_pos.y = 200; // �����BOSS�л���������λ������Ļ�Ϸ�200����
			}
			if (enemy_plane[i].plane_pos.y > SCREEN_HEIGHT) { // ����л�������Ļ�±߽�
				enemy_plane[i].is_alive = false; // ���õл�
				enemy_num--; // ���ٵл�����
			}
		}
	}
}

//����л��ӵ�
void enemy_shoot_bullet() {
	for(int j = 0; j < ENEMY_MAX_NUM; j++) {
		if (enemy_plane[j].is_alive && clock() - enemy_plane[j].generate_time > 1000 && clock() - enemy_plane[j].last_shoot_time > 1000) { // ����л������Ҿ�������ʱ�䳬��1000����
			for (int i = 0; i < BULLET_NUM; i++) {
				if (!enemy_bullet[i].is_active) { // ����л��ӵ�δ����
					enemy_bullet[i].is_active = true; // ����л��ӵ�
					enemy_bullet[i].start_pos.x = enemy_plane[j].plane_pos.x + enemy_plane[i].size / 2; // ���õл��ӵ�λ��Ϊ�л�λ��
					enemy_bullet[i].bullet_pos.x = enemy_bullet[i].start_pos.x; // ���õл��ӵ�λ��Ϊ��ʼλ��
					enemy_bullet[i].start_pos.y = enemy_plane[j].plane_pos.y + enemy_plane[i].height / 2; // ���õл��ӵ�λ��Ϊ�л�λ��
					enemy_bullet[i].bullet_pos.y = enemy_bullet[i].start_pos.y; // ���õл��ӵ�λ��Ϊ��ʼλ��
					enemy_bullet[i].bullet_speed = 0.3; // ���õл��ӵ��ٶ�
					// �л��ӵ��˺�,��Ӣ�л��˺�Ϊ3����ͨ�л��˺�Ϊ1
					if (enemy_plane[j].plane_type == ENEMY_TYPE_ELITE) {
						enemy_bullet[i].bullet_damage = 3; // ���õл��ӵ��˺�
						enemy_bullet[i].bullet_type = BULLET_TYPE_TRACKING; // ���õл��ӵ�����Ϊ׷���ӵ�
						enemy_bullet[i].aim_pos.x = my_plane.plane_pos.x; // ����Ŀ��λ��Ϊ��ҷɻ�λ��
						enemy_bullet[i].aim_pos.y = my_plane.plane_pos.y; // ����Ŀ��λ��Ϊ��ҷɻ�λ��
					} else if (enemy_plane[j].plane_type == ENEMY_TYPE_NORMAL) {
						enemy_bullet[i].bullet_damage = 1; // ���õл��ӵ��˺�
						enemy_bullet[i].bullet_type = BULLET_TYPE_NORMAL; // ���õл��ӵ�����Ϊ��ͨ�ӵ�
					}
					enemy_bullet[i].generate_time = clock(); // ��¼�л��ӵ�����ʱ��
					enemy_plane[j].last_shoot_time = clock(); // ��¼���һ�����ʱ��
					enemy_bullet_num++; // ���ӵл��ӵ�����
					break; // �˳�ѭ��
				}
			}
		//enemy_plane[j].generate_time = clock(); // ���µл�����ʱ��
			break; // �˳�ѭ��
		}
	}
}

//���µл��ӵ�λ��
void enemy_bullet_move() {

		// �����ӵ�λ��
		for (int i = 0; i <= ENEMY_MAX_NUM; i++) {
			if (enemy_bullet[i].is_active) { // ����ӵ�����
				//���Ϊ��ͨ�л��ӵ�
				
					enemy_bullet[i].bullet_pos.y = enemy_bullet[i].start_pos.y + (clock() - enemy_bullet[i].generate_time) * enemy_bullet[i].bullet_speed; // �����ӵ�λ��
				
				//���Ϊ��Ӣ�л��ӵ�
				 if (enemy_bullet[i].bullet_type == BULLET_TYPE_TRACKING) {

					 enemy_bullet[i].bullet_pos.x = enemy_bullet[i].start_pos.x +
						 (clock() - enemy_bullet[i].generate_time) * enemy_bullet[i].bullet_speed * ((enemy_bullet[i].start_pos.x - enemy_bullet[i].aim_pos.x) / (enemy_bullet[i].start_pos.y - enemy_bullet[i].aim_pos.y)); // �����ӵ�λ��
					
				}
				if (enemy_bullet[i].bullet_pos.y > SCREEN_HEIGHT) { // ����ӵ�������Ļ�±߽�
						enemy_bullet[i].is_active = false; // �����ӵ�
						enemy_bullet_num--; // ���ٵл��ӵ�����
					}

			}
		}
}

//�л��ӵ�����ҷɻ���ײ
void check_enemy_bullet_collision() {
	for (int i = 0; i < BULLET_NUM; i++) {
		if (enemy_bullet[i].is_active) { // ����л��ӵ�����
			// ���л��ӵ�����ҷɻ�����ײ
			if (abs(enemy_bullet[i].bullet_pos.x - my_plane.plane_pos.x) < my_plane.size /2 &&
				abs(enemy_bullet[i].bullet_pos.y - my_plane.plane_pos.y) < my_plane.height /2) {
				// �ӵ�������Ч
				if (bullet_hit_sound) {
					DWORD chan = BASS_SampleGetChannel(bullet_hit_sound, FALSE);
					BASS_ChannelPlay(chan, TRUE);
				}
				my_plane.life -= enemy_bullet[i].bullet_damage; // ��ҷɻ��ܵ��˺�
				enemy_bullet[i].is_active = false; // ���õл��ӵ�
				enemy_bullet_num--; // ���ٵл��ӵ�����
				if (my_plane.life <= 0) { // �����ҷɻ�����ֵС�ڵ���0
					my_plane.is_alive = false; // ��ҷɻ�����
					break; // �˳�ѭ��
				}
			}
		}
	}
}

//�л�����ҷɻ���ײ���
void check_collision() {
	for (int i = 0; i < ENEMY_MAX_NUM; i++) {
		if (enemy_plane[i].is_alive) { // ����л�����
			// ���л�����ҷɻ�����ײ
			if (enemy_plane[i].plane_type != ENEMY_TYPE_BOSS && // �������BOSS�л�
				abs(enemy_plane[i].plane_pos.x - my_plane.plane_pos.x) < enemy_plane[i].size/2 &&
				abs(enemy_plane[i].plane_pos.y - my_plane.plane_pos.y) < enemy_plane[i].height/2) {
				// �л���������Ч
				if (enemy_down_sound) {
					DWORD chan = BASS_SampleGetChannel(enemy_down_sound, FALSE);
					BASS_ChannelPlay(chan, TRUE);
				}
				//���Ϊ��Ӣ�л���30���˺�����ͨ�л���10���˺�
				if (enemy_plane[i].plane_type == ENEMY_TYPE_ELITE) {
					my_plane.life -= 30; // ��ҷɻ��ܵ��˺�
				} else if (enemy_plane[i].plane_type == ENEMY_TYPE_NORMAL) {
					my_plane.life -= 10; // ��ҷɻ��ܵ��˺�
				}
				//my_plane.life -= 10; // ��ҷɻ��ܵ��˺�
				enemy_plane[i].is_alive = false; // ���õл�
				enemy_num--; // ���ٵл�����
				if (my_plane.life <= 0) { // �����ҷɻ�����ֵС�ڵ���0
					my_plane.is_alive = false; // ��ҷɻ�����
					break; // �˳�ѭ��
				}
			}
		}
	}
}

//����ӵ���л���ײ���
void check_bullet_collision() {
	for (int i = 0; i < BULLET_NUM; i++) {
		if (bullet[i].is_active) { // ����ӵ�����
			for (int j = 0; j < ENEMY_MAX_NUM; j++) {
				if (enemy_plane[j].is_alive && !enemy_plane[j].is_hitted_by_mega) { // ����л�����
					// ����ӵ���л�����ײ
					if (enemy_plane[j].plane_type == ENEMY_TYPE_BOSS) {// �����BOSS�л�
						if (abs(bullet[i].bullet_pos.x - enemy_plane[j].plane_pos.x) < enemy_plane[j].size / 2 &&
							abs(bullet[i].bullet_pos.y - enemy_plane[j].plane_pos.y) < enemy_plane[j].height / 2) {
							enemy_plane[j].life -= bullet[i].bullet_damage; // �л��ܵ��˺�
							if (enemy_plane[i].life > 0 || bullet[i].bullet_type == BULLET_TYPE_BIG) {
								// �ӵ�������Ч
								if (bullet[i].bullet_grade > 2 && bullet[i].bullet_type == BULLET_TYPE_BIG) {
									if (mega_bullet_hit_sound) {
										DWORD chan = BASS_SampleGetChannel(mega_bullet_hit_sound, FALSE);
										BASS_ChannelPlay(chan, TRUE);
									}
								}
								else if (enemy_plane[j].life > 0) {
									if (bullet_hit_sound) {
										DWORD chan = BASS_SampleGetChannel(bullet_hit_sound, FALSE);
										BASS_ChannelPlay(chan, TRUE);
									}
								}
							}
							if (bullet[i].bullet_type == BULLET_TYPE_BIG && bullet[i].bullet_grade > 2 ) {
								enemy_plane[j].is_hitted_by_mega = true; // ���õл����ػ��ӵ�����״̬Ϊtrue
							}
							else {
								bullet[i].is_active = false; // �����ӵ�
								my_plane.bullet_num--; // �����ӵ�����
								if (bullet[i].bullet_type == BULLET_TYPE_BIG) {
									mega_bullet[0].is_active = false; // ���ô��ӵ�
								}
							}
							
							if (enemy_plane[j].life <= 0) { // ����л�����ֵС�ڵ���0
								// �л���������Ч
								if (enemy_down_sound) {
									DWORD chan = BASS_SampleGetChannel(boss_down_sound, FALSE);
									BASS_ChannelPlay(chan, TRUE);
								}
								enemy_plane[j].is_alive = false; // ���õл�
								enemy_num--; // ���ٵл�����
								score += enemy_plane[j].maxlife;// ���ӷ���
								last_complete_time = clock(); // �����ϴ�ͨ��ʱ��
								boss_is_alive = false; // BOSS����״̬����Ϊfalse
								if(level < 5)level++; // �ؿ�������
								if (drop_item_num < ITEM_NUM - 1)generate_drop_item(ENEMY_TYPE_BOSS, enemy_plane[j].plane_pos); // ����BOSS������Ʒ
							}
							if(bullet[i].bullet_type == BULLET_TYPE_NORMAL)my_plane.power += 10; // ���ӷɻ�����
							break; // �˳�ѭ��
						}
					}
					else {// �������ͨ�л���Ӣ�л�
						if (abs(bullet[i].bullet_pos.x - enemy_plane[j].plane_pos.x) < enemy_plane[j].size &&
							abs(bullet[i].bullet_pos.y - enemy_plane[j].plane_pos.y) < enemy_plane[j].height){
							enemy_plane[j].life -= bullet[i].bullet_damage; // �л��ܵ��˺�
							if (enemy_plane[i].life > 0 || bullet[i].bullet_type == BULLET_TYPE_BIG) {
								// �ӵ�������Ч
								if (bullet[i].bullet_grade > 2 && bullet[i].bullet_type == BULLET_TYPE_BIG)  {
									if (mega_bullet_hit_sound) {
										DWORD chan = BASS_SampleGetChannel(mega_bullet_hit_sound, FALSE);
										BASS_ChannelPlay(chan, TRUE);
									}
								}
								else if(enemy_plane[j].life > 0) {
									if (bullet_hit_sound) {
										DWORD chan = BASS_SampleGetChannel(bullet_hit_sound, FALSE);
										BASS_ChannelPlay(chan, TRUE);
									}
								}
							}
							if (bullet[i].bullet_type == BULLET_TYPE_BIG && bullet[i].bullet_grade > 2 ) {
								enemy_plane[j].is_hitted_by_mega = true; // ���õл����ػ��ӵ�����״̬Ϊtrue
							}
							else {
								bullet[i].is_active = false; // �����ӵ�
								my_plane.bullet_num--; // �����ӵ�����
								if (bullet[i].bullet_type == BULLET_TYPE_BIG) {
									mega_bullet[0].is_active = false; // ���ô��ӵ�
								}
							}
							
							if (enemy_plane[j].life <= 0) { // ����л�����ֵС�ڵ���0
								// �л���������Ч
								if (enemy_down_sound) {
									DWORD chan = BASS_SampleGetChannel(enemy_down_sound, FALSE);
									BASS_ChannelPlay(chan, TRUE);
								}
								enemy_plane[j].is_alive = false; // ���õл�
								if (drop_item_num < ITEM_NUM)generate_drop_item(enemy_plane[j].plane_type, enemy_plane[j].plane_pos); // ���ɵл�������Ʒ
								enemy_num--; // ���ٵл�����
								score += enemy_plane[j].maxlife;// ���ӷ���
							}
							if(bullet[i].bullet_type == BULLET_TYPE_NORMAL)  my_plane.power += 10; // ���ӷɻ�����
							break; // �˳�ѭ��
							}

					}
				}
			}
		}
	}
}

//��Ϸ��ʼ90�������BOSS
void generate_boss() {
	if (clock() - last_complete_time > 90000 && !boss_is_alive) { // �����Ϸ��ʼ����90����BOSSδ����
		for (int i = 0; i < ENEMY_MAX_NUM; i++) {
			if (!enemy_plane[i].is_alive) { // ����л�δ����
				enemy_plane[i].is_alive = true; // ����л�
				enemy_plane[i].size = BOSS_SIZE; // ����BOSS��С
				enemy_plane[i].height = BOSS_HEIGHT;// ����BOSS�߶�
				enemy_plane[i].start_pos.x = SCREEN_WIDTH / 2 /*- enemy_plane[i].size / 2*/; // ����BOSSλ��Ϊ��Ļ����
				enemy_plane[i].plane_pos.x = enemy_plane[i].start_pos.x; // ����BOSSλ��Ϊ��ʼλ��
				enemy_plane[i].start_pos.y = -enemy_plane[i].height; // ����BOSS��ʼλ������Ļ�Ϸ�
				enemy_plane[i].plane_pos.y = enemy_plane[i].start_pos.y; // ����BOSSλ��Ϊ��ʼλ��
				enemy_plane[i].speed = 0.03; // ����BOSS�ٶ�
				enemy_plane[i].plane_type = ENEMY_TYPE_BOSS; // ����BOSS����ΪBOSS�л�
				enemy_plane[i].maxlife = BOSS_LIFE + level * 500; // ����BOSS�������ֵ
				enemy_plane[i].life = BOSS_LIFE + level * 500; // ����BOSS����ֵ
				enemy_plane[i].generate_time = clock(); // ��¼BOSS����ʱ��
				boss_is_alive = true; // BOSS����״̬����Ϊtrue
				srand(time(NULL));
				if (level <= 3) {
					enemy_plane[i].style = 0;
				} else {
					
					enemy_plane[i].style = 1;  
						
				}
				break; // �˳�ѭ��
			}
		}
	}
}

//����������״̬
void check_player_life() {
	if (my_plane.life <= 0) { // �����ҷɻ�����ֵС�ڵ���0
		my_plane.is_alive = false; // ��ҷɻ�����
		PlaySound("src/sound/game_over.wav", NULL, SND_FILENAME | SND_ASYNC | SND_NOWAIT); // ������Ϸ������Ч
		MessageBox(NULL, "Game Over!", "��ʾ", MB_OK); // ������Ϸ������ʾ��
		exit(0); // �˳���Ϸ
	}
}
//�;õļӼ�������״̬ÿ��ָ�15�;�
void add_endurance() {
	
	if ((my_plane.plane_state == PLANE_STATE_NORMAL || my_plane.plane_state == PLANE_STATE_MEGA_NORMAL || my_plane.plane_state == PLANE_STATE_MEGA_SHOOTING) && clock()-last_added_time > 200 && clock()-my_plane.last_shoot_time > 300) { // ����ɻ�״̬Ϊ����
		
		my_plane.endurance += 3; // ÿ��ָ�15�;�
		last_added_time = clock(); // �����ϴ�����;õ�ʱ��
		if (my_plane.endurance > 100) { // ����;öȳ���100
			my_plane.endurance = 100; // ���;ö�����Ϊ100
		}
	}
}


//���ɻ��;ã�����ʱ��ֹ���
void check_player_endurance() {
	if (my_plane.endurance <= 0) { // �����ҷɻ��;ö�С�ڵ���0
		my_plane.endurance = 0; // ���;ö�����Ϊ0
		my_plane.plane_state = my_plane.plane_state == PLANE_STATE_CHARGING ? PLANE_STATE_CHARGED : PLANE_STATE_NORMAL ; // �л�������״̬����Ϊ����״̬���л����������״̬
		
	}
}

//���ɻ���ֵ����������ϵ
void check_player_power() {
	if (my_plane.power >= GRADE1_SCORE && my_plane.grade == 0) { // ����ɻ����ƴ��ڵ���100
		//������Ч
		if (grade1_sound) {
			DWORD chan = BASS_SampleGetChannel(grade1_sound, FALSE);
			BASS_ChannelPlay(chan, TRUE);
		}
		my_plane.power -= 100; // ��������
		my_plane.grade++; // �������Ƶȼ�
	}

	if (my_plane.power >= GRADE2_SCORE && my_plane.grade == 1) { // ����ɻ����ƴ��ڵ���110
		//������Ч
		if (grade2_sound) {
			DWORD chan = BASS_SampleGetChannel(grade2_sound, FALSE);
			BASS_ChannelPlay(chan, TRUE);
		}
		my_plane.power -= 110; // ��������
		my_plane.grade++; // �������Ƶȼ�
	}

	if (my_plane.power >= GRADE3_SCORE && my_plane.grade == 2) { // ����ɻ����ƴ��ڵ���120
		//������Ч
		if (grade3_sound) {
			DWORD chan = BASS_SampleGetChannel(grade3_sound, FALSE);
			BASS_ChannelPlay(chan, TRUE);
		}
		my_plane.power -= 120; // ��������
		my_plane.grade++; // �������Ƶȼ�
	}

	if (my_plane.power >= GRADE4_SCORE && my_plane.grade == 3) { // ����ɻ����ƴ��ڵ���150
		//������Ч
		if (grade4_sound) {
			DWORD chan = BASS_SampleGetChannel(grade4_sound, FALSE);
			BASS_ChannelPlay(chan, TRUE);
		}
		my_plane.power -= 150; // ��������
		my_plane.grade++; // �������Ƶȼ�
	}

	if (my_plane.power >= GRADE5_SCORE && my_plane.grade == 4) { // ����ɻ����ƴ��ڵ���400
		//������Ч
		if (grade5_sound) {
			DWORD chan = BASS_SampleGetChannel(grade5_sound, FALSE);
			BASS_ChannelPlay(chan, TRUE);
		}
		my_plane.power = 400; // ��������
		my_plane.grade++; // �������Ƶȼ�
		last_power_time = clock(); // ��¼�������ϴμ������Ƶ�ʱ��
	}

	if (my_plane.grade >= 5) { // ������Ƶȼ�����5
		my_plane.grade = 5; // �����Ƶȼ�����Ϊ5
		my_plane.power = 400;// ����������Ϊ400
	}
}

//���ɻ����Ƶȼ����ڵ���3ʱ������ÿ�����5�㣬������С��0
void diminish_player_power() {
	if (my_plane.grade >= 3 && clock() - last_power_time > 200) { // ����ɻ����Ƶȼ�����3�Ҿ����ϴμ�������ʱ�䳬��1��
		if (my_plane.power > 0) {
			my_plane.power -= 1; // ÿ�����5������
		}
		last_power_time = clock(); // �����ϴμ������Ƶ�ʱ��
	}
	if ((my_plane.plane_state == PLANE_STATE_MEGA_NORMAL || my_plane.plane_state == PLANE_STATE_MEGA_SHOOTING) && clock() - last_power_time > 100) {
			my_plane.power -= 1; // ÿ�����10������
			if (my_plane.power <= 0) {
				my_plane.grade = 0;
				if (my_plane.plane_state == PLANE_STATE_MEGA_NORMAL) my_plane.plane_state = PLANE_STATE_NORMAL;
				else my_plane.plane_state = PLANE_STATE_SHOOTING;
			}
			last_power_time = clock(); // �����ϴμ������Ƶ�ʱ��
	}
}

//���л�����ʱ�������ռ��λ��Ϊ�л�λ��
void generate_drop_item(int plane_type, POS plane_pos) {
	int i = rand();
	switch (plane_type) {
	case ENEMY_TYPE_NORMAL: // ��ͨ�л�
		if (i % 1000 < 3) { // 0.3%�ĸ��ʵ�����Ʒ
			drop_item[drop_item_num].is_active = true; // ���������
			drop_item[drop_item_num].item_type = ITEM_TYPE_SUPPLY; // ���õ���������Ϊ�󲹸���
			drop_item[drop_item_num].start_pos.x = plane_pos.x; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].start_pos.y = plane_pos.y; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].item_pos.x = plane_pos.x; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].item_pos.y = plane_pos.y; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].generate_time = clock(); // ���õ�������ʼʱ��
			drop_item[drop_item_num].item_speed = 0.3; // ���õ������ٶ�
			drop_item_num++; // ���ӵ���������
			break; // �˳�ѭ��
		}
		if (i % 1000 < 5) { // 0.5%�ĸ��ʵ�����Ʒ
			drop_item[drop_item_num].is_active = true; // ���������
			drop_item[drop_item_num].item_type = ITEM_TYPE_BIG_LIFE; // ���õ���������Ϊ��������
			drop_item[drop_item_num].start_pos.x = plane_pos.x; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].start_pos.y = plane_pos.y; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].item_pos.x = plane_pos.x; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].item_pos.y = plane_pos.y; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].generate_time = clock(); // ���õ�������ʼʱ��
			drop_item[drop_item_num].item_speed = 0.3; // ���õ������ٶ�
			drop_item_num++; // ���ӵ���������
			break; // �˳�ѭ��
		}
		if (i % 1000 < 30) { // 3%�ĸ��ʵ�����Ʒ
			drop_item[drop_item_num].is_active = true; // ���������
			drop_item[drop_item_num].item_type = ITEM_TYPE_SUPPLY; // ���õ���������ΪС������
			drop_item[drop_item_num].start_pos.x = plane_pos.x; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].start_pos.y = plane_pos.y; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].item_pos.x = plane_pos.x; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].item_pos.y = plane_pos.y; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].generate_time = clock(); // ���õ�������ʼʱ��
			drop_item[drop_item_num].item_speed = 0.3; // ���õ������ٶ�
			drop_item_num++; // ���ӵ���������
			break; // �˳�ѭ��
		}
		if (i % 1000 < 50) { // 5%�ĸ��ʵ�����Ʒ
			drop_item[drop_item_num].is_active = true; // ���������
			drop_item[drop_item_num].item_type = ITEM_TYPE_SMALL_LIFE; // ���õ���������ΪС������
			drop_item[drop_item_num].start_pos.x = plane_pos.x; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].start_pos.y = plane_pos.y; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].item_pos.x = plane_pos.x; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].item_pos.y = plane_pos.y; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].generate_time = clock(); // ���õ�������ʼʱ��
			drop_item[drop_item_num].item_speed = 0.3; // ���õ������ٶ�
			drop_item_num++; // ���ӵ���������
			break; // �˳�ѭ��
		}
		
		
		
		break;
	case ENEMY_TYPE_ELITE: // ��Ӣ�л�
		if (i % 1000 < 15) { // 1.5%�ĸ��ʵ�����Ʒ
			drop_item[drop_item_num].is_active = true; // ���������
			drop_item[drop_item_num].item_type = ITEM_TYPE_SUPPLY; // ���õ���������Ϊ�󲹸���
			drop_item[drop_item_num].start_pos.x = plane_pos.x; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].start_pos.y = plane_pos.y; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].item_pos.x = plane_pos.x; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].item_pos.y = plane_pos.y; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].generate_time = clock(); // ���õ�������ʼʱ��
			drop_item[drop_item_num].item_speed = 0.3; // ���õ������ٶ�
			drop_item_num++; // ���ӵ���������
			break; // �˳�ѭ��
		}
		if (i % 1000 < 20) { // 2%�ĸ��ʵ�����Ʒ
			drop_item[drop_item_num].is_active = true; // ���������
			drop_item[drop_item_num].item_type = ITEM_TYPE_BIG_LIFE; // ���õ���������Ϊ��������
			drop_item[drop_item_num].start_pos.x = plane_pos.x; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].start_pos.y = plane_pos.y; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].item_pos.x = plane_pos.x; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].item_pos.y = plane_pos.y; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].generate_time = clock(); // ���õ�������ʼʱ��
			drop_item[drop_item_num].item_speed = 0.3; // ���õ������ٶ�
			drop_item_num++; // ���ӵ���������
			break; // �˳�ѭ��

		if (i % 1000 < 150) { // 15%�ĸ��ʵ�����Ʒ
			drop_item[drop_item_num].is_active = true; // ���������
			drop_item[drop_item_num].item_type = ITEM_TYPE_SUPPLY; // ���õ���������ΪС������
			drop_item[drop_item_num].start_pos.x = plane_pos.x; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].start_pos.y = plane_pos.y; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].item_pos.x = plane_pos.x; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].item_pos.y = plane_pos.y; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].generate_time = clock(); // ���õ�������ʼʱ��
			drop_item[drop_item_num].item_speed = 0.3; // ���õ������ٶ�
			drop_item_num++; // ���ӵ���������
			break; // �˳�ѭ��
		}

			if (i % 1000 < 200) { // 20%�ĸ��ʵ�����Ʒ
			drop_item[drop_item_num].is_active = true; // ���������
			drop_item[drop_item_num].item_type = ITEM_TYPE_SMALL_LIFE; // ���õ���������ΪС������
			drop_item[drop_item_num].start_pos.x = plane_pos.x; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].start_pos.y = plane_pos.y; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].item_pos.x = plane_pos.x; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].item_pos.y = plane_pos.y; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].generate_time = clock(); // ���õ�������ʼʱ��
			drop_item[drop_item_num].item_speed = 0.3; // ���õ������ٶ�
			drop_item_num++; // ���ӵ���������
			break; // �˳�ѭ��
		}
		
		}

		
		break;
	case ENEMY_TYPE_BOSS: // BOSS�л�

		//BOSS�ص���������
			drop_item[drop_item_num].is_active = true; // ���������
			drop_item[drop_item_num].item_type = ITEM_TYPE_BIG_LIFE; // ���õ���������Ϊ��������
			drop_item[drop_item_num].start_pos.x = plane_pos.x; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].start_pos.y = plane_pos.y; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].item_pos.x = plane_pos.x; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].item_pos.y = plane_pos.y; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].generate_time = clock(); // ���õ�������ʼʱ��
			drop_item[drop_item_num].item_speed = 0.3; // ���õ������ٶ�
			drop_item_num++; // ���ӵ���������
		if (i % 100 < 5) { // 5%�ĸ��ʵ�����Ʒ
			drop_item[++drop_item_num].is_active = true; // ���������
			drop_item[drop_item_num].item_type = ITEM_TYPE_SUPPLY; // ���õ���������Ϊ�󲹸���
			drop_item[drop_item_num].start_pos.x = plane_pos.x; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].start_pos.y = plane_pos.y; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].item_pos.x = plane_pos.x; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].item_pos.y = plane_pos.y; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].generate_time = clock(); // ���õ�������ʼʱ��
			drop_item[drop_item_num].item_speed = 0.3; // ���õ������ٶ�
			break; // �˳�ѭ��

		if (i % 100 < 50) { // 50%�ĸ��ʵ�����Ʒ
			drop_item[++drop_item_num].is_active = true; // ���������
			drop_item[drop_item_num].item_type = ITEM_TYPE_SUPPLY; // ���õ���������ΪС������
			drop_item[drop_item_num].start_pos.x = plane_pos.x; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].start_pos.y = plane_pos.y; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].item_pos.x = plane_pos.x; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].item_pos.y = plane_pos.y; // ���õ�����λ��Ϊ�л�λ��
			drop_item[drop_item_num].generate_time = clock(); // ���õ�������ʼʱ��
			drop_item[drop_item_num].item_speed = 0.3; // ���õ������ٶ�
			//drop_item_num++; // ���ӵ���������
			break; // �˳�ѭ��
		}
		

		}
		break;

	}
}


//���µ�����λ��
void update_drop_item() {
	for (int i = 0; i < ITEM_NUM; i++) {
		if (drop_item[i].is_active) { // ��������Ｄ��
			drop_item[i].item_pos.y = drop_item[i].start_pos.y + (clock() - drop_item[i].generate_time) * 0.1; // ���µ�����λ��
			if (drop_item[i].item_pos.y > SCREEN_HEIGHT) { // ��������ﳬ����Ļ�±߽�
				drop_item[i].is_active = false; // ���õ�����
				drop_item_num--; // ���ٵ���������
			}
		}
	}
}

//������������ײ���
void check_player_drop_item_collision() {
	for (int i = 0; i < ITEM_NUM; i++) {
		if (drop_item[i].is_active) { // ��������Ｄ��
			// ������������ҷɻ�����ײ
			if (abs(drop_item[i].item_pos.x - my_plane.plane_pos.x) < PLANE_SIZE * 2 &&
				abs(drop_item[i].item_pos.y - my_plane.plane_pos.y) < PLANE_SIZE * 2) {
				switch (drop_item[i].item_type) { // ���ݵ���������ִ�в�ͬ����
				case ITEM_TYPE_SMALL_LIFE: // С������
					my_plane.life += 30; // ��ҷɻ�����ֵ����1
					if (my_plane.life > 100) my_plane.life = 100; // ����ֵ������100
					drop_item[i].is_active = false; // ���õ�����
					break;
				case ITEM_TYPE_BIG_LIFE: // ��������
					my_plane.life = 100; // ��ҷɻ�����ֵ����5
					my_plane.endurance = 100; // ��ҷɻ��;ö�����20
					drop_item[i].is_active = false; // ���õ�����
					break;
				case ITEM_TYPE_SUPPLY: // С������
					my_plane.power += 100; // ��ҷɻ���������30
					drop_item[i].is_active = false; // ���õ�����
					break;
				case ITEM_TYPE_BIG_SUPPLY: // �󲹸���
					my_plane.power += 480; // ��ҷɻ���������480
					drop_item[i].is_active = false; // ���õ�����

				}
				drop_item[i].is_active = false; // ���õ�����
				drop_item_num--; // ���ٵ���������
			}
		}
	}
}

//��������
void play_music() {
	if (bgm1) { // ����������ִ���
		BGM = BASS_SampleGetChannel(bgm1, FALSE); // ��ȡ��������ͨ��
		//if (!BASS_ChannelIsActive(BGM)) { // �����������δ�ڲ���
			
			// ������������������Ϊ50%
			BASS_ChannelSetAttribute(BGM, BASS_ATTRIB_VOL, 0.5f);
			BASS_ChannelPlay(BGM, TRUE); // ���ű�������
		//}
	}
}

// ������Ϸ״̬����
void UpdateGame() {

	control_plane(); // ���ÿ��Ʒɻ�����������ɻ��ƶ������״̬
	check_plane_state();

	shoot_bullet(); // ���÷����ӵ������������ӵ�����
	
	bullet_move(); // ���ø����ӵ�λ�ú����������ӵ��ƶ�

	if(clock() - last_generate_enemy_time > (6000/level)) { // ������ϴ�����ʱ�䳬����6/�ؿ�������
		generate_enemy(); // �������ɵл�����������л�����
		last_generate_enemy_time = clock(); // �������ɵл�ʱ��
	}

	update_enemy(); // ���ø��µл�λ�ú���������л��ƶ�
	enemy_shoot_bullet(); // ���÷���л��ӵ�����������л��ӵ�����
	enemy_bullet_move(); // ���ø��µл��ӵ�λ�ú���������л��ӵ��ƶ�
	check_enemy_bullet_collision(); // ���õл��ӵ�����ҷɻ���ײ��⺯��������л��ӵ�����ҷɻ�����ײ
	check_collision(); // ������ײ��⺯��������л�����ҷɻ�����ײ
	check_bullet_collision(); // ������ײ��⺯������������ӵ���л�����ײ
	check_player_life(); // ���ü���������״̬������������ҷɻ�������״̬
	check_player_endurance(); // ���ü��ɻ��;ú���������ɻ��;�״̬
	check_player_power();// ���ü��ɻ����ƺ���������ɻ�����״̬
	diminish_player_power(); // ���ü��ɻ����ƺ���������ɻ�����״̬
	add_endurance(); // ��������;ú���������ɻ��;�״̬

	generate_boss(); // ��������BOSS����������BOSS����

	update_drop_item(); // ���ø��µ�����λ�ú��������������λ�ø���
	check_player_drop_item_collision(); // ����������������ײ��⺯����������ҷɻ�����������ײ

	play_music(); // ���ò������ֺ��������������ֲ���
}
