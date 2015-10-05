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

#define SCENE_COUNT				9			// 可以选择的场景的数量
#define ARROW_COUNT			8			// 箭头的数量

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
    
    // 工具
    void darkeningSceneIcon(WJSprite *sprite, int sceneInt);
    void lightSceneIcon(WJSprite *sprite, int sceneInt);
    
    // 动画
    void showSceneIconAni();
    void sceneIconScaleAni(WJSprite *sprite);
    void showWinSceneIcon();
    
    void openCurtain();
    void closeCurtain();
    
protected:
    // 事件
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
    
    // 购买成功之后
    void onStoreClosedAndPurchased();
};

#endif /* defined(__WeddingSalon__P010__) */