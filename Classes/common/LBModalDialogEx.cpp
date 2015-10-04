//
//  LBModalDialogEx.cpp
//  WeddingSalon
//
//  Created by DalechnMac on 15-9-24.
//
//

#include "LBModalDialogEx.h"

LBModalDialogEx * LBModalDialogEx::create( WJBase *contentNode, bool autoReleaseOnClose )
{
    LBModalDialogEx *dialog = new LBModalDialogEx();
    if (!dialog->init(contentNode, autoReleaseOnClose))
    {
        CC_SAFE_DELETE(dialog);
        return NULL;
    }
    dialog->m_buttonAddInterval = 0.2f; // 按钮依次弹出默认间隔时间
    dialog->autorelease();
    return dialog;
}

void LBModalDialogEx::doShowAnimation(int animationType)
{
    float scale = m_contentNode->getSavedScale();
    m_contentNode->nodeInstance()->stopAllActions();
    m_contentNode->nodeInstance()->setScale(scale * 0.5f);

    if (animationType == (int)LBModalDialogAnimationTypeEx::ScaleEaseBack)
    {
        m_contentNode->nodeInstance()->runAction(Sequence::create(
                                                                  Show::create(),
                                                                  EaseBackOut::create(ScaleTo::create(0.5f, scale)),
                                                                  NULL
                                                                  ));
    }
    else if (animationType == (int)LBModalDialogAnimationTypeEx::Scale)
    {
        m_contentNode->nodeInstance()->runAction(Sequence::create(
                                                                  Show::create(),
                                                                  ScaleTo::create(0.2f, scale * 1.2f),
                                                                  ScaleTo::create(0.1f, scale * 0.8f),
                                                                  ScaleTo::create(0.1f, scale * 1.0f),
                                                                  NULL
                                                                  ));
    }
    else if (animationType == (int)LBModalDialogAnimationTypeEx::PopIn1)
    {
        m_contentNode->nodeInstance()->setVisible(true);
        WJLayerJson* layerJson = (WJLayerJson*)m_contentNode;
        layerJson->setScale(scale*1.0f);
        //layerJson->runActionFadeOut(0,0,false,10,false);
        layerJson->runActionFadeInSavedOpacity(0.15f,0,false,10,false);
        layerJson->runAction(CCSequence::create(
                                                CCEaseOut::create(CCScaleTo::create(0.15f,scale*1.1f),1),
                                                CCEaseOut::create(CCScaleTo::create(0.15f,scale*1.0f),1),
                                                NULL
                                                ));
    }
    else if (animationType == (int)LBModalDialogAnimationTypeEx::PopIn2)
    {
        m_contentNode->nodeInstance()->setVisible(true);
        WJLayerJson* layerJson = (WJLayerJson*)m_contentNode;
        layerJson->setScale(0.0f);
        layerJson->runAction(CCSequence::create(
                                                CCShow::create(),
                                                CCEaseOut::create(CCScaleTo::create(0.15f,scale*1.1f),1),
                                                CCEaseOut::create(CCScaleTo::create(0.15f,scale*1.0f),1),
                                                NULL
                                                ));
    }
    else if (animationType == (int)LBModalDialogAnimationTypeEx::PopIn3)
    {
        m_contentNode->nodeInstance()->setVisible(true);
        WJLayerJson* layerJson = (WJLayerJson*)m_contentNode;
        layerJson->setScale(1.5f*scale);
        //layerJson->runActionFadeOut(0,0,false,10,false);
        layerJson->runActionFadeInSavedOpacity(0.15f,0,false,10,false);
        layerJson->runAction(CCSequence::create(
                                                CCShow::create(),
                                                CCScaleTo::create(0.15f, 1.0f*scale),
                                                NULL
                                                ));
    }
    else if (animationType == (int)LBModalDialogAnimationTypeEx::PopIn4)
    {
        m_contentNode->nodeInstance()->setVisible(true);
        WJLayerJson* layerJson = (WJLayerJson*)m_contentNode;
        layerJson->setScale(0.0f);
        layerJson->runAction(CCSequence::create(
                                                CCShow::create(),
                                                CCEaseOut::create(CCScaleTo::create(0.3f,scale*1.1f),1),
                                                CCEaseOut::create(CCScaleTo::create(0.3f,scale*1.0f),1),
                                                NULL
                                                ));
    } else if (animationType == (int)LBModalDialogAnimationTypeEx::PopIn5)
    {
        Size winSize = Director::getInstance()->getWinSize();
        Vec2 currentPos = m_contentNode->nodeInstance()->getPosition();
        Size contentSize = m_contentNode->nodeInstance()->getContentSize();
        m_contentNode->nodeInstance()->setPosition(Vec2(currentPos.x,winSize.height+contentSize.height/2+10));
        m_contentNode->nodeInstance()->setVisible(true);
        m_contentNode->nodeInstance()->setScale(1.0f);
        m_contentNode->nodeInstance()->runAction(Sequence::create(
                                                                  EaseSineInOut::create(MoveTo::create(0.3f,currentPos+Vec2(0,-50))),
                                                                  EaseSineInOut::create(MoveBy::create(0.15f,Vec2(0,50))),
                                                                  nullptr
                                                                  ));
    }

    // 弹窗的按钮依次出现
    playButtonShowAni();
}

void LBModalDialogEx::doCloseAnimation(int animationType)
{
    float scale = m_contentNode->getSavedScale();
    m_contentNode->nodeInstance()->stopAllActions();

    if (animationType == (int)LBModalDialogAnimationTypeEx::ScaleEaseBack)
    {
        m_contentNode->nodeInstance()->runAction(Sequence::create(
                                                                  Spawn::create(
                                                                                FadeOut::create(0.5f),
                                                                                EaseBackIn::create(ScaleTo::create(0.5f, 0.5f)),
                                                                                NULL),
                                                                  Hide::create(),
                                                                  NULL
                                                                  ));
    }
    else if (animationType == (int)LBModalDialogAnimationTypeEx::Scale)
    {

        m_contentNode->nodeInstance()->runAction(Sequence::create(
                                                                  ScaleTo::create(0.2f, scale * 1.3f),
                                                                  ScaleTo::create(0.2f, scale * 0.1f),
                                                                  Hide::create(),
                                                                  NULL
                                                                  ));
    }
    else if (animationType == (int)LBModalDialogAnimationTypeEx::PopIn1)
    {
        WJLayerJson* layerJson = (WJLayerJson*)m_contentNode;
        layerJson->runActionFadeOut(0.3f,0,false,10,false);
        layerJson->runAction(CCSequence::create(
                                                CCEaseOut::create(CCScaleTo::create(0.15f,scale*1.1f),1),
                                                CCEaseOut::create(CCScaleTo::create(0.15f,scale*1.0f),1),
                                                NULL
                                                ));
    }
    else if (animationType == (int)LBModalDialogAnimationTypeEx::PopIn2)
    {
        WJLayerJson* layerJson = (WJLayerJson*)m_contentNode;
        layerJson->runAction(CCSequence::create(
                                                CCEaseIn::create(CCScaleTo::create(0.15f,scale*1.1f),1),
                                                CCEaseIn::create(CCScaleTo::create(0.15f,0.0f),1),
                                                CCHide::create(),
                                                NULL
                                                ));
    }
    else if (animationType == (int)LBModalDialogAnimationTypeEx::PopIn3)
    {
        WJLayerJson* layerJson = (WJLayerJson*)m_contentNode;
        layerJson->runActionFadeOut(0.15f,0,false,10,false);
        layerJson->runAction(CCSequence::create(
                                                CCScaleTo::create(0.15f, 1.5f*scale),
                                                CCHide::create(),
                                                NULL
                                                ));
    }else if (animationType == (int)LBModalDialogAnimationTypeEx::PopIn4)
    {
        WJLayerJson* layerJson = (WJLayerJson*)m_contentNode;
        layerJson->runAction(CCSequence::create(
                                                CCEaseIn::create(CCScaleTo::create(0.3f,scale*1.1f),1),
                                                CCEaseIn::create(CCScaleTo::create(0.3f,0.0f),1),
                                                CCHide::create(),
                                                NULL
                                                ));
    } else if (animationType == (int)LBModalDialogAnimationTypeEx::PopIn5)
    {
        Size winSize = Director::getInstance()->getWinSize();
        Vec2 currentPos = m_contentNode->nodeInstance()->getPosition();
        Size contentSize = m_contentNode->nodeInstance()->getContentSize();
        //m_contentNode->nodeInstance()->setPosition(Vec2(currentPos.x,winSize.height+contentSize.height/2+10));
        m_contentNode->nodeInstance()->runAction(Sequence::create(
                                                                  EaseSineInOut::create(MoveBy::create(0.15f,Vec2(0,-50))),
                                                                  EaseSineInOut::create(MoveTo::create(0.3f,Vec2(currentPos.x,winSize.height+contentSize.height/2+10))),
                                                                  CCHide::create(),
                                                                  nullptr
                                                                  ));
    }

}

void LBModalDialogEx::addAniButton(std::string buttonStr)
{
    m_buttonStringList.push_back(buttonStr);
}

void LBModalDialogEx::setAddButtonInterval(float time)
{
    m_buttonAddInterval = time;
}

void LBModalDialogEx::playButtonShowAni()
{
    // 按钮依次出现动画
    if(m_buttonStringList.size()!=0)
    {
        WJSprite * buttonSprite;
        WJLayerJson* layerJson = (WJLayerJson*)m_contentNode;
        for (unsigned int i=0;i<m_buttonStringList.size();i++)
        {
            buttonSprite = layerJson->getSubSpriteByKey(m_buttonStringList.at(i).c_str());
            buttonSprite->setScale(0);
            buttonSprite->runAction(CCSequence::create(
                                                       CCDelayTime::create(0.2f+m_buttonAddInterval*i),
                                                       CCEaseOut::create(CCScaleTo::create(0.15f, buttonSprite->getSavedScale()*1.1f),1.0f),
                                                       CCEaseOut::create(CCScaleTo::create(0.15f, buttonSprite->getSavedScale()*1.0f),1.0f),
                                                       NULL
                                                       ));
        }
    }
}
