//
// P001.cpp
// WeddingSalon
//
// Created by DalechnMac on 15-9-22.
//
//

#include "P001.h"
#include "SpriteAnimation.h"
#include "P001Sub.h"

const char *Scene_001_Touch_Key[TOUCH_THING_COUNT] = {"mp3", "handcream", "food", "drink", "comb"};

const char *Mp3_Button_Frame_Key[MP3_BUTTON_COUNT] = {"last", "play", "rigth"};

const char *Mp3_Music_Sound_Key[MP3_MUSIC_SOUND_COUNT] =
{"P001:mp3music1", "P001:mp3music2", "P001:mp3music3"};
const char *Mp3_Music_Sound_Pic[MP3_MUSIC_SOUND_COUNT] =
{"game/P001/mp3/mp3screen001.png", "game/P001/mp3/mp3screen002.png", "game/P001/mp3/mp3screen003.png"};
const char *Mp3_Music_Sound_Name[MP3_MUSIC_SOUND_COUNT] =
{"game/P001/mp3/mp3screen001_name.png", "game/P001/mp3/mp3screen002_name.png", "game/P001/mp3/mp3screen003_name.png"};

const char *Random_Fruit_Frame_key[RANDOM_FRUIT_COUNT] = {"fruit01_b", "fruit02_b", "fruit03_b"};



INIT_SCENE_LOADER_ASYNC(P001);


void P001::asyncLoadSceneResource()
{
    // 预加载场景Json中的 所有图片 及 骨骼
    WJLayerJsonPreload::getInstance()->asyncPreload("game/json/p001.json");
    WJLayerJsonPreload::getInstance()->asyncPreload("game/json/p001_frame.json");
    WJLayerJsonPreload::getInstance()->asyncPreload("game/json/p001_mp3.json");
    WJLayerJsonPreload::getInstance()->asyncPreload("game/json/p001_handcream.json");
    
}

GameNumber P001::getGameNumber()
{
    return GameNumber::P001;
}

bool P001::init()
{
    if ( !PBase::init() )
    {
        return false;
    }
    
    initData();
    
    initSceneJson("game/json/p001.json");
    
    initWithEvent();
    
    return true;
}

void P001::initData()
{
    m_isNeedPrompt = true;
    m_promptSprite = nullptr;
    m_crownScrollLayer = nullptr;
    m_touchMoveSprite = nullptr;
}

void P001::initSceneJson( const char* jsonFileName )
{
    PBase::initSceneJson(jsonFileName);
    
    // 创建并隐藏提示用的提示用的箭头
    m_promptSprite = WJSprite::create("game/common/shouzhi.png");
    m_promptSprite->setPosition(Vec2(0.0f, 0.0f));
    m_promptSprite->setVisible(false);
    m_promptSprite->setAnchorPoint(Vec2(1.0f, 1.0f));
    this->addChild(m_promptSprite, ZORDER_ADS_LAYER - 1);
    
    // 设置头发的状态
//    setHairState(HairState::freeHair);
    
    // 隐藏任务完成的星星
    for (int i = 1; i <= 5; i++)
    {
        std::string starString = WJUtils::stringAddInt("star", i, 3);
        m_sceneJson->getSubSprite(starString.c_str())->setVisible(false);
    }
    
    // 隐藏果汁满时的粒子效果
    m_sceneJson->getSubParticle("bottleFullParticle")->stopSystem();
    m_sceneJson->getSubParticle("hairFinishParticle")->stopSystem();
    
}

void P001::initWithEvent()
{
//    // 初始化物品栏的触摸事件
//    for (int i = 0; i < TOUCH_THING_COUNT; i++)
//    {
        WJSprite *sprite = m_sceneJson->getSubSprite(Scene_001_Touch_Key[4]);

        Sub<P001, WJSprite> *sub = P001Comb::create();
        sub->bind(this, sprite, m_sceneJson);
        sub->retain();

//    }
    
}


void P001::setAllTouchThingEnable(bool isEnable)
{
    m_sceneJson->setEnabled(isEnable);
}

bool P001::isTouchInNode(Node *TouchRectNode, WJTouchEvent *event, Vec2 offsetPos /*= Vec2(0.0f, 0.0f)*/)
{
    if (TouchRectNode && event)
    {
        Vec2 touchPos = TouchRectNode->getParent()->convertTouchToNodeSpace(event->touch) + offsetPos;
        Rect nodeRect = TouchRectNode->getBoundingBox();
        if (nodeRect.containsPoint(touchPos))
        {
            return true;
        }
        return false;
    }
    return false;
}

void P001::stopPromptAni()
{
    m_sceneJson->getSubSprite("bg03")->stopAllActions();
    for (int i = 0; i < TOUCH_THING_COUNT; i++)
    {
        WJSprite *sprite = m_sceneJson->getSubSprite(Scene_001_Touch_Key[i]);
        sprite->stopAllActions();
        sprite->setScale(1.0f);
    }
}

void P001::showPromptWithPos(Vec2 onePoint, PromptShowAniType promptType, Vec2 doublePoint /* = Vec2(0.0f, 0.0f)*/)
{
    stopPromptWithPos(PromptHideAniType::nowHide);
    switch (promptType)
    {
        case PromptShowAniType::pointBlink:
        {
            m_promptSprite->setPosition(onePoint);
            m_promptSprite->runAction(Sequence::create(DelayTime::create(3.0f), Show::create(), FadeIn::create(0.3f), DelayTime::create(0.5f), FadeOut::create(0.3f), Hide::create(), NULL));
        }
            break;
        case PromptShowAniType::doublePointRestoreMove:
        {
            m_promptSprite->setPosition(onePoint);
            m_promptSprite->runAction(Sequence::create(DelayTime::create(3.0f), Show::create(), FadeIn::create(0.3f), MoveTo::create(0.5f, doublePoint), MoveTo::create(0.5f, onePoint), FadeOut::create(0.3f), Hide::create(), NULL));
        }
            break;
        case PromptShowAniType::doublePointOneWayMove:
        {
            m_promptSprite->setPosition(onePoint);
            m_promptSprite->runAction(Sequence::create(DelayTime::create(3.0f), Show::create(), FadeIn::create(0.3f), MoveTo::create(0.5f, doublePoint), FadeOut::create(0.3f), Hide::create(), MoveTo::create(0.0f, onePoint), NULL));
        }
            break;
    }
}

void P001::stopPromptWithPos(PromptHideAniType promptType)
{
    switch (promptType)
    {
        case PromptHideAniType::fadeOutHide:
        {
            m_promptSprite->stopAllActions();
            m_promptSprite->runAction(Sequence::create(FadeOut::create(0.3f), Hide::create(), NULL));
        }
            break;
        case PromptHideAniType::nowHide:
        {
            m_promptSprite->stopAllActions();
            m_promptSprite->setVisible(false);
        }
            break;
    }
}

void P001::restorePosWithSprite(WJSprite *sprite, float restoreDelayTime /*= 0.0f*/, bool restoreIsShow /*= true*/)
{
    const char * spriteKey = m_sceneJson->getSubKeyByNode(sprite);
    // 还原物品
    sprite->runAction(
                      Sequence::create(
                                       CallFunc::create([=](){setAllTouchThingEnable(false);}),
                                       DelayTime::create(restoreDelayTime),
                                       MoveTo::create(RESTORE_POS_TIME, sprite->getSavedPosition()),
                                       CallFunc::create([=](){
                          setAllTouchThingEnable(true);
                          sprite->setVisible(restoreIsShow);
                          sprite->setMoveAble(true);
                          
                          // 提示禁止解除
                          m_isNeedPrompt = true;
                          
                          std::string spriteShadowString = spriteKey;
                          spriteShadowString.append("_shadow");
                          if (m_sceneJson->getSubSprite(spriteShadowString.c_str()))
                          {
                              m_sceneJson->getSubSprite(spriteShadowString.c_str())->setVisible(restoreIsShow);
                          }
                          
                          if (m_touchMoveSprite)
                          {
                              m_touchMoveSprite->removeFromParentAndCleanup(true);
                              m_touchMoveSprite = NULL;
                          }
                      }),
                                       NULL));
}

void P001::onExit()
{
    PBase::onExit();
    
}

void P001::onEnterTransitionDidFinish()
{
    PBase::onEnterTransitionDidFinish();
}

void P001::onStoreClosedAndPurchased()
{
    PBase::onStoreClosedAndPurchased();
    
    // 购买成功之后
    
}

void P001::onGetFreeVideoClosed(const char* getFreeLockKey, bool isUnlocked)
{
    PBase::onGetFreeVideoClosed(getFreeLockKey, isUnlocked);
}

void P001::onGetFreeVideoUnlocked(const char* getFreeLockKey)
{
    PBase::onGetFreeVideoUnlocked(getFreeLockKey);
    
    Vector<WJScrollItem *>*crownScrollChilren = m_crownScrollLayer->getItems();
    for (int i = 0; i < crownScrollChilren->size(); i++)
    {
        WJSprite *crownSprite = dynamic_cast<WJSprite *>(crownScrollChilren->at(i)->getContentNode());
        WJSprite *lockSprite = dynamic_cast<WJSprite *>(crownSprite->getChildByTag(LOCKED_TAG));
        if (lockSprite)
        {
            lockSprite->runAction(Sequence::create(FadeOut::create(0.3f), RemoveSelf::create(), CallFunc::create([=](){
                ParticleSystemQuad *particle = ParticleSystemQuad::create("particles/huanzhuang2.plist");
                particle->setPosition(Vec2(crownSprite->getContentSize().width / 2, crownSprite->getContentSize().height / 2));
                crownSprite->addChild(particle);
                Common::sound.play("Common:bling2");
            }), NULL));
        }
    }
}