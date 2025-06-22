#pragma once//用于防止头文件被多次包含
#include "defines.h" // 包含宏定义头文件(已包含了标准头文件)
#include "bass.h"// BASS音频库相关的函数和接口（用于音频播放、处理等）



inline void loadSounds() {
    // 初始化BASS音频库
    if (!BASS_Init(-1, 44100, 0, NULL, NULL)) {
        MessageBox(NULL, "BASS音频库初始化失败！", "错误", MB_OK | MB_ICONERROR);
        exit(1);
    }
    // 加载音效文件
    bullet_sound = BASS_SampleLoad(FALSE, "src/sound/bullet.wav", 0, 0, 8, 0); // 加载子弹音效
    enemy_down_sound = BASS_SampleLoad(FALSE, "src/sound/enemy_down.wav", 0, 0, 8, 0); // 加载敌机被击落音效
	elite_down_sound = BASS_SampleLoad(FALSE, "src/sound/elite_down.wav", 0, 0, 8, 0); // 加载精英敌机被击落音效
	boss_down_sound = BASS_SampleLoad(FALSE, "src/sound/boss_down.wav", 0, 0, 8, 0); // 加载BOSS被击落音效
    bullet_hit_sound = BASS_SampleLoad(FALSE, "src/sound/hit.wav", 0, 0, 8, 0); // 加载子弹击中音效
}