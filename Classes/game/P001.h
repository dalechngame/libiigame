//
// P001.h
// WeddingSalon
//
// Created by DalechnMac on 15-9-22.
//
//

#ifndef __WeddingSalon__P001__
#define __WeddingSalon__P001__

#include "PBase.h"
#include "P001Macro.h"

class P001 : public PBase
{
protected:
    void initData();
    void initWithEvent();

       // 手势
    void stopPromptAni();
    void showPromptWithPos(Vec2 onePoint, PromptShowAniType promptType, Vec2 doublePoint  = Vec2(0.0f, 0.0f));
    void stopPromptWithPos(PromptHideAniType promptType);
    
protected:
        //手势
    bool m_isNeedPrompt;
    CC_SYNTHESIZE(WJSprite*, m_promptSprite, PromptSprite);
    CC_SYNTHESIZE(WJVScrollLayer*, m_crownScrollLayer, CrownScrollLayer);
    
public:
    // tools
    void setAllTouchThingEnable(bool isEnable);
    bool isTouchInNode(Node *TouchRectNode, WJTouchEvent *event, Vec2 offsetPos = Vec2(0.0f, 0.0f));
    void restorePosWithSprite(WJSprite *sprite, float restoreDelayTime = 0.0f, bool restoreIsShow = true);
    
    // 事件
    CC_SYNTHESIZE(WJSprite *, m_touchMoveSprite, TouchMoveSprite);

public:
    virtual bool init() override;
    
    virtual void onEnterTransitionDidFinish() override;
    virtual void onExit() override;
    
public:
    CREATE_SCENE_FUNC(P001);
    
    static void asyncLoadSceneResource();
    
protected:
    void onStoreClosedAndPurchased();
    void onGetFreeVideoClosed(const char* getFreeLockKey,bool isUnlocked);
    void onGetFreeVideoUnlocked(const char* getFreeLockKey);
    
    virtual void initSceneJson(const char* jsonFileName) override;
    virtual GameNumber getGameNumber() override;
};

#endif /* defined(__WeddingSalon__P001__) */