#pragma once//���ڷ�ֹͷ�ļ�����ΰ���
#include "defines.h" // �����궨��ͷ�ļ�(�Ѱ����˱�׼ͷ�ļ�)
#include "bass.h"// BASS��Ƶ����صĺ����ͽӿڣ�������Ƶ���š�����ȣ�



inline void loadSounds() {
    // ��ʼ��BASS��Ƶ��
    if (!BASS_Init(-1, 44100, 0, NULL, NULL)) {
        MessageBox(NULL, "BASS��Ƶ���ʼ��ʧ�ܣ�", "����", MB_OK | MB_ICONERROR);
        exit(1);
    }
    // ������Ч�ļ�
    bullet_sound = BASS_SampleLoad(FALSE, "src/sound/bullet.wav", 0, 0, 8, 0); // �����ӵ���Ч
    enemy_down_sound = BASS_SampleLoad(FALSE, "src/sound/enemy_down.wav", 0, 0, 8, 0); // ���صл���������Ч
	elite_down_sound = BASS_SampleLoad(FALSE, "src/sound/elite_down.wav", 0, 0, 8, 0); // ���ؾ�Ӣ�л���������Ч
	boss_down_sound = BASS_SampleLoad(FALSE, "src/sound/boss_down.wav", 0, 0, 8, 0); // ����BOSS��������Ч
    bullet_hit_sound = BASS_SampleLoad(FALSE, "src/sound/hit.wav", 0, 0, 8, 0); // �����ӵ�������Ч
}