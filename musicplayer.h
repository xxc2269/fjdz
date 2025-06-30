#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <vector>
#include <map>
#include "bass.h"
#include"defines.h" // 包含宏定义头文件（已包含了标准头文件）

using namespace std;

// 音乐管理器类
class MusicManager {
public:
    // 游戏状态枚举
    enum GameState {
        MENU,
        LEVEL1,
        LEVEL2,
        LEVEL3,
        LEVEL4,
        LEVEL5,
        BOSS_FIGHT,
        PLAYER_DEATH,
        GAME_VICTORY,
        PAUSED
    };

    // 构造函数
    MusicManager() : currentState(MENU), originalVolume(0.7f), isBossLooping(false) {}

    // 初始化音乐系统
    bool Initialize() {
        // 初始化BASS库
        if (!BASS_Init(-1, 44100, 0, nullptr, nullptr)) {
            cerr << "BASS初始化失败! 错误代码: " << BASS_ErrorGetCode() << endl;
            return false;
        }

        // 加载所有音乐资源
        if (!LoadMusicResources()) {
            cerr << "音乐资源加载失败!" << endl;
            return false;
        }

        return true;
    }

    // 加载音乐资源
    bool LoadMusicResources() {
        // 关卡音乐
        levelMusic[LEVEL1] = LoadStream("C:/Users/10691/source/repos/飞机大战音乐/飞机大战音乐/lib/bgm1.mp3");
        levelMusic[LEVEL2] = LoadStream("C:/Users/10691/source/repos/飞机大战音乐/飞机大战音乐/lib/bgm2.ogg");
        levelMusic[LEVEL3] = LoadStream("C:/Users/10691/source/repos/飞机大战音乐/飞机大战音乐/lib/bgm3.mp3");
        levelMusic[LEVEL4] = LoadStream("C:/Users/10691/source/repos/飞机大战音乐/飞机大战音乐/lib/bgm4.mp3");
        levelMusic[LEVEL5] = LoadStream("C:/Users/10691/source/repos/飞机大战音乐/飞机大战音乐/lib/bgm5.mp3");

        // 音效
        deathSound = LoadStream("C:/Users/10691/source/repos/飞机大战音乐/飞机大战音乐/lib/bgmover.mp3");
        victorySound = LoadStream("C://CloudMusic//周杰伦 - 半岛铁盒.flac");

        // Boss循环段
        bossLoops[LEVEL1] = make_pair(30.0, 60.0); // 30-60秒循环
        bossLoops[LEVEL2] = make_pair(45.0, 75.0);
		bossLoops[LEVEL3] = make_pair(40.0, 70.0);// 40-70秒循环
		bossLoops[LEVEL4] = make_pair(35.0, 65.0);// 35-65秒循环
		bossLoops[LEVEL5] = make_pair(50.0, 90.0);// 50-90秒循环

        // 检查所有资源是否加载成功
        for (auto& music : levelMusic) {
            if (!music.second) {
                cerr << "关卡" << music.first << "音乐加载失败!" << endl;
                return false;
            }
        }

        if (!deathSound || !victorySound) {
            cerr << "音效加载失败!" << endl;
            return false;
        }

        // 设置初始音量
        SetMasterVolume(originalVolume);

        return true;
    }

    // 改变游戏状态
    void ChangeState(GameState newState) {
        if (currentState == newState) return;

        // 只在这些状态才停止音乐
        if (newState == PLAYER_DEATH || newState == GAME_VICTORY || newState == MENU) {
            StopAllMusic();
        }

        currentState = newState;
        isBossLooping = false;

        switch (newState) {
        case LEVEL1: case LEVEL2: case LEVEL3: case LEVEL4: case LEVEL5:
            PlayLevelMusic(newState);
            break;
        case BOSS_FIGHT:
            StartBossLoop(currentState);
            break;
        case PLAYER_DEATH:
            PlayDeathSound();
            break;
        case GAME_VICTORY:
            PlayVictorySound();
            break;
        case PAUSED:
            SetPauseVolume();
            break;
        case MENU:
        default:
            break;
        }
    }

    // 切换暂停状态
    void TogglePause() {
        if (currentState == PAUSED) {
            // 恢复音量
            RestoreVolume();
            currentState = previousState; // 只恢复状态，不重新播放音乐
        } else {
            // 降低音量
            previousState = currentState;
            SetPauseVolume();
            currentState = PAUSED; // 只切换状态，不停止音乐
        }
    }

    // 更新音乐系统
    void Update() {
        // 处理Boss循环
        if (isBossLooping && currentState == BOSS_FIGHT) {
            HandleBossLoop();
        }
    }

    // 清理资源
    void Cleanup() {
        // 释放所有音乐流
        for (auto& music : levelMusic) {
            if (music.second) {
                BASS_StreamFree(music.second);
            }
        }

        if (deathSound) BASS_StreamFree(deathSound);
        if (victorySound) BASS_StreamFree(victorySound);

        // 关闭BASS
        BASS_Free();
    }

private:
    // 加载音频流
    HSTREAM LoadStream(const char* filename) {
        HSTREAM stream = BASS_StreamCreateFile(
            FALSE, filename, 0, 0, 0
        );

        if (!stream) {
            cerr << "无法加载音频文件: " << filename
                << " 错误代码: " << BASS_ErrorGetCode() << endl;
        }

        return stream;
    }

    // 播放关卡音乐
    void PlayLevelMusic(GameState level) {
        StopAllMusic(); // 先停止所有音乐
        HSTREAM stream = levelMusic[level];
        if (stream) {
            currentStream = stream;
            BASS_ChannelPlay(stream, TRUE);
            cout << "播放关卡" << (int)level << "音乐" << endl;
        }
    }

    // 开始Boss循环
    void StartBossLoop(GameState level) {
        StopAllMusic(); // 先停止所有音乐
        if (bossLoops.find(level) != bossLoops.end()) {
            double startTime = bossLoops[level].first;
            double endTime = bossLoops[level].second;
            HSTREAM stream = levelMusic[level];
            if (stream) {
                QWORD startPos = BASS_ChannelSeconds2Bytes(stream, startTime);
                QWORD endPos = BASS_ChannelSeconds2Bytes(stream, endTime);

                // 设置循环终点的同步回调
                BASS_ChannelSetSync(stream, BASS_SYNC_POS | BASS_SYNC_MIXTIME,
                    endPos, LoopCallback, this);

                // 跳到循环起点
                BASS_ChannelSetPosition(stream, startPos, BASS_POS_BYTE);

                currentStream = stream;
                isBossLooping = true;

                // 从当前位置（循环起点）开始播放
                BASS_ChannelPlay(stream, FALSE);

                cout << "Boss战开始! 循环播放 " << startTime << "s-" << endTime << "s" << endl;
            }
        }
    }

    // 处理Boss循环
    void HandleBossLoop() {
        // 检查当前播放位置是否接近循环结束点
        // 在实际游戏中，这个逻辑可能不需要，因为同步回调已经处理了循环
    }

    // 播放死亡音效
    void PlayDeathSound() {
        if (deathSound) {
            BASS_ChannelPlay(deathSound, TRUE); // 从头开始播放
            cout << "播放死亡音效" << endl;
        }
    }

    // 播放胜利音乐
    void PlayVictorySound() {
        if (victorySound) {
            BASS_ChannelPlay(victorySound, TRUE); // 从头开始播放
            cout << "播放胜利音乐" << endl;
        }
    }

    // 设置暂停音量
    void SetPauseVolume() {
        SetMasterVolume(originalVolume * 0.3f); // 降低到30%音量
        cout << "游戏暂停，音乐音量降低" << endl;
    }

    // 恢复音量
    void RestoreVolume() {
        SetMasterVolume(originalVolume);
        cout << "游戏恢复，音乐音量正常" << endl;
    }

    // 设置主音量
    void SetMasterVolume(float volume) {
        // 设置所有流的音量
        for (auto& music : levelMusic) {
            if (music.second) {
                BASS_ChannelSetAttribute(music.second, BASS_ATTRIB_VOL, volume);
            }
        }

        // 设置音效的音量
        if (deathSound) BASS_ChannelSetAttribute(deathSound, BASS_ATTRIB_VOL, volume);
        if (victorySound) BASS_ChannelSetAttribute(victorySound, BASS_ATTRIB_VOL, volume);
    }

    // 停止所有音乐
    void StopAllMusic() {
        for (auto& music : levelMusic) {
            if (music.second) {
                BASS_ChannelStop(music.second);
            }
        }

        if (deathSound) BASS_ChannelStop(deathSound);
        if (victorySound) BASS_ChannelStop(victorySound);
    }

    // 循环回调函数（静态）
    static void CALLBACK LoopCallback(HSYNC handle, DWORD channel, DWORD data, void* user) {
        MusicManager* manager = static_cast<MusicManager*>(user);
        if (manager) {
            // 获取当前关卡的循环起始点
            GameState level = manager->currentState;
            if (manager->bossLoops.find(level) != manager->bossLoops.end()) {
                double startTime = manager->bossLoops[level].first;
                QWORD startPos = BASS_ChannelSeconds2Bytes(channel, startTime);

                // 设置位置回到循环起点
                BASS_ChannelSetPosition(channel, startPos, BASS_POS_BYTE);

                // 重新设置同步点
                double endTime = manager->bossLoops[level].second;
                QWORD endPos = BASS_ChannelSeconds2Bytes(channel, endTime);
                BASS_ChannelSetSync(channel, BASS_SYNC_POS | BASS_SYNC_MIXTIME,
                    endPos, LoopCallback, user);
            }
        }
    }

private:
    GameState currentState;      // 当前游戏状态
    GameState previousState;     // 暂停前的游戏状态
    float originalVolume;        // 原始音量

    // 音乐资源
    map<GameState, HSTREAM> levelMusic;  // 关卡音乐
    HSTREAM deathSound;                  // 死亡音效
    HSTREAM victorySound;                // 胜利音乐

    // Boss循环信息 <关卡, <开始时间, 结束时间>>
    map<GameState, pair<double, double>> bossLoops;

    bool isBossLooping;          // 是否正在循环Boss音乐
    HSTREAM currentStream = 0;   // 当前正在播放的音乐流
};

// 游戏模拟类
class Game {
public:
    Game() : currentLevel(1), playerAlive(true), gamePaused(false), gameWon(false) {
        // 初始化音乐管理器
        if (!musicManager.Initialize()) {
            cerr << "音乐系统初始化失败!" << endl;
            exit(1);
        }

        // 进入第一关
        StartLevel(1);
    }

    // 开始新关卡
    void StartLevel(int level) {
        currentLevel = level;
        playerAlive = true;
        bossActive = false;

        // 更新音乐状态
        musicManager.ChangeState(static_cast<MusicManager::GameState>(level));
    }

    // 触发Boss战
    void StartBossFight() {
        bossActive = true;
        musicManager.ChangeState(MusicManager::BOSS_FIGHT);
    }

    // 玩家死亡
    void PlayerDeath() {
        playerAlive = false;
        musicManager.ChangeState(MusicManager::PLAYER_DEATH);
    }

    // 通关游戏
    void WinGame() {
        gameWon = true;
        musicManager.ChangeState(MusicManager::GAME_VICTORY);
    }

    // 切换暂停状态
    void TogglePause() {
        gamePaused = !gamePaused;
        musicManager.TogglePause();
    }

    // 更新游戏状态
    void Update() {
        musicManager.Update();
    }

    // 清理资源
    void Cleanup() {
        musicManager.Cleanup();
    }

    // 游戏主循环
    void Run() {
        cout << "=== 游戏音乐系统演示 ===" << endl;
        cout << "按键控制:" << endl;
        cout << "  1-5: 切换到关卡1-5" << endl;
        cout << "  b: 开始Boss战" << endl;
        cout << "  d: 玩家死亡" << endl;
        cout << "  w: 游戏胜利" << endl;
        cout << "  p: 暂停/继续游戏" << endl;
        cout << "  q: 退出游戏" << endl;

        bool running = true;
        while (running) {
            if (_kbhit()) {
                char key = _getch();

                switch (key) {
                case '1': StartLevel(1); break;
                case '2': StartLevel(2); break;
                case '3': StartLevel(3); break;
                case '4': StartLevel(4); break;
                case '5': StartLevel(5); break;
                case 'b': StartBossFight(); break;
                case 'd': PlayerDeath(); break;
                case 'w': WinGame(); break;
                case 'p': TogglePause(); break;
                case 'q': running = false; break;
                }
            }

            Update();
            Sleep(50);
        }

        Cleanup();
    }

private:
    int currentLevel;        // 当前关卡
    bool playerAlive;        // 玩家是否存活
    bool bossActive;         // Boss是否激活
    bool gamePaused;         // 游戏是否暂停
    bool gameWon;            // 游戏是否胜利

    MusicManager musicManager; // 音乐管理器
};

int musicplayer() {
    Game game;
    game.Run();
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
