//
// P010.h
// WeddingSalon
//
// Created by DalechnMac on 15-9-25.
//
//

#ifndef __WeddingSalon__P010__
#define __WeddingSalon__P010__

#include "PBase.h"

#define SCENE_COUNT				9			// ����ѡ��ĳ���������
#define ARROW_COUNT			8			// ��ͷ������

enum SceneLightOrDark
{
    light = 0,
    dark
};

class P010 : public PBase
{
protected:
    // method
    void initData();
    void initWithEvent();
    
    // ����
    void darkeningSceneIcon(WJSprite *sprite, int sceneInt);
    void lightSceneIcon(WJSprite *sprite, int sceneInt);
    
    // ����
    void showSceneIconAni();
    void sceneIconScaleAni(WJSprite *sprite);
    void showWinSceneIcon();
    
    void openCurtain();
    void closeCurtain();
    
protected:
    // �¼�
    void scenenButtonOnClick(Node *node, WJTouchEvent *event);

protected:
    // attr
    int m_lightSceneCount;
    int m_getSceneNo;
    bool m_isWinEnter;
    
public:
    virtual bool init() override;
    
    virtual void onEnterTransitionDidFinish() override;
    virtual void onExit() override;
    
public:
    CREATE_SCENE_FUNC(P010);
    
    static void asyncLoadSceneResource();
protected:
    virtual GameNumber getGameNumber() override;
    virtual void initSceneJson(const char* jsonFileName) override;
    
    // ����ɹ�֮��
    void onStoreClosedAndPurchased();
};

#endif /* defined(__WeddingSalon__P010__) */