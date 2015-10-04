//
//  P006Sub.cpp
//  WeddingSalon
//
//  Created by DalechnMac on 15-9-30.
//
//

#include "P006Sub.h"
#include "P006.h"

bool P006Baby::init()
{
    if (!Sub::init())
    {
        return false;
    }
	m_messyHair = nullptr;

    return true;
}

void P006Baby::bind(P006 *fa, WJSkeletonAnimation* sub, WJLayerJson* json)
{
	Sub<P006, WJSkeletonAnimation>::bind(fa, sub, json);
   
    if (m_sub)
    {
		m_sub->saveCurrentPosition();
		m_sub->saveCurrentRotation();
		m_sub->saveCurrentScale();
		m_sub->noClickMoveEffect();
		m_sub->setOnTouchAble(CC_CALLBACK_2(P006Baby::thingOnTouchAble, this));
		m_sub->setOnWillMoveTo(CC_CALLBACK_2(P006Baby::thingOnWillMoveTo, this));
		m_sub->setOnTouchEnded(CC_CALLBACK_2(P006Baby::thingOnTouchEnd, this));
    }
    
    subInit();
}

bool P006Baby::subInit()
{
    m_sub->setSlotTexture("dress04", "game/P007/diaper/clothes01_dress04.png");
    m_sub->setCompleteListener(CC_CALLBACK_2(P006Baby::babyAnimationCompleted,this));
    m_sub->stopAllAnimation();
    m_sub->playAnimation("aniIdle03", true, 0);
    
    
    m_messyHair = m_sceneJson->getSubSprite("hair");
    m_messyHair->setOpacity(0);
    m_messyHair->setEnabled(false);                //杂乱的头发是否可以梳理
//    m_sub->addChild(m_messyHair);
    
    m_sub->bindNodeToBone(m_messyHair, "rbl02", Vec2::ZERO,true);
    
    for (int i = 1; i <= 3; i++)
    {
        string slotName = WJUtils::stringAddInt("babyhair", i, 2);
        string hairFile = WJUtils::stringAddInt("game/P006/babyhair",i,2).append(".png");
        m_sub->setSlotTexture(slotName.c_str(), hairFile.c_str());
        m_sub->slotFadeOut(slotName.c_str(), 0.1);
    }
    
    int i = 1;
    do
    {
        string boneName = WJUtils::stringAddInt("point", i, 2);
        spBone *bone = m_sub->findBone(boneName);
        if (bone)
        {
            WJSprite *sprite = WJSprite::create("base/none.png");
            m_sceneJson->addChild(sprite,150);
            sprite->setUserTag(false);              //泡泡位置是否有过泡泡
            
            //            m_bublePosVec.push_back(sprite);
            m_sub->bindNodeToBone(sprite, boneName,Vec2::ZERO,true);
            i++;
        }
        else
        {
            break;
        }
    } while (1);
    
    for (int i = 1; i <= 3; i++)
    {
        WJSprite *blot = m_sceneJson->getSubSprite(WJUtils::stringAddInt("blot_", i, 2).c_str());
//        m_sub->addChild(blot);
        
        string boneName = WJUtils::stringAddInt("stains", i, 2);
        spBone *bone = m_sub->findBone(boneName);
        blot->setUserTag(false);
        //        m_bublePosVec.push_back(blot);
        //        m_blotVec.push_back(blot);
        m_sub->bindNodeToBone(blot, boneName, Vec2::ZERO, true);
    }
    
    int j = 1;
    do
    {
        string boneName = WJUtils::stringAddInt("drip", j, 2);
        spBone *bone = m_sub->findBone(boneName);
        if (bone)
        {
            WJSprite *drop = WJSprite::create("game/P006/drop.png");
            m_sceneJson->addChild(drop, 69);
            drop->setOpacity(0);
            drop->setUserTag(false);                  //水滴是否可以被毛巾擦除
            
            //            m_dropVec.push_back(drop);
            m_sub->bindNodeToBone(drop, boneName,Vec2::ZERO,true);
            j++;
        }
        else
        {
            break;
        }
    } while (1);
    
    return true;
}

void P006Baby::babyAnimationCompleted(int index, int loopCount)
{
    switch (index)
    {
        case 0:
            if (loopCount == 2)
            {
                m_sub->stopAllAnimation();
                m_sub->playAnimation("aniIdle02", false, 1);
            }
            break;
        case 1:
            m_sub->stopAllAnimation();
            m_sub->playAnimation("aniIdle03", false, 2);
            break;
        case 2:
            m_sub->stopAllAnimation();
            m_sub->playAnimation("aniSmile", false, 3);
            Common::sound.play("P005:babySmile");
            break;
        case 3:
            m_sub->stopAllAnimation();
            m_sub->playAnimation("aniIdle03", true, 0);
            break;
    }
}

