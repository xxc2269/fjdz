#pragma once//���ڷ�ֹͷ�ļ�����ΰ���
#include "defines.h" // �����궨��ͷ�ļ�(�Ѱ����˱�׼ͷ�ļ�)
#include "bass.h"// BASS��Ƶ����صĺ����ͽӿڣ�������Ƶ���š�����ȣ�



inline void loadSounds() {
    // ��ʼ��BASS��Ƶ��
    if (!BASS_Init(-1, 44100, 0, NULL, NULL)) {
        MessageBox(NULL, "BASS��Ƶ���ʼ��ʧ�ܣ�", "����", MB_OK | MB_ICONERROR);
        exit(1);
    }
	//���ر�������
	bgm1 = BASS_SampleLoad(FALSE, "src/sound/bgm1.mp3", 0, 0, 1, BASS_SAMPLE_LOOP); // ���ر�������1
	bgm2 = BASS_SampleLoad(FALSE, "src/sound/bgm2.mp3", 0, 0, 1, BASS_SAMPLE_LOOP);// ���ر�������2
	bgm3 = BASS_SampleLoad(FALSE, "src/sound/bgm3.mp3", 0, 0, 1, BASS_SAMPLE_LOOP); // ���ر�������3
	bgm4 = BASS_SampleLoad(FALSE, "src/sound/bgm4.mp3", 0, 0, 1, BASS_SAMPLE_LOOP); // ���ر�������4
	bgm5 = BASS_SampleLoad(FALSE, "src/sound/bgm5.mp3", 0, 0, 1, BASS_SAMPLE_LOOP); // ���ر�������5
    
    // ������Ч�ļ�
    bullet_sound = BASS_SampleLoad(FALSE, "src/sound/bullet.wav", 0, 0, 8, 0); // �����ӵ���Ч
	mega_bullet_sound = BASS_SampleLoad(FALSE, "src/sound/mega_bullet.ogg", 0, 0, 8, 0); // ���س����ӵ���Ч
    enemy_down_sound = BASS_SampleLoad(FALSE, "src/sound/enemy_down.wav", 0, 0, 8, 0); // ���صл���������Ч
	elite_down_sound = BASS_SampleLoad(FALSE, "src/sound/elite_down.wav", 0, 0, 8, 0); // ���ؾ�Ӣ�л���������Ч
	boss_down_sound = BASS_SampleLoad(FALSE, "src/sound/boss_down.wav", 0, 0, 8, 0); // ����BOSS��������Ч
    bullet_hit_sound = BASS_SampleLoad(FALSE, "src/sound/hit.wav", 0, 0, 16, 0); // �����ӵ�������Ч
	mega_bullet_hit_sound = BASS_SampleLoad(FALSE, "src/sound/mega_hit.ogg", 0, 0, 16, 0); // ���س����ӵ�������Ч
	get_life_sound = BASS_SampleLoad(FALSE, "src/sound/get_life.wav", 0, 0, 8, 0); // ���ػ�ȡ������Ч
	get_power_sound = BASS_SampleLoad(FALSE, "src/sound/get_power.wav", 0, 0, 8, 0); // ���ػ�ȡ������Ч

	grade1_sound = BASS_SampleLoad(FALSE, "src/sound/grade1.ogg", 0, 0, 8, 0); // ����һ����Ч
	grade2_sound = BASS_SampleLoad(FALSE, "src/sound/grade2.ogg", 0, 0, 8, 0); // ���ض�����Ч
	grade3_sound = BASS_SampleLoad(FALSE, "src/sound/grade3.ogg", 0, 0, 8, 0); // ����������Ч
	grade4_sound = BASS_SampleLoad(FALSE, "src/sound/grade4.ogg", 0, 0, 8, 0); // �����ļ���Ч
	grade5_sound = BASS_SampleLoad(FALSE, "src/sound/grade5.ogg", 0, 0, 8, 0); // �����弶��Ч
}