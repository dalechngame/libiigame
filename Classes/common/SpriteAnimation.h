//
//  SpriteAnimation.h
//  WeddingSalon
//
//  Created by DalechnMac on 15-9-23.
//
//

#ifndef __WeddingSalon__SpriteAnimation__
#define __WeddingSalon__SpriteAnimation__


#include "cocos2d.h"
#include "LBLibraryBase.h"
#include "Common.h"

#define LB_ANI_TYPE_TIP_DELAY_TAG 100000
#define LB_ANI_TYPE_TIP1_TAG 99999
#define LB_ANI_TYPE_TIP2_TAG 99998
#define LB_ANI_TYPE_TIP3_TAG 99997
#define LB_ANI_TYPE_TIP4_TAG 99996
#define LB_ANI_TYPE_TIP5_TAG 99995
#define LB_ANI_TYPE_TIP6_TAG 99994
#define LB_ANI_TYPE_SHOW_TAG 99993
#define LB_ANI_TYPE_HIDE_TAG 99992
#define LB_ANI_TYPE_MOVE_TAG 99991

enum class LBAniTypeTip
{
    ALL,
    Tip1, // 1. scale: 1 �� 1.1����ʱ0.15��
            // 2. scale: 1.1 �� 1����ʱ0.15��
            // 3. �ظ�ǰ��������3��
    Tip2, // 1. alpha: 0.3 �� 0.8����ʱ0.5��
            // 2. alpha: 0.8 �� 0.3����ʱ0.5��
            // 3. �ظ�ǰ��������3�κ�alpha��0.3 �� 0����ʱ0.3��
    Tip3,
    Tip4,
    Tip5,
    Tip6,
};

enum class LBAniTypeShow
{
    Show1,//����ʽ������Ʒ
    Show2,//͸������
    Show3,//��С͸������
    Show4//��˸����
};

enum class LBAniTypeHide
{
    Hide1, // 1. scale: 1 �� 0����ʱ0.5��
                // 2. �ڲ���1��ͬʱ��moveto��ָ��Ŀ���
                // Ŀ�����ò������룬Ĭ����ԭ��ִ�ж���
    Hide2, // 1. alpha��1 �� 0����ʱ0.5��
    Hide3  // 1. scale: 1 �� 1.5����ʱ0.5�룬��easeOut�Ļ�����ʽ������Ϊ1
                // 2. �ڲ���1��ͬʱ��alpha: 1 �� 0����ʱ0.5��
};

enum class LBAniTypeMove
{
    Move1,// һ���������������ģ��
    Move2,// һ�������ƽ����Ƴ���Ļ�����ģ��
    Move3,// 1. moveto����ǰλ�� �� ������������ʱ0.1��
                // ��ҵ�����壬��������Ļ��ƶ��������ָ�Ӵ�λ�á�
                // ����ͨ������Ϊ����λ������һ��ƫ��
    Move4, // moveto����ǰλ�� �� ������������ʱ0.5�룻����easeInOut�Ļ�����ʽ������Ϊ1
                // ��ͨ������ƶ���ʱ���������Ϊ������������
    Move5  // һ����Ͳ�������������Ļ�����µ���
                //1. moveto��������,�ֶ����õ�ǰ���꣩�� Ŀ��λ�õ�y - 50����ʱ0.3�룻����easeInOut�Ļ�����ʽ������Ϊ1
                //2. moveby��y �� y+75����ʱ0.2�룻����easeInOut�Ļ�����ʽ������Ϊ1
                //3. moveby��y �� y-50����ʱ0.2�룻����easeInOut�Ļ�����ʽ������Ϊ1
                //4. moveby��y �� y+50����ʱ0.1�룻����easeInOut�Ļ�����ʽ������Ϊ1
                //5. moveby��y �� y-25����ʱ0.1�룻����easeInOut�Ļ�����ʽ������Ϊ1
};

class SpriteAnimation
{
public:
    // ��ʾ����
    static void playAnimation(WJSprite* sprite, LBAniTypeTip type,bool repeat = false,float waitSecond = 0.0f);
    static void stopAnimation(WJSprite* sprite,LBAniTypeTip type = LBAniTypeTip::ALL);
    // ��ʾ����
    static float show(WJSprite* sprite,LBAniTypeShow type,float waitSecond = 0.0f);
    
    // ���ض���
    static float hide(WJSprite* sprite,LBAniTypeHide type,Vec2 toPoint = Vec2(-9999,-9999),bool cleanUp = true);
    
    // �ƶ�����
    static float moveTo(Node* sprite,LBAniTypeMove type, Vec2 toPoint,float waitSecond = 0.0f,float moveTime = 0.0f);
};

#endif /* defined(__WeddingSalon__SpriteAnimation__) */
