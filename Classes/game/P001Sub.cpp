//
//  P001Sub.cpp
//  WeddingSalon
//
//  Created by DalechnMac on 15-9-28.
//
//

#include "P001Sub.h"
#include "P001.h"

bool P001Comb::s_isShowCrownScroll;
int P001Crown::s_selectCrownInt;

bool P001Comb::init()
{
    if (!Sub<P001, WJSprite>::init())
    {
        return false;
    }
    
    m_isFinishCombTask = noComb;
    m_touchCrownSprite = nullptr;
    s_isShowCrownScroll = false;
    m_crown = nullptr;
    
    return true;
}

void P001Comb ::bind(P001*fa, WJSprite* sub, WJLayerJson* json)
{
    Sub<P001, WJSprite>::bind(fa,sub,  json);
    
    if (m_sub)
    {
        m_sub->saveCurrentPosition();
        m_sub->saveCurrentRotation();
        m_sub->saveCurrentScale();
        m_sub->noClickMoveEffect();
        
        m_sub->setOnTouchAble(CC_CALLBACK_2(P001Comb::thingOnTouchAble, this));
        m_sub->setOnWillMoveTo(CC_CALLBACK_2(P001Comb::thingOnWillMoveTo, this));
        m_sub->setOnTouchEnded(CC_CALLBACK_2(P001Comb::thingOnTouchEnd, this));
    }

}


bool P001Comb::thingOnTouchAble(Node *node, WJTouchEvent *event)
{
    WJSprite *sprite = dynamic_cast<WJSprite *>(node);
    const char * spriteKey = m_sceneJson->getSubKeyByNode(node);
    
//    // 取消提示
//    m_fa->m_isNeedPrompt = false;
//    m_fa->stopPromptAni();
    
    Common::sound.play("Common:button2");
    if (WJUtils::equals(spriteKey, "comb")) // comb
    {
        
        Common::sound.play("Common:pickRight");
        
        if (m_isFinishCombTask != CombTaskState::finishComb)
        {
            Vec2 startPos = Vec2(m_sceneJson->getSubLayer("hairRect")->getBoundingBox().getMinX(), m_sceneJson->getSubLayer("hairRect")->getBoundingBox().getMidY());
            Vec2 endPos = Vec2(m_sceneJson->getSubLayer("hairRect")->getBoundingBox().getMaxX(), m_sceneJson->getSubLayer("hairRect")->getBoundingBox().getMidY());
//            showPromptWithPos(startPos, PromptShowAniType::doublePointRestoreMove, endPos);
        }
        if (m_isFinishCombTask == CombTaskState::finishComb)
        {
            showCrownScrollLayer();
        }
    }
    
    std::string spriteShadowString = spriteKey;
    spriteShadowString.append("_shadow");
    if (m_sceneJson->getSubSprite(spriteShadowString.c_str()))
    {
        m_sceneJson->getSubSprite(spriteShadowString.c_str())->setVisible(false);
    }
    WJSprite *touchMoveSprite = m_fa->getTouchMoveSprite();
    if (touchMoveSprite)
    {
        touchMoveSprite->removeFromParentAndCleanup(true);
       touchMoveSprite = NULL;
    }
    
    // 隐藏原来的，创建新的来代替移动的物品
    sprite->setVisible(false);
    
    if (WJUtils::equals(spriteKey, "comb"))
    {
        touchMoveSprite = WJSprite::create("game/P001/ui/comb_Hold.png");
        m_fa->setTouchMoveSprite(touchMoveSprite);
    }
    else
    {
        touchMoveSprite = WJSprite::create(dynamic_cast<WJSprite *>(sprite)->getSpriteFileName());
        m_fa->setTouchMoveSprite(touchMoveSprite);
    }
    m_sceneJson->addChild(touchMoveSprite, 1000);
    touchMoveSprite->followNode(sprite, Vec2::ZERO, true, false);
    
    return true;
}

bool P001Comb::thingOnWillMoveTo(Node *node, WJTouchEvent *event)
{
    const char * spriteKey = m_sceneJson->getSubKeyByNode(node);
    
    // 播放梳子的音效
    if (WJUtils::equals(spriteKey, "comb") && m_fa->isTouchInNode(m_sceneJson->getSubLayer("hairRect"), event))
    {
        if (!Common::sound.isPlaying("General:comb"))
        {
            Common::sound.play("General:comb");
        }
    }
    
    if (WJUtils::equals(spriteKey, "comb") && m_fa->isTouchInNode(m_sceneJson->getSubLayer("hairRect"), event)
        && m_isFinishCombTask != CombTaskState::finishComb && WJUtils::canClick("", 2000))
    {
        if (m_isFinishCombTask == CombTaskState::noComb)
        {
            m_isFinishCombTask = CombTaskState::touchHair;
            
//            stopPromptWithPos(PromptHideAniType::fadeOutHide);
        }
        else if (m_isFinishCombTask == CombTaskState::touchHair)
        {
            m_isFinishCombTask = CombTaskState::finishComb;
            setHairState(HairState::noFreeHair);
            
            Common::sound.play("Common:bling");
            m_sceneJson->getSubParticle("hairFinishParticle")->resetSystem();
        }
        return true;
    }
    
    return true;

}

void P001Comb::thingOnTouchEnd(Node *node, WJTouchEvent *event)
{
    WJSprite *sprite = dynamic_cast<WJSprite *>(node);
    
    if (sprite->isMoveAble())
    {
        // 还原物品的位置
        m_fa->restorePosWithSprite(sprite, 0.0f, true);
    }

}

void P001Comb::setHairState(HairState hairStyle /* = HairState::freeHair */)
{
    switch (hairStyle)
    {
        case HairState::freeHair:
        {
            
        }
            break;
        case  HairState::noFreeHair:
        {
            playPrincessAni(PrincessAni::hairAniIdele, true);
            initWithSkeleton();
            m_sceneJson->getSubSprite("hairFree")->runActionFadeOut(0.3f);
        }
            break;
    }
}

void P001Comb::playPrincessAni(PrincessAni aniName, bool loop /*= false*/, int stateIndex /* = 0 */)
{
    switch (aniName)
    {
        case PrincessAni::noHairaniIdle:
        {
            m_sceneJson->getSubSkeleton("princessSpine")->playAnimation("aniChangeblk", loop, stateIndex);
        }
            break;
        case PrincessAni::hairAniIdele:
        {
            m_sceneJson->getSubSkeleton("princessSpine")->playAnimation("aniIdle01", loop, stateIndex);
        }
            break;
        case PrincessAni::eat:
        {
            m_sceneJson->getSubSkeleton("princessSpine")->playAnimation("aniEat", loop, stateIndex);
        }
            break;
        case PrincessAni::happy:
        {
            m_sceneJson->getSubSkeleton("princessSpine")->playAnimation("aniHappy", loop, stateIndex);
        }
            break;
        case PrincessAni::sad:
        {
            m_sceneJson->getSubSkeleton("princessSpine")->playAnimation("aniSad", loop, stateIndex);
        }
            break;
    }
}

void P001Comb::initWithSkeleton()
{
    // 初始化公主的动画
    m_sceneJson->getSubSkeleton("princessSpine")->setCompleteListener([=](int trackIndex, int loopCount){
        if (trackIndex == 0)
        {
            playPrincessAni(PrincessAni::hairAniIdele, true);
        }
    });
}

void P001Comb::showCrownScrollLayer()
{
    if (s_isShowCrownScroll)
        return;
    
    // 创建选择窗口
    WJSprite *crownScrollBg = m_sceneJson->getSubSprite("foodFrame");
    
    Sub<P001, WJSprite> *sub = P001Crown::create();
    sub->bind( m_fa, crownScrollBg, m_sceneJson);
    sub->retain();
    m_crown = sub;
}

void P001Comb::onExit()
{
   m_crown->release();
}

void P001Crown ::bind(P001*fa, WJSprite* sub, WJLayerJson* json)
{
    Sub<P001, WJSprite>::bind( fa, sub, json);

    m_crownScrollLayer = WJVScrollLayer::create();
    m_fa->setCrownScrollLayer(m_crownScrollLayer);
    
    Size size = m_sub->getContentSize();
    
    // 取得小图标
    std::vector<string> fileList;
    for (int i = 1; i <= CROWN_COUNT; i++)
    {
        string fileName = WJUtils::stringAddInt("game/P001/crown/crown_Off/crown_Off", i, 3);
        fileName.append(".png");
        fileList.push_back(fileName);
    }
    Vector<WJScrollItem*> items = WJScrollItem::create(fileList, 85, 0, 0.8f);
    
    m_crownScrollLayer->initWithItems( items, Rect(20, -20, size.width, size.height - 40),
                                      NULL, false, 180, Color3B::WHITE, true, false, true, 60.0f);
    m_sub->addChild(m_crownScrollLayer);
    
    // 设置物品的移动事件
    Vector<WJScrollItem *>*crownScrollChilren = m_crownScrollLayer->getItems();
    for (int i = 0; i < crownScrollChilren->size(); i++)
    {
        WJSprite *crownSprite = dynamic_cast<WJSprite *>(crownScrollChilren->at(i)->getContentNode());
        crownSprite->noClickMoveEffect();
        crownSprite->saveCurrentPosition();
        
        crownSprite->setOnClick(CC_CALLBACK_2(P001Crown::crownOnClick, this));
        
        // 加锁
        if (i >= CROWN_START_LOCK_NO - 1)
        {
            WJSprite *lockSprite = WJSprite::create("lock.png");
            lockSprite->setPosition(Vec2(crownSprite->getContentSize().width / 2, crownSprite->getContentSize().height / 2) + Vec2(0.0f, -15.0f));
            lockSprite->saveCurrentPosition();
            crownSprite->addChild(lockSprite, 10, LOCKED_TAG);
            
            // 让锁自己检查状态
            if (Common::isGetFreeUnlocked("AccessoriesAndCrown"))
            {
                lockSprite->removeFromParentAndCleanup(true);
                continue;
            }
            lockSprite->runAction(RepeatForever::create(Sequence::create(CallFunc::create([=](){
                if (Common::isInAppPurchasedByKey("AccessoriesAndCrown"))
                {
                    lockSprite->removeFromParentAndCleanup(true);
                    return;
                }
                
                if (WJUtils::isGetFreeRewardVideoReady("AccessoriesAndCrown") && WJUtils::endWith(lockSprite->getSpriteFileName(), "lock.png"))
                {
                    lockSprite->setPosition(lockSprite->getSavedPosition() + Vec2(0.0f, -20.0f));
                    lockSprite->loadSpriteTexture("getFree.png");
                }
                else if (!WJUtils::isGetFreeRewardVideoReady("AccessoriesAndCrown") && WJUtils::endWith(lockSprite->getSpriteFileName(), "getFree.png"))
                {
                    lockSprite->setPosition(lockSprite->getSavedPosition());
                    lockSprite->loadSpriteTexture("lock.png");
                }
            }), DelayTime::create(1.0f), NULL)));
        }
        
    }
    
    if (m_crownScrollLayer)
    {
        Common::sound.play("Common:slideIn");
        m_sub->runAction(
                            Sequence::create(
                                             CallFunc::create([=](){m_sceneJson->getSubSprite("comb")->setEnabled(false);}),
                                             MoveTo::create(SCROLL_MOVE_TIME, Vec2(m_sceneJson->getSubSprite("foodFrame")->getSavedPosition() + Vec2(-m_sceneJson->getSubSprite("foodFrame")->getContentSize().width, 0.0f))),
                                             CallFunc::create([=](){m_sceneJson->getSubSprite("comb")->setEnabled(true); Common::sound.play("P001:voice37");}),
                                             NULL));
        
        //        // 拖动皇冠的提示
        //        WJSprite *crownSprite = dynamic_cast<WJSprite *>(crownScrollChilren->at(0)->getContentNode());
        //        Vec2 starPos = m_sceneJson->convertToNodeSpace(crownSprite->getParent()->convertToWorldSpace(crownSprite->getPosition())) - Vec2(150, 20);
        //        Vec2 finishPos = m_sceneJson->convertToNodeSpace(m_sceneJson->convertToWorldSpace(m_sceneJson->getSubLayer("crownRect")->getPosition())) + Vec2(20, 20);
        //        m_crownScrollLayer->runAction(Sequence::create(DelayTime::create(SCROLL_MOVE_TIME + 2.0f), CallFunc::create([=](){showPromptWithPos(starPos, PromptShowAniType::doublePointOneWayMove, finishPos);}), NULL));
    }
    

}

bool P001Crown::init()
{
    if (!Sub<P001, WJSprite>::init())
    {
        return false;
    }
    m_crownScrollLayer = nullptr;
    s_selectCrownInt = 1;
    
    return true;

}

void P001Crown::crownOnClick(Node *node, WJTouchEvent *event)
{
    Common::sound.play("P001:voice06");
    Common::sound.play("General:change");
    
    m_crownScrollLayer->stopAllActions();
    WJSprite *sprite = dynamic_cast<WJSprite *>(node);
    
    Vec2 pos(Vec2(m_sceneJson->getSubLayer("crownRect")->getPosition() + Vec2(m_sceneJson->getSubLayer("crownRect")->getContentSize().width / 2, m_sceneJson->getSubLayer("crownRect")->getContentSize().height / 2)));
    
    WJUtils::playParticle("particles/new.plist", m_sceneJson, 1000, true, false, pos, 1.0f, 0);
    
    std::string fileName = WJUtils::stringAddInt("game/P001/crown/crown_On/crown_On", sprite->getTag() + 1, 3);
    fileName.append(".png");
    m_sceneJson->getSubSkeleton("princessSpine")->setSlotTexture("dress01", fileName.c_str());
    
    s_selectCrownInt = sprite->getTag() + 1;

//    stopPromptWithPos(PromptHideAniType::fadeOutHide);
    sprite->setVisible(true);
    
    m_fa->showStarAni(m_sceneJson->getSubSprite("star005"));
    hideCrownScrollLayer();
    
    // 因为只显示一次，所以加入判断
    P001Comb::s_isShowCrownScroll = true;


}

void P001Crown::hideCrownScrollLayer()
{
    if (m_crownScrollLayer)
    {
        Common::sound.play("Common:slideOut");
        m_sceneJson->getSubSprite("foodFrame")->runAction(
                                                          Sequence::create(
                                                                           CallFunc::create([=](){m_sceneJson->getSubSprite("comb")->setEnabled(false);}),
                                                                           MoveTo::create(SCROLL_MOVE_TIME, m_sceneJson->getSubSprite("foodFrame")->getSavedPosition()),
                                                                           CallFunc::create([=](){
                                                              if (m_crownScrollLayer)
                                                              {
                                                                  m_crownScrollLayer->removeFromParentAndCleanup(true);
                                                                  m_crownScrollLayer = NULL;
                                                              }
                                                              m_sceneJson->getSubSprite("comb")->setEnabled(true);
                                                              
//                                                              // 提示禁止解除
//                                                              m_isNeedPrompt = true;
                                                          }),
                                                                           NULL));
    }

}