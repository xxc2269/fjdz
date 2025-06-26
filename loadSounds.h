#pragma once//用于防止头文件被多次包含
#include "defines.h" // 包含宏定义头文件(已包含了标准头文件)
#include "bass.h"// BASS音频库相关的函数和接口（用于音频播放、处理等）



inline void loadSounds() {
    // 初始化BASS音频库
    if (!BASS_Init(-1, 44100, 0, NULL, NULL)) {
        MessageBox(NULL, "BASS音频库初始化失败！", "错误", MB_OK | MB_ICONERROR);
        exit(1);
    }
	//加载背景音乐
	bgm1 = BASS_SampleLoad(FALSE, "src/sound/bgm1.mp3", 0, 0, 1, BASS_SAMPLE_LOOP); // 加载背景音乐1
	bgm2 = BASS_SampleLoad(FALSE, "src/sound/bgm2.mp3", 0, 0, 1, BASS_SAMPLE_LOOP);// 加载背景音乐2
	bgm3 = BASS_SampleLoad(FALSE, "src/sound/bgm3.mp3", 0, 0, 1, BASS_SAMPLE_LOOP); // 加载背景音乐3
	bgm4 = BASS_SampleLoad(FALSE, "src/sound/bgm4.mp3", 0, 0, 1, BASS_SAMPLE_LOOP); // 加载背景音乐4
	bgm5 = BASS_SampleLoad(FALSE, "src/sound/bgm5.mp3", 0, 0, 1, BASS_SAMPLE_LOOP); // 加载背景音乐5
    
    // 加载音效文件
    bullet_sound = BASS_SampleLoad(FALSE, "src/sound/bullet.wav", 0, 0, 8, 0); // 加载子弹音效
	mega_bullet_sound = BASS_SampleLoad(FALSE, "src/sound/mega_bullet.ogg", 0, 0, 8, 0); // 加载超级子弹音效
    enemy_down_sound = BASS_SampleLoad(FALSE, "src/sound/enemy_down.wav", 0, 0, 8, 0); // 加载敌机被击落音效
	elite_down_sound = BASS_SampleLoad(FALSE, "src/sound/elite_down.wav", 0, 0, 8, 0); // 加载精英敌机被击落音效
	boss_down_sound = BASS_SampleLoad(FALSE, "src/sound/boss_down.wav", 0, 0, 8, 0); // 加载BOSS被击落音效
    bullet_hit_sound = BASS_SampleLoad(FALSE, "src/sound/hit.wav", 0, 0, 16, 0); // 加载子弹击中音效
	mega_bullet_hit_sound = BASS_SampleLoad(FALSE, "src/sound/mega_hit.ogg", 0, 0, 16, 0); // 加载超级子弹击中音效
	get_life_sound = BASS_SampleLoad(FALSE, "src/sound/get_life.wav", 0, 0, 8, 0); // 加载获取生命音效
	get_power_sound = BASS_SampleLoad(FALSE, "src/sound/get_power.wav", 0, 0, 8, 0); // 加载获取气势音效

	grade1_sound = BASS_SampleLoad(FALSE, "src/sound/grade1.ogg", 0, 0, 8, 0); // 加载一级音效
	grade2_sound = BASS_SampleLoad(FALSE, "src/sound/grade2.ogg", 0, 0, 8, 0); // 加载二级音效
	grade3_sound = BASS_SampleLoad(FALSE, "src/sound/grade3.ogg", 0, 0, 8, 0); // 加载三级音效
	grade4_sound = BASS_SampleLoad(FALSE, "src/sound/grade4.ogg", 0, 0, 8, 0); // 加载四级音效
	grade5_sound = BASS_SampleLoad(FALSE, "src/sound/grade5.ogg", 0, 0, 8, 0); // 加载五级音效
}