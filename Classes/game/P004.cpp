//
// P004.cpp
// WeddingSalon
//
// Created by DalechnMac on 15-9-25.
//
//

#include "P004.h"
#include "LBModalDialogEx.h"
INIT_SCENE_LOADER_ASYNC(P004);

void P004::asyncLoadSceneResource()
{
    	WJLayerJsonPreload::getInstance()->asyncPreload("game/json/p004.json");
}

GameNumber P004::getGameNumber()
{
    return GameNumber::P004;
}

bool P004::init()
{
    if ( !PBase::init() )
    {
        return false;
    }
    
    initData();
    
    initSceneJson("game/json/p004.json");
    
    return true;
}

void P004::initData()
{
    
}

void P004::initSceneJson( const char* jsonFileName )
{
    PBase::initSceneJson(jsonFileName);
    
//    m_microlayer = WJLayerJson::create("game/json/p004_chouxue.json");
//    m_microlayer->ignoreAnchorPointForPosition(false);
//    m_microlayer->setAnchorPoint(Vec2(0.5f, 0.5f));
//    m_microlayer->setPosition(Vec2(winSize.width/2,winSize.height/2));
//    
//    
//    
//    
//    m_nextButton = WJSprite::create("button/next.png");
//    m_nextButton->retain();
//    
//    
//    
//    
//    
//    if(!m_info_panelNode)
//    {
//        
//        m_info_panelNode = m_microlayer->getSubNodeByKey("info_panel");
//        m_infoPanelPos = m_info_panelNode->getParent()->convertToWorldSpace(m_info_panelNode->getPosition());
//        m_info_panelNode->retain();
//        m_info_panelNode->setVisible(false);
//        m_info_panelNode->retain();
//        m_info_panelNode->removeFromParent();
//    }
//    
//    
////    m_nextButton->setOnTouchAble(CC_CALLBACK_2(P004::onNextBtnTouch, this));
////    m_nextButton->setOnWillMoveTo(CC_CALLBACK_2(P004::onNextBtnWillMoveTo, this));
////    m_nextButton->setOnTouchEnded(CC_CALLBACK_2(P004::onNextBtnButtonClick, this));
//    
//    
//    
//    
//    m_chouXueDialog = LBModalDialogEx::create(m_microlayer,false);
//    
//    
//    this->addChild(m_chouXueDialog,ZORDER_SCENE_JSON+1);
//    
//    
//    m_maskSpr = m_microlayer->getSubSpriteByKey("mask");
//    m_microscopeSpr = m_microlayer->getSubSpriteByKey("microscope");
//    m_microscopeSpr->retain();
//    m_microscopeSpr->removeFromParent();
//    
//    
//    //m_microscopeSpr->followNode(m_maskSpr);
//    
//    m_maskSpr->noClickMoveEffect();
////    m_maskSpr->setOnTouchAble(CC_CALLBACK_2(P004::onMicroCamTouch, this));
////    m_maskSpr->setOnWillMoveTo(CC_CALLBACK_2(P004::onMicroCamWillMoveTo, this));
////    m_maskSpr->setOnTouchEnded(CC_CALLBACK_2(P004::onMicroCamButtonClick, this));
//    m_maskSpr->setEnabled(false);
//    m_cellNode1 = m_microlayer->getSubNodeByKey("celllayer1");
//    m_cellNode1->setVisible(false);
//    m_cellNode2 = m_microlayer->getSubNodeByKey("celllayer2");
//    m_cellNode2->setVisible(false);
//    m_whitecellNode = m_microlayer->getSubNodeByKey("whitecell");
//    m_whitecellNode->setVisible(false);
//    
//    
//    m_erythrocyteSpr = m_microlayer->getSubSpriteByKey("cell_bg");
//    m_erythrocyteSpr->ignoreAnchorPointForPosition(true);
//    m_erythrocyteSpr->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
//    m_erythrocyteSpr->setPosition(Vec2::ZERO);
//    m_erythrocyteSpr->setVisible(false);
//    
//
    
}

void P004::onExit()
{
    PBase::onExit();
    
}

void P004::onEnterTransitionDidFinish()
{
    PBase::onEnterTransitionDidFinish();
}