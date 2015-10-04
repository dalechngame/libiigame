//
//  P001Macro.h
//  WeddingSalon
//
//  Created by DalechnMac on 15-9-23.
//
//

#ifndef WeddingSalon_P001Macro_h
#define WeddingSalon_P001Macro_h
// mp3的播放状态
enum Mp3MusicState
{
    currentMusic = 0,		// 当前播放的
    backMusic,				// 上一首
    nextMusic					// 下一首
};

// mp3是否处于播放状态
enum Mp3PlayState
{
    moving = 0,				// 正在播放音乐
    noMoving					// 音乐已经暂停
};

// 孕妇公主的动画状态
enum PrincessAni
{
    noHairaniIdle = 0,				// 没梳头的常态
    hairAniIdele,						// 梳头之后的常态
    eat,									// 吃东西
    sad,									// 难过
    happy								// 高兴
};

// 果汁的杯子的状态
enum FruitBottleState
{
    full = 0,						// 杯子装满果汁
    empty						// 杯子是空的
};

// 水果是否已经被选择
enum RandomFruitState
{
    noSelected = 0,		// 没有被选择
    selected					// 已经被选择
};

//果汁会是的颜色
enum FruitColor
{
    purpleFruit = 0,			// 紫色
    redFruit,					// 红色
    orangeFruit				// 橙色
};

// 妊娠霜被涂抹的状态
enum CreamState
{
    noCream = 0,			// 没有涂抹
    fullCream,					// 涂抹满了
    finishCream				// 涂抹完成
};

// 梳子任务的状态
enum CombTaskState
{
    noComb = 0,			// 没有触摸到头发
    touchHair,				// 触摸到头发
    finishComb				// 梳子梳头完成
};

// 提示需要执行的动画效果
enum PromptShowAniType
{
    pointBlink = 0,							// 单点的闪烁提示
    doublePointRestoreMove,			// 两个点之间来回移动提示
    doublePointOneWayMove		// 两点之间单向移动提示
};

enum PromptHideAniType
{
    fadeOutHide = 0,				// 隐藏时淡出隐藏
    nowHide							// 立即隐藏
};

// 头发的状态
enum HairState
{
    freeHair = 0,
    noFreeHair
};

// 所有可使用物品
#define TOUCH_THING_COUNT			5
extern const char *Scene_001_Touch_Key[];

// mp3相关
#define MP3_BUTTON_COUNT				3
#define MP3_MUSIC_SOUND_COUNT					3
#define MP3_TASK_TOTAL_TIME						1.0f
#define MP3_MUSIC_PARTICLE_TAG					200

extern const char *Mp3_Button_Frame_Key[];
extern const char *Mp3_Music_Sound_Key[];
extern const char *Mp3_Music_Sound_Pic[];
extern const char *Mp3_Music_Sound_Name[];


// 食物相关
#define RANDOM_FOOD_COUNT						7
#define BUBBLE_WANT_EAT_TAG						10
#define BUBBLE_WANT_EAT_FADE_TIME			0.5f
#define BUBBLE_WANT_EAT_FLY_TIME				2.0f
#define FOOD_TASK_COUNT								3

// 水果相关
#define RANDOM_FRUIT_COUNT			3
#define CHOOSE_FRUIT_COUNT			7
#define OFFSET_POINT_TAG					250
extern const char *Random_Fruit_Frame_key[];

// 梳子相关
#define CROWN_COUNT						4

// 提示相关
#define PROMPT_INTERVAL_TIME				5.0f

// 加锁相关
#define CROWN_START_LOCK_NO			2

#endif
