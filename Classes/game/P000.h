//
// P000.h
// WeddingSalon
//
// Created by DalechnMac on 15-9-22.
//
//

#ifndef __WeddingSalon__P000__
#define __WeddingSalon__P000__

#include "PBase.h"

class P000 : public PBase
{
protected:
    virtual GameNumber getGameNumber() override;
    virtual void initSceneJson(const char* jsonFileName) override;
    
    void initData();
    void initSceneAni();
    void initToolbar();
    
    void onToolbarClick(Node* node, WJTouchEvent* evnet);
    void showInfoDialog();
    
protected:
    LBToolbar *m_toolbar;
protected:
    virtual void onStoreClosedAndPurchased() override;
public:
    virtual bool init() override;
    
    virtual void onEnterTransitionDidFinish() override;
    virtual void onExit() override;
    
public:
    CREATE_SCENE_FUNC(P000);
    
    static void asyncLoadSceneResource();
};

#endif /* defined(__WeddingSalon__P000__) */