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
	if (my_plane.plane_state == PLANE_STATE_SHOOTING) {
		for (int i = 0; i <= my_plane.bullet_num; i++) {
			if (!bullet[i].is_active && clock() - last_shoot_time > 200) { // ����ӵ�δ�����Ҿ����ϴ����ʱ�䳬��200����
				PlaySound("src/sound/bullet.wav", NULL, SND_FILENAME | SND_ASYNC | SND_NOWAIT); // �����ӵ�������Ч��SND_FILENAME��ʾ�ļ�����SND_ASYNC��ʾ�첽���ţ���ֹ����,SND_NOWAIT��ʾ���ȴ���Ч�������
				bullet[i].is_active = true; // �����ӵ�
				bullet[i].bullet_pos.x = my_plane.plane_pos.x + PLANE_SIZE / 2; // �����ӵ�λ��Ϊ�ɻ�λ��
				bullet[i].bullet_pos.y = my_plane.plane_pos.y - PLANE_SIZE / 2; // �����ӵ�λ��Ϊ�ɻ�λ��
				bullet[i].bullet_speed = 1.0; // �����ӵ��ٶ�
				my_plane.endurance -= 1; // ���ٷɻ��;ö�
				last_shoot_time = clock(); // ��¼���һ�����ʱ��
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
	for (int i = 0; i <= BULLET_NUM; i++) {
		if (bullet[i].is_active) { // ����ӵ�����
			bullet[i].bullet_pos.y -= bullet[i].bullet_speed; // �����ӵ�λ��
			if (bullet[i].bullet_pos.y < 0) { // ����ӵ�������Ļ�ϱ߽�
				bullet[i].is_active = false; // �����ӵ�
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
				enemy_plane[i].plane_pos.x = rand() % (SCREEN_WIDTH - PLANE_SIZE)+25; // ������ɵл�λ��
				enemy_plane[i].plane_pos.y = -PLANE_SIZE; // ���õл���ʼλ������Ļ�Ϸ�
				enemy_plane[i].speed = 0.3; // ���õл��ٶ�
				enemy_plane[i].plane_type = ENEMY_TYPE_NORMAL; // ���õл�����Ϊ��ͨ�л�
				enemy_plane[i].maxlife = 50; // ���õл��������ֵ
				enemy_plane[i].life = 50; // ���õл�����ֵ
				enemy_num++; // ���ӵл�����
				break; // �˳�ѭ��
			}
		}
	}
}
// ���µл�λ��
void update_enemy() {
	for (int i = 0; i < ENEMY_MAX_NUM; i++) {
		if (enemy_plane[i].is_alive) { // ����л�����
			enemy_plane[i].plane_pos.y += enemy_plane[i].speed; // ���µл�λ��
			if (enemy_plane[i].plane_pos.y > SCREEN_HEIGHT) { // ����л�������Ļ�±߽�
				enemy_plane[i].is_alive = false; // ���õл�
				enemy_num--; // ���ٵл�����
			}
		}
	}
}
//�л�����ҷɻ���ײ���
void check_collision() {
	for (int i = 0; i < ENEMY_MAX_NUM; i++) {
		if (enemy_plane[i].is_alive) { // ����л�����
			// ���л�����ҷɻ�����ײ
			if (abs(enemy_plane[i].plane_pos.x - my_plane.plane_pos.x) < PLANE_SIZE &&
				abs(enemy_plane[i].plane_pos.y - my_plane.plane_pos.y) < PLANE_SIZE) {
				PlaySound("src/sound/enemy1_down.wav", NULL, SND_FILENAME | SND_ASYNC | SND_NOWAIT); // ���ŵл���������Ч
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
					if (abs(bullet[i].bullet_pos.x - enemy_plane[j].plane_pos.x) < PLANE_SIZE &&
						abs(bullet[i].bullet_pos.y - enemy_plane[j].plane_pos.y) < PLANE_SIZE) {
						PlaySound("src/sound/hit.wav", NULL, SND_FILENAME | SND_ASYNC | SND_NOWAIT); // �����ӵ����ел���Ч
						enemy_plane[j].life -= bullet[i].bullet_damage; // �л��ܵ��˺�
						bullet[i].is_active = false; // �����ӵ�
						my_plane.bullet_num--; // �����ӵ�����
						if (enemy_plane[j].life <= 0) { // ����л�����ֵС�ڵ���0
							PlaySound("src/sound/enemy1_down.wav", NULL, SND_FILENAME | SND_ASYNC | SND_NOWAIT); // ���ŵл���������Ч
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
	
	if (my_plane.plane_state == PLANE_STATE_NORMAL && clock()-last_added_time > 200) { // ����ɻ�״̬Ϊ����
		
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


// ������Ϸ״̬����
void UpdateGame() {

	control_plane(); // ���ÿ��Ʒɻ�����������ɻ��ƶ������״̬

	shoot_bullet(); // ���÷����ӵ������������ӵ�����
	
	bullet_move(); // ���ø����ӵ�λ�ú����������ӵ��ƶ�

	if(clock() - last_generate_enemy_time > (2500/level)) { // ������ϴ�����ʱ�䳬����2.5/�ؿ�������
		generate_enemy(); // �������ɵл�����������л�����
		last_generate_enemy_time = clock(); // �������ɵл�ʱ��
	}

	update_enemy(); // ���ø��µл�λ�ú���������л��ƶ�
	check_collision(); // ������ײ��⺯��������л�����ҷɻ�����ײ
	check_bullet_collision(); // ������ײ��⺯������������ӵ���л�����ײ
	check_player_life(); // ���ü���������״̬������������ҷɻ�������״̬
	check_player_endurance(); // ���ü��ɻ��;ú���������ɻ��;�״̬


	check_player_endurance(); // ���ü��ɻ��;ú���������ɻ��;�״̬
	add_endurance(); // ��������;ú���������ɻ��;�״̬
}
