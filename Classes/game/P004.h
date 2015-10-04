//
// P004.h
// WeddingSalon
//
// Created by DalechnMac on 15-9-25.
//
//

#ifndef __WeddingSalon__P004__
#define __WeddingSalon__P004__

#include "PBase.h"
class LBModalDialogEx;

class P004 : public PBase
{
protected:
    // method
    void initData();
    
protected:
    // attr
    WJLayerJson *  m_microlayer ;
    
    Node * m_info_panelNode;
    
    RenderTexture * microscopeRT;
    RenderTexture * m_cellRT;
    WJSprite * m_maskSpr;
    WJSprite * m_microscopeSpr;
    WJSprite * m_erythrocyteSpr;			//红血版
    Node *m_cellNode1,*m_cellNode2, * m_whitecellNode;
    LayerColor * m_colorlayer;

    LBModalDialogEx * m_chouXueDialog;
    
    Point m_infoPanelPos;
    WJSprite * m_nextButton;	//下一步
    
public:
    virtual bool init() override;
    
    virtual void onEnterTransitionDidFinish() override;
    virtual void onExit() override;
    
public:
    CREATE_SCENE_FUNC(P004);
    
    static void asyncLoadSceneResource();
protected:
    virtual GameNumber getGameNumber() override;
    virtual void initSceneJson(const char* jsonFileName) override;
    
};

#endif /* defined(__WeddingSalon__P004__) */