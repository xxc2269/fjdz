#pragma once//���ڷ�ֹͷ�ļ�����ΰ���
#include"defines.h"//�����궨��ͷ�ļ�(�Ѱ����˱�׼ͷ�ļ�)

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
		break;
	case WM_LBUTTONUP:
		// �������ɿ��¼�
		if (my_plane.plane_state == PLANE_STATE_SHOOTING) { // ����ɻ�״̬Ϊ���
			my_plane.plane_state = PLANE_STATE_NORMAL; // �л�������״̬
		}
		break;
	}
}

//�����ӵ�
void shoot_bullet() {
	if (my_plane.plane_state == PLANE_STATE_SHOOTING && my_plane.endurance > 0) {
		for (int i = 0; i <= my_plane.bullet_num; i++) {
			if (!bullet[i].is_active && clock() - my_plane.last_shoot_time > 200) { // ����ӵ�δ�����Ҿ����ϴ����ʱ�䳬��200����
				// �ӵ�������Ч
				if (bullet_sound) {
					DWORD chan = BASS_SampleGetChannel(bullet_sound, FALSE);
					BASS_ChannelPlay(chan, TRUE);
				}
				bullet[i].is_active = true; // �����ӵ�
				bullet[i].start_pos.x = my_plane.plane_pos.x + PLANE_SIZE / 2; // �����ӵ�λ��Ϊ�ɻ�λ��
				bullet[i].bullet_pos.x = bullet[i].start_pos.x; // �����ӵ�λ��Ϊ��ʼλ��
				bullet[i].start_pos.y = my_plane.plane_pos.y - PLANE_SIZE / 2; // �����ӵ�λ��Ϊ�ɻ�λ��
				bullet[i].bullet_pos.y = bullet[i].start_pos.y; // �����ӵ�λ��Ϊ��ʼλ��
				bullet[i].bullet_speed = 0.3; // �����ӵ��ٶ�
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
}

//�����ӵ�λ��
void bullet_move() {
	
		// �����ӵ�λ��
		for (int i = 0; i < BULLET_NUM; i++) {
			if (bullet[i].is_active) { // ����ӵ�����
				bullet[i].bullet_pos.y = bullet[i].start_pos.y - (clock() - bullet[i].generate_time) * bullet[i].bullet_speed; // �����ӵ�λ��
				if (bullet[i].bullet_pos.y < 0) { // ����ӵ�������Ļ�ϱ߽�
					bullet[i].is_active = false; // �����ӵ�
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
				enemy_plane[i].size = PLANE_SIZE; // ���õл���С
				enemy_plane[i].height = PLANE_SIZE; // ���õл��߶�
				enemy_plane[i].start_pos.x = rand() % (SCREEN_WIDTH - enemy_plane[i].size)+25; // ������ɵл�λ��
				enemy_plane[i].plane_pos.x = enemy_plane[i].start_pos.x; // ���õл�λ��Ϊ��ʼλ��
				enemy_plane[i].start_pos.y = -enemy_plane[i].height; // ���õл���ʼλ������Ļ�Ϸ�
				enemy_plane[i].plane_pos.y = enemy_plane[i].start_pos.y; // ���õл�λ��Ϊ��ʼλ��
				enemy_plane[i].speed = 0.1; // ���õл��ٶ�
				enemy_plane[i].plane_type = ENEMY_TYPE_NORMAL; // ���õл�����Ϊ��ͨ�л�
				enemy_plane[i].maxlife = 50; // ���õл��������ֵ
				enemy_plane[i].life = 50; // ���õл�����ֵ
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
				enemy_bullet[i].bullet_pos.y = enemy_bullet[i].start_pos.y + (clock() - enemy_bullet[i].generate_time) * enemy_bullet[i].bullet_speed; // �����ӵ�λ��
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
				my_plane.life -= 1; // ��ҷɻ��ܵ��˺�
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
				my_plane.life -= 10; // ��ҷɻ��ܵ��˺�
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
				if (enemy_plane[j].is_alive) { // ����л�����
					// ����ӵ���л�����ײ
					if (enemy_plane[j].plane_type == ENEMY_TYPE_BOSS) {// �����BOSS�л�
						if (abs(bullet[i].bullet_pos.x - enemy_plane[j].plane_pos.x) < enemy_plane[j].size / 2 &&
							abs(bullet[i].bullet_pos.y - enemy_plane[j].plane_pos.y) < enemy_plane[j].height / 2) {
							enemy_plane[j].life -= bullet[i].bullet_damage; // �л��ܵ��˺�
							if (enemy_plane[i].life > 0) {
								// �ӵ�������Ч
								if (bullet_hit_sound) {
									DWORD chan = BASS_SampleGetChannel(bullet_hit_sound, FALSE);
									BASS_ChannelPlay(chan, TRUE);
								}
							}
							bullet[i].is_active = false; // �����ӵ�
							my_plane.bullet_num--; // �����ӵ�����
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
							}
							break; // �˳�ѭ��
						}
					}
					else {// �������ͨ�л���Ӣ�л�
						if (abs(bullet[i].bullet_pos.x - enemy_plane[j].plane_pos.x) < enemy_plane[j].size &&
							abs(bullet[i].bullet_pos.y - enemy_plane[j].plane_pos.y) < enemy_plane[j].height){
							enemy_plane[j].life -= bullet[i].bullet_damage; // �л��ܵ��˺�
							if (enemy_plane[i].life > 0) {
								// �ӵ�������Ч
								if (bullet_hit_sound) {
									DWORD chan = BASS_SampleGetChannel(bullet_hit_sound, FALSE);
									BASS_ChannelPlay(chan, TRUE);
								}
							}
							bullet[i].is_active = false; // �����ӵ�
							my_plane.bullet_num--; // �����ӵ�����
							if (enemy_plane[j].life <= 0) { // ����л�����ֵС�ڵ���0
								// �л���������Ч
								if (enemy_down_sound) {
									DWORD chan = BASS_SampleGetChannel(enemy_down_sound, FALSE);
									BASS_ChannelPlay(chan, TRUE);
								}
								enemy_plane[j].is_alive = false; // ���õл�
								enemy_num--; // ���ٵл�����
								score += enemy_plane[j].maxlife;// ���ӷ���
							}
							break; // �˳�ѭ��
							}

					}
				}
			}
		}
	}
}

//��Ϸ��ʼ2���Ӻ�����BOSS
void generate_boss() {
	if (clock() - last_complete_time > 90000 && !boss_is_alive) { // �����Ϸ��ʼ����2������BOSSδ����
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
				enemy_plane[i].maxlife = BOSS_LIFE; // ����BOSS�������ֵ
				enemy_plane[i].life = BOSS_LIFE; // ����BOSS����ֵ
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
	
	if (my_plane.plane_state == PLANE_STATE_NORMAL && clock()-last_added_time > 200 && clock()-my_plane.last_shoot_time > 300) { // ����ɻ�״̬Ϊ����
		
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
		my_plane.plane_state = PLANE_STATE_NORMAL; // �л�������״̬
		
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

	shoot_bullet(); // ���÷����ӵ������������ӵ�����
	
	bullet_move(); // ���ø����ӵ�λ�ú����������ӵ��ƶ�

	if(clock() - last_generate_enemy_time > (5000/level)) { // ������ϴ�����ʱ�䳬����5/�ؿ�������
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


	check_player_endurance(); // ���ü��ɻ��;ú���������ɻ��;�״̬
	add_endurance(); // ��������;ú���������ɻ��;�״̬

	generate_boss(); // ��������BOSS����������BOSS����


	play_music(); // ���ò������ֺ��������������ֲ���
}
