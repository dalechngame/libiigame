//
//  P001Macro.h
//  WeddingSalon
//
//  Created by DalechnMac on 15-9-23.
//
//

#ifndef WeddingSalon_P001Macro_h
#define WeddingSalon_P001Macro_h
// mp3�Ĳ���״̬
enum Mp3MusicState
{
    currentMusic = 0,		// ��ǰ���ŵ�
    backMusic,				// ��һ��
    nextMusic					// ��һ��
};

// mp3�Ƿ��ڲ���״̬
enum Mp3PlayState
{
    moving = 0,				// ���ڲ�������
    noMoving					// �����Ѿ���ͣ
};

// �и������Ķ���״̬
enum PrincessAni
{
    noHairaniIdle = 0,				// û��ͷ�ĳ�̬
    hairAniIdele,						// ��ͷ֮��ĳ�̬
    eat,									// �Զ���
    sad,									// �ѹ�
    happy								// ����
};

// ��֭�ı��ӵ�״̬
enum FruitBottleState
{
    full = 0,						// ����װ����֭
    empty						// �����ǿյ�
};

// ˮ���Ƿ��Ѿ���ѡ��
enum RandomFruitState
{
    noSelected = 0,		// û�б�ѡ��
    selected					// �Ѿ���ѡ��
};

//��֭���ǵ���ɫ
enum FruitColor
{
    purpleFruit = 0,			// ��ɫ
    redFruit,					// ��ɫ
    orangeFruit				// ��ɫ
};

// ����˪��ͿĨ��״̬
enum CreamState
{
    noCream = 0,			// û��ͿĨ
    fullCream,					// ͿĨ����
    finishCream				// ͿĨ���
};

// ���������״̬
enum CombTaskState
{
    noComb = 0,			// û�д�����ͷ��
    touchHair,				// ������ͷ��
    finishComb				// ������ͷ���
};

// ��ʾ��Ҫִ�еĶ���Ч��
enum PromptShowAniType
{
    pointBlink = 0,							// �������˸��ʾ
    doublePointRestoreMove,			// ������֮�������ƶ���ʾ
    doublePointOneWayMove		// ����֮�䵥���ƶ���ʾ
};

enum PromptHideAniType
{
    fadeOutHide = 0,				// ����ʱ��������
    nowHide							// ��������
};

// ͷ����״̬
enum HairState
{
    freeHair = 0,
    noFreeHair
};

// ���п�ʹ����Ʒ
#define TOUCH_THING_COUNT			5
extern const char *Scene_001_Touch_Key[];

// mp3���
#define MP3_BUTTON_COUNT				3
#define MP3_MUSIC_SOUND_COUNT					3
#define MP3_TASK_TOTAL_TIME						1.0f
#define MP3_MUSIC_PARTICLE_TAG					200

extern const char *Mp3_Button_Frame_Key[];
extern const char *Mp3_Music_Sound_Key[];
extern const char *Mp3_Music_Sound_Pic[];
extern const char *Mp3_Music_Sound_Name[];


// ʳ�����
#define RANDOM_FOOD_COUNT						7
#define BUBBLE_WANT_EAT_TAG						10
#define BUBBLE_WANT_EAT_FADE_TIME			0.5f
#define BUBBLE_WANT_EAT_FLY_TIME				2.0f
#define FOOD_TASK_COUNT								3

// ˮ�����
#define RANDOM_FRUIT_COUNT			3
#define CHOOSE_FRUIT_COUNT			7
#define OFFSET_POINT_TAG					250
extern const char *Random_Fruit_Frame_key[];

// �������
#define CROWN_COUNT						4

// ��ʾ���
#define PROMPT_INTERVAL_TIME				5.0f

// �������
#define CROWN_START_LOCK_NO			2

#endif
